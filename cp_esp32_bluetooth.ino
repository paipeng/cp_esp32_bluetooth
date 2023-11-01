#include <BluetoothSerial.h>

BluetoothSerial bs;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  bs.begin("ESP32-BT");
}

void loop() {
  if (Serial.available()) {
    bs.write(Serial.read());
  } else if (bs.available()) {
    Serial.write(bs.read());
  }
  delay(20);
}
