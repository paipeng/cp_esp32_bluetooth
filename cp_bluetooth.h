#ifndef _CP_BLUETOOTH_H_
#define _CP_BLUETOOTH_H_

#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


class CPBluetooth {
public:
  CPBluetooth();
  void init();
  // slave name or mac address
  void connect(String slave, String pin = "");
  void connect(uint8_t remoteAddress[], String pin = "");
  void disconnect();
  void discover();
  void loop();
  void write(String data);
  bool isConnected();

private:
  BluetoothSerial btSerial;
  String macAddress;
};

#endif