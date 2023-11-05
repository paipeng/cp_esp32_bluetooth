#include "cp_bluetooth.h"

#define CP_GPIO_SW 35

CPBluetooth bluetooth;
#define SLAVE_MAC "16:04:14:32:47:6f"
uint8_t address[6]  = {0x16, 0x04, 0x14, 0x32, 0x47, 0x6f};
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(CP_GPIO_SW, INPUT);

  bluetooth.init();
  bluetooth.discover();
  
  bluetooth.connect(address);
}

void loop() {
  int b = digitalRead(CP_GPIO_SW);
  if (b == LOW) {
    Serial.println("button pressed");
    bluetooth.connect(address);
  }
  bluetooth.loop();
  delay(20);
}
