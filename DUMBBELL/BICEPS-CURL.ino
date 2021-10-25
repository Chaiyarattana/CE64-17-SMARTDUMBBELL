#define M5STACK_MPU6886
#include <M5Stack.h>
#include <SPI.h>
#include <SD.h>

File myFile;
unsigned long previousMillis_Save = 0;
unsigned long Time = 0;
int saveState = 0;
String dataLog[9][100];
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



// the setup routine runs once when M5Stack starts up
void setup() 
{
  // Initialize the M5Stack object
  M5.begin();
  Wire.begin();
  M5.Power.begin();
  M5.IMU.Init();
  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    while (1);
  }
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

//  if (M5.BtnA.wasReleased() && saveState == 0) 
//  {
//    saveState = 1;
//    previousMillis_Save = currentMillis;
//    Time = currentMillis;
//  }
//  if(gyroX <= 150 && gyroX >= 100 && gyroY <= 50 && gyroY >= -70 && gyroZ <= 50 && gyroZ >= -70)
//  {
//    saveState = 0;
//  }
//  if(gyroX <= -150 && gyroX >= -200 && gyroY <= 50 && gyroY >= -70 && gyroZ <= 50 && gyroZ >= -70)
//  {
//    if(saveState == 0)
//    {
//      CountSave += 1;
//      saveState = 1;
//    }    
//  }
  if(roll >= -90 && roll <= -60 && pitch >= -20 && pitch <= 50 && yaw >= -180 && yaw <= 105&& gyroX >= -150 && gyroX <= 150)
  {
    saveState = 1;        
  }
  if(roll >= 55 && roll <= 100 && pitch >= -20 && pitch <= 50 && yaw >= -180 && yaw <= 105&& gyroX >= -150 && gyroX <= 150)
  {
    if(saveState == 1)
    {
      CountSave += 1;
      saveState = 0;
    }
  }  
  M5.Lcd.setCursor(0, 150);
  M5.Lcd.printf("Count =  %d",CountSave);
  delay(1);
 }
