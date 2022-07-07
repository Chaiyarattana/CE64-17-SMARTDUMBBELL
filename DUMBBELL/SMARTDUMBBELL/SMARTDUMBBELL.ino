#define M5STACK_MPU6886
#include <M5Stack.h>
#include <SPI.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;
String reciveMsg = "";
String msgUse = "";

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"



unsigned long previousMillis_Save = 0;
unsigned long Time = 0;
int saveState = 0;
String dataLog[9][100];


String string = "\r\n";
const char *C = string.c_str();


int CountSave = 0;
int pos = 0;
float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;


///////////////////////////////////////////////////////////////////////////////////////////////////////
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};
class MyCallbacks: public BLECharacteristicCallbacks { // recive msg function
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
        {
          Serial.print(rxValue[i]);
          reciveMsg = reciveMsg + rxValue[i];
        }
        msgUse = reciveMsg; //use msgUse(string) for condition ^-^
        Serial.println("");
        Serial.print("msgUse lenght : ");
        Serial.println(String(msgUse.length()));
        Serial.println(msgUse);
        saveState = 0;
        Serial.println("*********");
        reciveMsg = "";
      }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////





// the setup routine runs once when M5Stack starts up
void setup() 
{
  //Serial.begin(115200, SERIAL_8N1, 16, 17);
  //bluetooth setup
  BLEDevice::init("Smart Dumbel");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
  pTxCharacteristic->addDescriptor(new BLE2902());         
  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );
  pRxCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();       
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

  
  // Initialize the M5Stack object
  M5.begin();
  Wire.begin();
  M5.Power.begin();
  M5.IMU.Init();
//  if (!SD.begin(4)) 
//  {
//    Serial.println("initialization failed!");
//    while (1);
//  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(2);
                          
}

// the loop routine runs over and over again forever
void loop() 
{
  unsigned long currentMillis = millis();
  M5.update();
  // put your main code here, to run repeatedly:
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);
  
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ);
  M5.Lcd.setCursor(220, 42);
  M5.Lcd.print(" o/s");
  M5.Lcd.setCursor(0, 65);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
  M5.Lcd.setCursor(220, 87);
  M5.Lcd.print(" G");
  M5.Lcd.setCursor(0, 110);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw);
  M5.Lcd.setCursor(220, 132);
  M5.Lcd.print(" degree");
  M5.Lcd.setCursor(0, 190);
  M5.Lcd.print("deviceConnected : " + String(deviceConnected));
  if (deviceConnected) 
  {
    if(msgUse == "1") // Cuban Press
    {
      if(roll >= -140 && roll <= -80 && pitch >= 0 && pitch <= 30 && saveState == 0)
      {
        saveState = 1;        
      }
      else if(roll >= -200 && roll <= -150 && pitch >= 0 && pitch <= 40 && saveState == 1)
      {    
        saveState = 2;
      }
      else if(roll >= 60 && roll <= 100 && pitch >= 0 && pitch <= 30 && saveState == 2)
      {    
        saveState = 3;
      }
      else if(roll >= 50 && roll <= 100 && pitch >= 0 && pitch <= 30 && accY >= 1.3 && saveState == 3)
      {    
        saveState = 4;
      }
      else if(roll >= 150 && roll <= 180 && pitch >= 0 && pitch <= 30 && saveState == 4)
      {    
        saveState = 5;
      }
      else if(roll >= -140 && roll <= -80 && pitch >= 0 && pitch <= 30 && accY <= 0 && saveState == 5)
      {    
        saveState = 6;
      }
      else if(roll >= -140 && roll <= -80 && pitch >= 0 && pitch <= 30 && saveState == 6)
      {          
        CountSave += 1;
        String str = String(CountSave);
        uint8_t first = atoi (str.substring(0,1).c_str ());
        if(first == 9)
        {
          pTxCharacteristic->setValue("9");
        }
        else
        {
          pTxCharacteristic->setValue(&first,str.length()+1);
        }
        pTxCharacteristic->notify();
        delay(10);
        saveState = 0;
      }
    }
    else if(msgUse == "2") //Biceps Curl
    {
      if(roll >= -100 && roll <= -35 && pitch >= -20 && pitch <= 50 &&  gyroX >= -300 && gyroX <= 250)
      {
         saveState = 1;        
      }
      if(roll >= 35 && roll <= 90 && pitch >= -20 && pitch <= 50 &&  gyroX >= -300 && gyroX <= 250)
       {
        if(saveState == 1)
        {
          CountSave += 1;
          String str = String(CountSave);
          uint8_t first = atoi (str.substring(0,1).c_str ());
          if(first == 9)
          {
            pTxCharacteristic->setValue("9");
          }
          else
          {
            pTxCharacteristic->setValue(&first,str.length()+1);
          }
          pTxCharacteristic->notify();
          delay(10);
          saveState = 0;
        }
      }
    }
    else if(msgUse == "3") // fly
    {
      if(roll >= -40 && roll <= 0 && pitch >= -30 && pitch <= 30 &&  gyroX >= -50 && gyroX <= 30 && saveState == 0)
      {
        saveState = 1;        
      }
      else if(roll >= 85 && roll <= 115 && pitch >= -20 && pitch <= 20 && gyroX >= -70 && gyroX <= 0 && saveState == 1)
      {    
        
        saveState = 2;
      }
      else if(roll >= -30 && roll <= 0 && pitch >= -20 && pitch <= 10 && gyroX >= -120 && gyroX <= 0 && saveState == 2)
      {    
          CountSave += 1;
          String str = String(CountSave);
          uint8_t first = atoi (str.substring(0,1).c_str ());
          if(first == 9)
          {
            pTxCharacteristic->setValue("9");
          }
          else
          {
            pTxCharacteristic->setValue(&first,str.length()+1);
          }
          pTxCharacteristic->notify();
          delay(10);
          saveState = 0;
      }
    }
    else if(msgUse == "4") // front_Raise
    {
      if(roll >= -170 && roll <= -100 && pitch >= -30 && pitch <= 50 &&   saveState == 0)
      {
        saveState = 1;        
      }
      else if(roll >= 150 && roll <= 190 && pitch >= -30 && pitch <= 50 &&  saveState == 1)
      {    
        saveState = 2;
      }
      else if(roll >= -170 && roll <= -100 && pitch >= -30 && pitch <= 50 &&  saveState == 2)
      {    
          CountSave += 1;
          String str = String(CountSave);
          uint8_t first = atoi (str.substring(0,1).c_str ());
          if(first == 9)
          {
            pTxCharacteristic->setValue("9");
          }
          else
          {
            pTxCharacteristic->setValue(&first,str.length()+1);
          }
          pTxCharacteristic->notify();
          delay(10);
          saveState = 0;
      } 
    }
    else if(msgUse == "5") //Bent_Over_Row
    {
       if(accX >= 0 && roll <= 0.4 && accY >= -1.5 && accY <= -0.5 &&  gyroZ >= 20 && gyroZ <= 70 && saveState == 0)
    {
    saveState = 1;        
    }
       else if(accX >= 0.5 && accX <= 1.5 && accY >= -0.8 && accY <= 0.3 && gyroZ >= -100 && gyroZ <= -20 && saveState == 1)
    {    
    saveState = 2;
    }
       else if(accX >= 0 && roll <= 0.4 && accY >= -1.2 && accY <= -1 &&  gyroZ >= 20 && gyroZ <= 70 && saveState == 2)
      {    
          CountSave += 1;
          String str = String(CountSave);
          uint8_t first = atoi (str.substring(0,1).c_str ());
          if(first == 9)
          {
            pTxCharacteristic->setValue("9");
          }
          else
          {
            pTxCharacteristic->setValue(&first,str.length()+1);
          }
          pTxCharacteristic->notify();
          delay(10);
          saveState = 0;
      } 
    }
    else if(msgUse == "6") //Brench_Press
    {
        if(accY >= 0.9 && accY <= 1.4 && accZ >= 0 && accZ <= 0.4 &&  pitch >= -5 && pitch <= 20 && roll >= 50 && roll <= 100 && saveState == 0)
        {
          previousMillis_Save = currentMillis;
          saveState = 1;        
        }
        else if(accY >= 0.8 && accY <= 1.0 && accZ >= -0.5 && accZ <= 0 &&  pitch >= -3 && pitch <= 20 && roll >= 50 && roll <= 100 && saveState == 1)
        {        
          if ((currentMillis - previousMillis_Save) >= 600 ) 
          {
            saveState = 2;
            previousMillis_Save = currentMillis;
          }
        }
        else if(accY >= 0.9 && accY <= 1.4 && accZ >= 0 && accZ <= 0.4 &&  pitch >= -5 && pitch <= 20 && roll >= 50 && roll <= 100 && saveState == 2)
        {    
          if ((currentMillis - previousMillis_Save) >= 600 ) 
          {      
            CountSave += 1;
            String str = String(CountSave);
            uint8_t first = atoi (str.substring(0,1).c_str ());
            if(first == 9)
            {
              pTxCharacteristic->setValue("9");
            }
            else
            {
              pTxCharacteristic->setValue(&first,str.length()+1);
            }
            pTxCharacteristic->notify();
            delay(10);
            saveState = 0;
            previousMillis_Save = currentMillis;
          }
        }
    }
    else if(msgUse == "9") //ClearData
    {
        saveState = 0;
        CountSave = 0;
    }
    else
    {
      pTxCharacteristic->setValue("Change Mode");
      pTxCharacteristic->notify();      
      delay(10);
    }
  }
  if (!deviceConnected && oldDeviceConnected) 
  {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
  }
  if (deviceConnected && !oldDeviceConnected) 
  {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }

//  SerialBT.write(char(CountSave));  
//  SerialBT.write('\r');
//  SerialBT.write('\n');
//  String stringcount = String(String(CountSave) + "\r\n");
//  for(int i = 0 ; i < stringcount.length() ; i++)
//  {
//    SerialBT.write(stringcount[i]);
//    delay(5);
//  }

    M5.Lcd.setCursor(0, 150);
    M5.Lcd.printf("Count =  %d",CountSave);
    M5.Lcd.setCursor(0, 170);
    M5.Lcd.printf("State =  %d",saveState);
 }
