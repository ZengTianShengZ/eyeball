extern bool motor2_running_state;
extern bool motor2_clockwise;

// 定义引脚
const int lightSensor2_DO = A1;    // 光敏模块DO引脚连接 A1

bool lightSensor2_running_state = false;
bool lightSensor2_last_state = HIGH;  // 初始值设为 HIGH（无光）

void light_sensor2_init() {  
  pinMode(lightSensor2_DO, INPUT);
  lightSensor2_running_state = false;
  lightSensor2_last_state = digitalRead(lightSensor2_DO); // 初始化为当前状态
  Serial.println("光敏传感器2 DO控制程序启动");
}

void lightSensor2_run() {
  if (!lightSensor2_running_state) {
    return;
  }

  int lightSensor2_num = digitalRead(lightSensor2_DO);

  // 只有状态变化时才打印
  if (lightSensor2_num != lightSensor2_last_state) {
    if (lightSensor2_num == HIGH) {
      Serial.println("光敏传感器2 无光照");
      motor2_running_state = true;
      motor2_clockwise = false;
    } else {
      Serial.println("光敏传感器2 有光照");
      motor2_running_state = true;
      motor2_clockwise = true;
    }
    lightSensor2_last_state = lightSensor2_num; // 更新上次状态
  }
}
