// 定义引脚
const int lightSensorDO = 2;    // 光敏模块DO引脚连接数字引脚2
const int ledPin = 13;          // LED连接数字引脚13（板载LED）

// 变量存储状态
int lightState = 0;             // 存储光敏传感器状态
int lastLightState = -1;        // 存储上一次的光线状态
unsigned long lastOutputTime = 0; // 上次串口输出的时间
const unsigned long OUTPUT_INTERVAL = 1000; // 串口输出间隔（毫秒）

void initLightSensor() {  
  // 设置光敏传感器DO引脚为输入模式
  pinMode(lightSensorDO, INPUT);
  // 设置LED引脚为输出模式
  pinMode(ledPin, OUTPUT);
  Serial.println("光敏传感器DO控制程序启动");
}

void showLightSensor() {
  // 读取数字输出引脚状态
  lightState = digitalRead(lightSensorDO);
  
  // 根据光线状态控制LED
  if (lightState == LOW) {
    // 光线较暗时（DO输出LOW），点亮LED
    digitalWrite(ledPin, HIGH);
  } else {
    // 光线充足时（DO输出HIGH），熄灭LED
    digitalWrite(ledPin, LOW);
  }
  
  // 只在状态改变或达到输出间隔时才输出串口信息
  unsigned long currentTime = millis();
  if (lightState != lastLightState || 
      (currentTime - lastOutputTime >= OUTPUT_INTERVAL)) {
    
    if (lightState == LOW) {
      Serial.println("状态：光线不足 - LED亮起");
    } else {
      Serial.println("状态：光线充足 - LED熄灭");
    }
    
    lastOutputTime = currentTime;
    lastLightState = lightState;
  }
}