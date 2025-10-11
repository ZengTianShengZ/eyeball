extern void pupil_motor_run_state_change();

// 定义引脚
const int pupil_light_sensor_DO = A1;    // 光敏模块DO引脚连接 A1

bool pupil_light_sensor_running_state = false; // 是否开启光敏传感器
bool pupil_light_sensor_last_state = HIGH;  // 初始值设为 HIGH（无光）

void pupil_light_sensor_init() {  
  pinMode(pupil_light_sensor_DO, INPUT);
  pupil_light_sensor_running_state = false;
  pupil_light_sensor_last_state = digitalRead(pupil_light_sensor_DO); // 初始化为当前状态
  Serial.println("光敏传感器_pupil DO控制程序启动");
}

void pupil_light_sensor_run() {
  if (!pupil_light_sensor_running_state) {
    return;
  }

  int pupil_light_sensor_num = digitalRead(pupil_light_sensor_DO);

  // 只有状态变化时才打印
  if (pupil_light_sensor_num != pupil_light_sensor_last_state) {
    if (pupil_light_sensor_num == HIGH) {
      pupil_motor_run_state_change(HIGH);
    } else {
      pupil_motor_run_state_change(LOW);
    }
    pupil_light_sensor_last_state = pupil_light_sensor_num; // 更新上次状态
  }
}

/**
改变光敏传感器的状态
*/
void pupil_light_sensor_state_change() {
  Serial.println("光敏传感器_pupil 状态改变");
  pupil_light_sensor_running_state = !pupil_light_sensor_running_state;
}