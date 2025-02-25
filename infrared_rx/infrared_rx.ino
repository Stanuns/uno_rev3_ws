#include <IRremote.h>  // 使用v3.x以上版本的IRremote库

#define IR_RECEIVE_PIN 11  // 红外接收模块信号引脚（如VS1838B）

void setup() {
  Serial.begin(9600);         // 初始化串口
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // 启动接收，启用板载LED反馈
  Serial.println("红外接收器已启动，等待信号...");
}

void loop() {
  if (IrReceiver.decode()) {  // 检测是否收到信号
    printIRInfo();            // 打印解码信息
    IrReceiver.resume();      // 继续接收下一个信号
  }
  delay(100);  // 降低CPU负载
}

// 自定义函数：打印红外信号详细信息
void printIRInfo() {
  Serial.println("\n--- 红外信号解码结果 ---");
  
  // 1. 协议类型
  Serial.print("协议: ");
  switch (IrReceiver.decodedIRData.protocol) {
    case NEC: Serial.println("NEC"); break;
    case SONY: Serial.println("SONY"); break;
    case RC5: Serial.println("RC5"); break;
    case RC6: Serial.println("RC6"); break;
    case UNKNOWN: Serial.println("未知协议"); break;
    default: Serial.println("其他协议"); break;
  }

  // 2. 原始数据值（HEX格式）
  Serial.print("数据值 (HEX): 0x");
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  // 3. NEC协议解析（地址码和命令码）
  if (IrReceiver.decodedIRData.protocol == NEC) {
    Serial.print("地址码: 0x");
    Serial.println(IrReceiver.decodedIRData.address, HEX);
    Serial.print("命令码: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
  }

  Serial.println("------------------------");
}