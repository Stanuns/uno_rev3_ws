#include <IRremote.h> //IRremote 4.4.1
// #define IR_SEND_PIN_1 3
// #define IR_SEND_PIN_2 5
#define IR_SEND_PIN_3 7

// IRsend irsend1(IR_SEND_PIN_1);
// IRsend irsend2(IR_SEND_PIN_2);
IRsend irsend3(IR_SEND_PIN_3);

void setup(){
  // 启动发送，并指定引脚；开启Arduino主板LED灯反馈；
  // irsend1.begin(ENABLE_LED_FEEDBACK);
  // irsend2.begin(ENABLE_LED_FEEDBACK);
  // irsend3.begin(ENABLE_LED_FEEDBACK);
}

void loop(){
  // 发送红外编码值
  // irsend1.sendNEC(0xFF30,0x01,0);
  // delay(2);
  // irsend2.sendNEC(0xFF50,0x02,0);
  // delay(2);
  irsend3.sendNEC(0xFF70,0x03,0);
  delay(100);
}