// 眼球控制主程序 - eyeball.ino
// 使用 MotorController.ino 作为电机控制库

// 定义引脚
const int buttonPin = 2;      // 按钮连接的引脚
const int controlPinA = 3;    // 控制电平引脚A

// 控制变量
int lastControlState = LOW;  // 上次控制引脚状态

void setup() {
   // 初始化引脚模式
   pinMode(buttonPin, INPUT_PULLUP);
   pinMode(controlPinA, INPUT);
   
   // 初始化电机
   initMotor();
   
   initOLED();


   // 初始化串口用于调试（可选）
   Serial.begin(9600);
}

void loop() {
  // 读取按钮状态和控制引脚状态
  int buttonState = digitalRead(buttonPin);
  int controlState = digitalRead(controlPinA);
  
  // 如果按钮按下
  if (buttonState == LOW) {
    // 检测控制引脚状态变化
    if (controlState != lastControlState) {
      // 设置目标方向
      int newDirection = (controlState == HIGH) ? 1 : -1;
      setTargetDirection(newDirection);
      lastControlState = controlState;
    }
    
    // 更新电机状态
    updateMotor();
    
    // 控制电机速度
    delay(getStepDelay());
  } else {
    // 按钮未按下，停止电机
    if (isMotorRunning()) {
      stopMotor();
      Serial.println("电机停止");
    }
  }

  // showOLED();
}