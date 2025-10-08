extern void lens_motor_run_state_change();

// 定义引脚
const int lens_light_sensor_DO = A0;    // 光敏模块DO数字引脚连接 A0

bool lens_light_sensor_running_state = false; // 是否开启光敏传感器
bool lens_light_sensor_last_num = 0;  // 初始值

void lens_light_sensor_init() {  
  pinMode(lens_light_sensor_DO, INPUT);
  lens_light_sensor_running_state = false;
  lens_light_sensor_last_num = analogRead(lens_light_sensor_DO); // 初始化为当前状态
  Serial.println("光敏传感器_lens DO控制程序启动");
}

/**
改变光敏传感器的状态
*/
void lens_light_sensor_state_change() {
  Serial.println("光敏传感器_lens 状态改变");
  lens_light_sensor_running_state = !lens_light_sensor_running_state;
}

void lens_light_sensor_run() {
  if (!lens_light_sensor_running_state) {
    return;
  }

  int lens_light_sensor_num = analogRead(lens_light_sensor_DO);

  if (lens_light_sensor_num - lens_light_sensor_last_num > 10) {
    lens_motor_run_state_change(HIGH);
  } else {
    lens_motor_run_state_change(LOW);
  }

  lens_light_sensor_last_num = lens_light_sensor_num;
 
  Serial.println("光敏传感器_lens 数值: " + String(lens_light_sensor_num));
  delay(1000);

}
