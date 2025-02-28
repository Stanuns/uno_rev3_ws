#include <IRremote.h> //IRremote 4.4.1
#define RECV_PIN_1 2
#define RECV_PIN_2 3
IRrecv irReceiver1(RECV_PIN_1);
IRrecv irReceiver2(RECV_PIN_2);

void setup() {
  Serial.begin(9600);
  // irReceiver1.begin(RECV_PIN_1, true); // 仅保留必要参数
  irReceiver1.enableIRIn(); // 仅保留必要参数
  // delay(1000);
  irReceiver2.enableIRIn(); // 仅保留必要参数
  delay(1000);
  Serial.println("--------IR Ready-------"); 
}

void loop() {
  // Serial.println("------------------------- ");
  if (irReceiver1.decode()) {
    Serial.print("Receiver1 ");
    Serial.print(irReceiver1.decodedIRData.protocol);
    Serial.print(" 地址码: 0x");
    Serial.print(irReceiver1.decodedIRData.address, HEX);
    Serial.print(" 命令码: 0x");
    Serial.println(irReceiver1.decodedIRData.command, HEX);
    delay(50);
    irReceiver1.resume();
  }

  if (irReceiver2.decode()) {
    Serial.print("Receiver2 ");
    Serial.print(irReceiver2.decodedIRData.protocol);
    Serial.print(" 地址码: 0x");
    Serial.print(irReceiver2.decodedIRData.address, HEX);
    Serial.print(" 命令码: 0x");
    Serial.println(irReceiver2.decodedIRData.command, HEX);
    delay(50);
    irReceiver2.resume();
  }
}