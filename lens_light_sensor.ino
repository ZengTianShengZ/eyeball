extern int lens_motor_run_state_change_count;

// 定义引脚
const int lens_light_sensor_DO = A0;    // 光敏模块DO数字引脚连接 A0

bool lens_light_sensor_running_state = false; // 是否开启光敏传感器
int lens_light_sensor_last_num = 2000;  // 初始值

unsigned long lens_light_sensor_last_detection_time = 0;
const unsigned long lens_light_sensor_detection_grace_period = 500; // 宽限时间（毫秒）


void lens_light_sensor_init() {  
  pinMode(lens_light_sensor_DO, INPUT);
  lens_light_sensor_running_state = false;
  lens_light_sensor_last_num = 2000; // 初始化为当前状态
  Serial.println("光敏传感器_lens DO控制程序启动");
}

/**
改变光敏传感器的状态
*/
void lens_light_sensor_state_change() {
  Serial.println("光敏传感器_lens 状态改变");
  lens_light_sensor_last_num = 2000; // 初始化为当前状态
  lens_motor_run_state_change_count = 0;
  lens_light_sensor_running_state = !lens_light_sensor_running_state;
}

void lens_light_sensor_run() {
  if (!lens_light_sensor_running_state) {
    return;
  }

  // unsigned long now = millis();

  // if (now - lens_light_sensor_last_detection_time < lens_light_sensor_detection_grace_period) {
  //   return;
  // }

  int lens_light_sensor_num = analogRead(lens_light_sensor_DO);

  if ((lens_light_sensor_num <= lens_light_sensor_last_num) && lens_light_sensor_num > 10) {

    lens_light_sensor_last_num = lens_light_sensor_num;

  }

  int difference = abs(lens_light_sensor_num - lens_light_sensor_last_num);

  Serial.println("光敏传感器_lens 次数>>>: " + String(lens_motor_run_state_change_count));
  Serial.println("光敏传感器_lens 当前数值>>>: " + String(lens_light_sensor_num) + "  最后数值>>>: " + String(lens_light_sensor_last_num));
  Serial.println("光敏传感器_lens 数值差异>>>: " + String(difference));
  if (lens_motor_run_state_change_count > 1 &&  difference < 5) {
    Serial.println("光敏传感器_lens 最后数值 ++++++++++: " + String(lens_light_sensor_last_num));
    lens_light_sensor_running_state = false;
  }

 

}
