#include "cp_bluetooth.h"


#define BT_DISCOVER_TIME  10000

BluetoothSerial *pBtSerial = NULL;
/*
ESP_SPP_INIT_EVT: When SPP mode is initialized
ESP_SPP_UNINIT_EVT: When the SPP mode is deinitialized
ESP_SPP_DISCOVERY_COMP_EVT: When service discovery is complete
ESP_SPP_OPEN_EVT: When an SPP client opens a connection
ESP_SPP_CLOSE_EVT: When an SPP connection is closed
ESP_SPP_START_EVT: When the SPP server is initialized
ESP_SPP_CL_INIT_EVT: When an SPP client initializes a connection
ESP_SPP_DATA_IND_EVT: When receiving data through an SPP connection
ESP_SPP_CONG_EVT: When congestion status changes on an SPP connection
ESP_SPP_WRITE_EVT: When sending data through SPP.
ESP_SPP_SRV_OPEN_EVT: When a client connects to the SPP server
ESP_SPP_SRV_STOP_EVT: When the SPP server stops
*/
// Bluetooth Event Handler CallBack Function Definition
void bt_event_handler(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_START_EVT) {
    Serial.println("Initialized SPP");
  }
  else if (event == ESP_SPP_SRV_OPEN_EVT ) {
    Serial.println("Client connected");
  }
  else if (event == ESP_SPP_CLOSE_EVT  ) {
    Serial.println("Client disconnected");
  }
  else if (event == ESP_SPP_DATA_IND_EVT ) {
    Serial.println("Data received");
    while (pBtSerial->available()) {
      int incoming = pBtSerial->read();
      Serial.println(incoming);
    }
  }
}


CPBluetooth::CPBluetooth(): macAddress("") {
  pBtSerial = &(this->btSerial);
}

void CPBluetooth::init() {
  btSerial.begin("ESP32-BT");
  btSerial.register_callback(bt_event_handler); // Attach The CallBack Function Definition To S

  delay(500);
  macAddress = btSerial.getBtAddressString();
  Serial.println("bt mac: " + macAddress);
}


void CPBluetooth::connect(String slave, String pin) {
  if (pin.length() > 0) {
    btSerial.setPin(pin.c_str());
    btSerial.println("Using PIN");
  }

  // connected = SerialBT.connect(SlaveAddress);  // Or MAC Address
  if (btSerial.connect(slave)) {
    Serial.println("connected to: " + slave);
  } else {
    Serial.println("failed to connect: " + slave);
    while(!btSerial.connected(10)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
}

void CPBluetooth::connect(uint8_t remoteAddress[], String pin) {
  if (pin.length() > 0) {
    btSerial.setPin(pin.c_str());
    btSerial.println("Using PIN");
  }

  // connected = SerialBT.connect(SlaveAddress);  // Or MAC Address
  if (btSerial.connect(remoteAddress)) {
    Serial.println("connected success");
  } else {
    Serial.println("failed to connect");
    /*
    while(!btSerial.connected(10)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
    */
  }
}

void CPBluetooth::disconnect() {
  // Disconnect() may take up to 10 secs max
  if (btSerial.disconnect()) {
    // Disconnected Successfully!
    Serial.println("disconnected success");
  }
}

void CPBluetooth::discover() {
  Serial.println("Starting discover...");
  BTScanResults *pResults = btSerial.discover(BT_DISCOVER_TIME);
  if (pResults)
    pResults->dump(&Serial);
  else
    Serial.println("Error on BT Scan, no result!");
}

void CPBluetooth::loop() {
  if (Serial.available()) {
    btSerial.write(Serial.read());
  } else if (btSerial.available()) {
    Serial.write(btSerial.read());
  }
}

void CPBluetooth::write(String data) {
  btSerial.write((const uint8_t*)data.c_str(), data.length());
}

bool CPBluetooth::isConnected() {
  return !btSerial.isClosed();
}
