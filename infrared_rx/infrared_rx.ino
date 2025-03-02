#include <IRremote.h>  // IRremote 4.4.1

#define IR_RECEIVE_PIN_1 9 // 红外接收模块信号引脚
// #define IR_RECEIVE_PIN_2 5  
// #define IR_RECEIVE_PIN_3 13

IRrecv irReceiver1(IR_RECEIVE_PIN_1);
// IRrecv irReceiver2(IR_RECEIVE_PIN_2);
// IRrecv irReceiver3(IR_RECEIVE_PIN_3);

void setup() {
  Serial.begin(9600);         // 初始化串口
  // IrReceiver.begin(IR_RECEIVE_PIN_1, ENABLE_LED_FEEDBACK);  // 启动接收，启用板载LED反馈
  irReceiver1.enableIRIn();  // 初始化三个接收器
  // irReceiver2.enableIRIn();
  // irReceiver3.enableIRIn();
  // Serial.println("intrared receiver has started, waiting signal...");
}

void loop() {
  // printIRInfo();
  sendIRData();
  delay(100);
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

// 计算CRC16校验（MODBUS参数）
uint16_t calculateCRC(uint8_t *data, uint16_t length) {
  uint16_t crc = 0xFFFF;
  for (uint16_t i = 0; i < length; i++) {
    crc ^= data[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 1) {
        crc = (crc >> 1) ^ 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

void sendIRData() {
  uint8_t cmd1 = 0;
  // uint8_t cmd2 = 0;
  uint8_t functionCode = 0X00;

  // 处理第一个接收器
  if (irReceiver1.decode()) {
    if (irReceiver1.decodedIRData.protocol == NEC) {
      cmd1 = irReceiver1.decodedIRData.command;
      functionCode = 0x02;
      Serial.print("cmd1值:");
      Serial.println(cmd1, HEX);
    }
  }
  irReceiver1.resume();

  // if (irReceiver2.decode()) {
  //   if (irReceiver2.decodedIRData.protocol == NEC) {
  //     cmd2 = irReceiver2.decodedIRData.command;
  //     functionCode = 0x02;
  //     Serial.print("cmd2值:");
  //     Serial.println(cmd2, HEX);
  //   }
  // }
  // irReceiver2.resume();

  // 构建核心数据（协议+原始数据32位）
  uint8_t coreData[1] = {cmd1};

  // 构建CRC计算数据（功能码+核心数据）
  uint8_t crcData[2] = {
    functionCode,
    coreData[0]
  };

  // 计算CRC
  uint16_t crc = calculateCRC(crcData, sizeof(crcData));
  uint8_t crcLow = crc & 0xFF;
  uint8_t crcHigh = (crc >> 8) & 0xFF;

  // 构建完整报文
  uint8_t packet[] = {
    0xFF, 0xFE,               // 帧头
    sizeof(crcData) + 2,      // 数据长度（功能码+核心数据+CRC）
    functionCode,             // 功能码
    coreData[0],  // 核心数据（1）
    crcLow,           // CRC低字节
    crcHigh,          // CRC高字节
    0x00                      // 帧尾
  };

  // 发送报文
  Serial.write(packet, sizeof(packet));
  delay(10);
  //degug
  // Serial.println("\n--- 红外信号解码结果 ---");
  // Serial.println(cmd1, HEX);
  // Serial.println(cmd2, HEX);
  // Serial.println(cmd3, HEX);
}