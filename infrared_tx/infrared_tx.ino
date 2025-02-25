#include <IRremote.h>
#define IR_SEND_PIN_1 3
#define IR_SEND_PIN_2 5
#define IR_SEND_PIN_3 7

IRsend irsend1(IR_SEND_PIN_1);
IRsend irsend2(IR_SEND_PIN_2);
IRsend irsend3(IR_SEND_PIN_3);

void setup(){
  // 启动发送，并指定引脚；开启Arduino主板L灯反馈；
  IrSender.begin(IR_SEND_PIN_1, DISABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN_2, DISABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN_3, DISABLE_LED_FEEDBACK);
}

void loop(){
  // 发送红外编码值
  irsend1.sendNEC(0xFF00,0x33,0);
  delay(16);
  irsend2.sendNEC(0xFF00,0x55,0);
  delay(16);
  irsend3.sendNEC(0xFF00,0x77,0);
  delay(16);
}