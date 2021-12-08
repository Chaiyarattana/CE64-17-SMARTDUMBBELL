#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
String string = "TEST M5STACK TO APPLICATION\r\n";
const char *C = string.c_str();
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    for (int i = 0; i < string.length(); i++)
      {
        SerialBT.write(string[i]);   // Push each char 1 by 1 on each loop pass
      }
      delay(1000); 
  }
  
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
