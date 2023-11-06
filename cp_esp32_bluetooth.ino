#include "cp_bluetooth.h"

#define CP_GPIO_SW 35

CPBluetooth bluetooth;
#define SLAVE_MAC "MOCUTE-032_B53-476F"
uint8_t address[6]  = {0x16, 0x04, 0x14, 0x32, 0x47, 0x6f};
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(CP_GPIO_SW, INPUT);

  bluetooth.init();
  //bluetooth.discover();
  
  //String slave(SLAVE_MAC);
  //bluetooth.connect(slave);
  //bluetooth.connect(address, "1344");
}

void loop() {
  int b = digitalRead(CP_GPIO_SW);
  if (b == LOW) {
    Serial.println("button pressed");
    bluetooth.discover();
    String slave(SLAVE_MAC);
    bluetooth.connect(slave);
  }
  bluetooth.loop();
  delay(1);
}
