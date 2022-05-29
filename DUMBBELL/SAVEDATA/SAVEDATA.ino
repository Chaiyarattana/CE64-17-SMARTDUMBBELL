#define M5STACK_MPU6886
#include <M5Stack.h>
#include <SPI.h>
#include <SD.h>

File myFile;
unsigned long previousMillis_Save = 0;
unsigned long Time = 0;
int saveState = 0;
String dataLog[9][160];
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

  if (M5.BtnA.wasReleased() && saveState == 0) 
  {
    saveState = 1;
    previousMillis_Save = currentMillis;
    Time = currentMillis;
  }
  if (saveState == 1) 
  {
    M5.Lcd.setTextColor(WHITE , BLACK);
    M5.Lcd.setCursor(20, 220);
    M5.Lcd.print(Time);
    M5.Lcd.setTextColor(WHITE , BLACK);
    M5.Lcd.setCursor(100, 220);
    M5.Lcd.print(CountSave);
    if ((currentMillis - previousMillis_Save) >= 50 ) 
    {
      dataLog[0][CountSave] = accX;
      dataLog[1][CountSave] = accY;
      dataLog[2][CountSave] = accZ;
      dataLog[3][CountSave] = gyroX;
      dataLog[4][CountSave] = gyroY;
      dataLog[5][CountSave] = gyroZ;
      dataLog[6][CountSave] = pitch;
      dataLog[7][CountSave] = roll;
      dataLog[8][CountSave] = yaw;
      CountSave++;
      if (M5.BtnA.wasReleased() && saveState == 1) 
      {
        M5.Lcd.setTextColor(WHITE , BLACK);
        M5.Lcd.setCursor(100, 220);
        M5.Lcd.print("Writing..");
        saveState = 2;        
      }
      if(CountSave > 159)
      {
        M5.Lcd.setTextColor(WHITE , BLACK);
        M5.Lcd.setCursor(100, 220);
        M5.Lcd.print("Writing..");
        saveState = 2;
      }
      previousMillis_Save = currentMillis;
    }
  }
   if (saveState == 2) 
   {
    myFile = SD.open("/data.txt", FILE_WRITE);
    if (myFile) 
    {
      Serial.print("Writing...");
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 10;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 20;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 30;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 40;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 50;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 60;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 70;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      pos = 80;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);
      pos = 90;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);
      pos = 100;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);
      pos = 110;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);
      pos = 120;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);
      pos = 130;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);
      pos = 140;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);
      pos = 150;
      myFile.println(dataLog[0][pos+0] + " "  + dataLog[1][pos+0] + " "  + dataLog[2][pos+0] + " " +  dataLog[3][pos+0] + " "  + dataLog[4][pos+0] + " "  + dataLog[5][pos+0] + " "  + dataLog[6][pos+0] + " "  + dataLog[7][pos+0] + " "  + dataLog[8][pos+0]);
      myFile.println(dataLog[0][pos+1] + " "  + dataLog[1][pos+1] + " "  + dataLog[2][pos+1] + " " +  dataLog[3][pos+1] + " "  + dataLog[4][pos+1] + " "  + dataLog[5][pos+1] + " "  + dataLog[6][pos+1] + " "  + dataLog[7][pos+1] + " "  + dataLog[8][pos+1]);
      myFile.println(dataLog[0][pos+2] + " "  + dataLog[1][pos+2] + " "  + dataLog[2][pos+2] + " " +  dataLog[3][pos+2] + " "  + dataLog[4][pos+2] + " "  + dataLog[5][pos+2] + " "  + dataLog[6][pos+2] + " "  + dataLog[7][pos+2] + " "  + dataLog[8][pos+2]);
      myFile.println(dataLog[0][pos+3] + " "  + dataLog[1][pos+3] + " "  + dataLog[2][pos+3] + " " +  dataLog[3][pos+3] + " "  + dataLog[4][pos+3] + " "  + dataLog[5][pos+3] + " "  + dataLog[6][pos+3] + " "  + dataLog[7][pos+3] + " "  + dataLog[8][pos+3]);
      myFile.println(dataLog[0][pos+4] + " "  + dataLog[1][pos+4] + " "  + dataLog[2][pos+4] + " " +  dataLog[3][pos+4] + " "  + dataLog[4][pos+4] + " "  + dataLog[5][pos+4] + " "  + dataLog[6][pos+4] + " "  + dataLog[7][pos+4] + " "  + dataLog[8][pos+4]);
      myFile.println(dataLog[0][pos+5] + " "  + dataLog[1][pos+5] + " "  + dataLog[2][pos+5] + " " +  dataLog[3][pos+5] + " "  + dataLog[4][pos+5] + " "  + dataLog[5][pos+5] + " "  + dataLog[6][pos+5] + " "  + dataLog[7][pos+5] + " "  + dataLog[8][pos+5]);
      myFile.println(dataLog[0][pos+6] + " "  + dataLog[1][pos+6] + " "  + dataLog[2][pos+6] + " " +  dataLog[3][pos+6] + " "  + dataLog[4][pos+6] + " "  + dataLog[5][pos+6] + " "  + dataLog[6][pos+6] + " "  + dataLog[7][pos+6] + " "  + dataLog[8][pos+6]);
      myFile.println(dataLog[0][pos+7] + " "  + dataLog[1][pos+7] + " "  + dataLog[2][pos+7] + " " +  dataLog[3][pos+7] + " "  + dataLog[4][pos+7] + " "  + dataLog[5][pos+7] + " "  + dataLog[6][pos+7] + " "  + dataLog[7][pos+7] + " "  + dataLog[8][pos+7]);
      myFile.println(dataLog[0][pos+8] + " "  + dataLog[1][pos+8] + " "  + dataLog[2][pos+8] + " " +  dataLog[3][pos+8] + " "  + dataLog[4][pos+8] + " "  + dataLog[5][pos+8] + " "  + dataLog[6][pos+8] + " "  + dataLog[7][pos+8] + " "  + dataLog[8][pos+8]);
      myFile.println(dataLog[0][pos+9] + " "  + dataLog[1][pos+9] + " "  + dataLog[2][pos+9] + " " +  dataLog[3][pos+9] + " "  + dataLog[4][pos+9] + " "  + dataLog[5][pos+9] + " "  + dataLog[6][pos+9] + " "  + dataLog[7][pos+9] + " "  + dataLog[8][pos+9]);

      Serial.println("Done.");
      M5.Lcd.setTextColor(WHITE , BLACK);
      M5.Lcd.setCursor(100, 220);
      M5.Lcd.print("Save Done");
//      CountSave = 0;
//      saveState = 0;
    } 
    else 
    {
      M5.Lcd.setTextColor(WHITE , BLACK);
      M5.Lcd.setCursor(100, 220);
      M5.Lcd.print("Error Opening");
      Serial.println("error opening");
    }
  }
  delay(1);
}
