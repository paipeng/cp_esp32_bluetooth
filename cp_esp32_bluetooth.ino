#include "cp_bluetooth.h"


CPBluetooth bluetooth;
#define SLAVE_MAC "16:04:14:32:47:6f"
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  bluetooth.init();
  bluetooth.discover();
  String slave(SLAVE_MAC);
  
  bluetooth.connect(slave);
}

void loop() {
  bluetooth.loop();
  delay(20);
}
