// 电机控制库 - MotorController.ino
// 用于控制两个步进电机的同步运行

// 定义引脚
const int motorPin1 = 8;      // 步进电机1引脚1
const int motorPin2 = 9;      // 步进电机1引脚2
const int motorPin3 = 10;     // 步进电机1引脚3
const int motorPin4 = 11;     // 步进电机1引脚4

const int motor2Pin1 = 4;     // 步进电机2引脚1
const int motor2Pin2 = 5;     // 步进电机2引脚2
const int motor2Pin3 = 6;     // 步进电机2引脚3
const int motor2Pin4 = 7;     // 步进电机2引脚4

// 步进电机步序（改进的半步序列，运行更平滑）
const int steps[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

// 电机控制变量
int stepDelay = 3;           // 步进延迟时间(毫秒)
int currentStep = 0;         // 当前步序
int direction = 1;           // 转动方向: 1=正转, -1=反转
int targetDirection = 1;     // 目标方向
bool directionChanging = false; // 方向是否正在改变
unsigned long directionChangeStartTime = 0; // 方向改变开始时间
const unsigned long DIRECTION_CHANGE_DELAY = 1000; // 方向改变延迟时间(毫秒)

// 初始化电机
void initMotor() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  
  // 初始状态所有电机引脚置低
  stopMotor();
}

// 设置目标方向
void setTargetDirection(int newDirection) {
  targetDirection = newDirection;
  
  // 如果方向确实需要改变
  if (targetDirection != direction) {
    directionChanging = true;
    directionChangeStartTime = millis(); // 记录开始时间
    Serial.print("开始方向改变: ");
    Serial.println(targetDirection == 1 ? "正转" : "反转");
  }
}

// 更新电机状态
void updateMotor() {
  // 处理方向改变
  if (directionChanging) {
    handleDirectionChange();
    return; // 方向改变期间不执行步进
  }
  
  // 执行步进
  stepMotor(currentStep);
  
  // 更新步序
  currentStep += direction;
  
  // 处理步序循环
  if (currentStep >= 8) currentStep = 0;
  if (currentStep < 0) currentStep = 7;
}

// 处理方向改变，立即停止然后延迟1秒
void handleDirectionChange() {
  // 立即停止电机
  stopMotor();
  
  // 检查是否已经延迟了足够时间
  if (millis() - directionChangeStartTime >= DIRECTION_CHANGE_DELAY) {
    // 延迟时间到，改变方向
    direction = targetDirection;
    directionChanging = false;
    Serial.print("方向已改变为: ");
    Serial.println(direction == 1 ? "正转" : "反转");
    Serial.println("方向改变完成");
  }
}

// 执行一步电机转动
void stepMotor(int step) {
  // 控制第一个步进电机
  digitalWrite(motorPin1, steps[step][0]);
  digitalWrite(motorPin2, steps[step][1]);
  digitalWrite(motorPin3, steps[step][2]);
  digitalWrite(motorPin4, steps[step][3]);
  
  // 控制第二个步进电机（同步运行）
  digitalWrite(motor2Pin1, steps[step][0]);
  digitalWrite(motor2Pin2, steps[step][1]);
  digitalWrite(motor2Pin3, steps[step][2]);
  digitalWrite(motor2Pin4, steps[step][3]);
}

// 停止电机
void stopMotor() {
  // 停止第一个步进电机
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  
  // 停止第二个步进电机
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
}

// 获取当前步进延迟时间
int getStepDelay() {
  return stepDelay;
}

// 检查电机是否正在运行
bool isMotorRunning() {
  return digitalRead(motorPin1) || digitalRead(motorPin2) || 
         digitalRead(motorPin3) || digitalRead(motorPin4);
}