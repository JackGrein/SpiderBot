#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//#include <SoftwareSerial.h>

//SoftwareSerial Bluetooth(12, 9); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

float distance;
long duration;
int dataIn;
int dataIn1;
int dataIn2;
int m = 0;
int h = 0;
int t = 0;
int speedV = 30;

bool togglem = false;
int n = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(2, OUTPUT); // Red Color LED
  pinMode(25, OUTPUT); // Green Color LED
  pinMode(14, OUTPUT); // Blue Color LED
  digitalWrite(2, LOW);    // switch off LED pins
  digitalWrite(25, LOW);
  digitalWrite(14, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  if (Serial.available()) {
  SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
  Serial.write(SerialBT.read());
  }
  */
  delay(20);

  // Check for incoming data
  if (SerialBT.available()) {
    dataIn1 = SerialBT.read();  // Read the data
    /*
    Serial.println(dataIn1);
    Serial.println(m);
    */
  }

  if (dataIn1 == 49) {
    m = 0;
    digitalWrite(25, LOW);
  }
  if (dataIn1 == 50) {
    m = 1;
    digitalWrite(14, HIGH);
  }
  if (dataIn1 == 51) {
    m = 2;
    digitalWrite(25, HIGH);
  }
  if (dataIn1 == 52) {
    m = 5;
    digitalWrite(2, HIGH);
  }
  if (dataIn1 == 53) {
    m = 6;
    digitalWrite(14, LOW);
  }
  if (dataIn1 == 54) {
    m = 7;
    digitalWrite(2, LOW);
  }

  //Sending data to servo contrl
  if (m == 0) {
    if (togglem == true) {
      n = 0;
    }
  }
  else if (m == 1) {
    if ((togglem == true) && (n == 1)) {
      togglem = false;
    }
    else {
      togglem = true;
    }
    n = 1;
  }
  else if (m == 2) {
    if ((togglem == true) && (n == 2)) {
      togglem = false;
    }
    else {
      togglem = true;
    }
    n = 2;
  }
  else if (m == 5) {
    if ((togglem == true) && (n == 5)) {
      togglem = false;
    }
    else {
      togglem = true;
    }
    n = 5;
  }
  else if (m == 6) {
    if ((togglem == true) && (n == 6)) {
      togglem = false;
    }
    else {
      togglem = true;
    }
    n = 6;
  }
  else if (m == 3) {
    if ((togglem == true) && (n == 3)) {
      togglem = false;
    }
    else {
      togglem = true;
    }
    n = 3;
  }

  //Info for contr
  Serial.println(n);

  //Data from servo control
  if (Serial.available() >= 0) {
    char receivedData = Serial.read();
    if (receivedData == '1'){
      //Serial1.println('1');
      digitalWrite(12, HIGH);
      //Serial.println("LEDS ON");
    }
    else if (receivedData == '0'){
      Serial.println('0');
      digitalWrite(12, LOW);
      //Serial.print("LEDS OFF");
    }
  }
}
