// 定义 LED 引脚
const int ledPin = 9;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  
  // 设置 LED 引脚为输出
  pinMode(ledPin, OUTPUT);
  // 将 LED 设置为默认的最低亮度
  analogWrite(ledPin, 255);
}

void loop() {
  if (Serial.available() > 0) {
    // 读取串口输入
    int brightness = Serial.parseInt(); // 解析连续的数据
    Serial.println(brightness);
    
    // 将亮度值限制在 0 到 255 之间
    brightness = constrain(brightness, 0, 255);
    
    // 设置 PWM 占空比
    analogWrite(ledPin, brightness);
  }
  
}
