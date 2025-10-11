extern int lens_motor_run_state_change_count;
extern void lens_motor_stop();
extern void oled_show_init();
extern void oled_show_t();

// 定义引脚
const int lens_light_sensor_DO = A0;    // 光敏模块DO数字引脚连接 A0

const int lens_light_sensor_num_max = 2000;
bool lens_light_sensor_running_state = false; // 是否开启光敏传感器
int lens_light_sensor_last_num = lens_light_sensor_num_max;  // 初始值

void lens_light_sensor_init() {  
  pinMode(lens_light_sensor_DO, INPUT);
  lens_light_sensor_running_state = false;
  lens_light_sensor_last_num = lens_light_sensor_num_max; // 初始化为当前状态
  Serial.println("光敏传感器_lens DO控制程序启动");
}

/**
改变光敏传感器的状态
*/
void lens_light_sensor_state_change() {
  Serial.println("光敏传感器_lens 状态改变");
  oled_show_init();
  lens_light_sensor_last_num = lens_light_sensor_num_max; // 初始化为当前状态
  lens_motor_run_state_change_count = 0;
  lens_light_sensor_running_state = !lens_light_sensor_running_state;
}

void lens_light_sensor_stop() {
  lens_light_sensor_running_state = false;
  lens_motor_stop();
  lens_light_sensor_last_num = lens_light_sensor_num_max;
}

void lens_light_sensor_run() {
  if (!lens_light_sensor_running_state) {
    return;
  }

  int lens_light_sensor_num = analogRead(lens_light_sensor_DO);

  // 如果当前数值小于等于最后数值，且大于10，则更新最后数值，且电机运行状态改变次数大于等于1（防止首次启动光敏电阻记录的数值有误）
  if ((lens_light_sensor_num <= lens_light_sensor_last_num) 
      && lens_light_sensor_num > 10 
      && lens_motor_run_state_change_count >= 1) {
    lens_light_sensor_last_num = lens_light_sensor_num;
  }

  int difference = abs(lens_light_sensor_num - lens_light_sensor_last_num);

  Serial.println(lens_motor_run_state_change_count);
  Serial.println(lens_light_sensor_num);
  Serial.println(lens_light_sensor_last_num);
  Serial.println(difference);
  if (lens_motor_run_state_change_count >= 2 &&  difference < 4) {
    lens_light_sensor_stop();
    oled_show_t();
  }

  if (lens_motor_run_state_change_count >= 3 &&  difference < 8) {
    lens_light_sensor_stop();
    oled_show_t();
  }

  if (lens_motor_run_state_change_count >= 4 &&  difference < 15) {
    lens_light_sensor_stop();
    oled_show_t();
  }
  
  if (lens_motor_run_state_change_count >= 5 &&  difference < 30) {
    lens_light_sensor_stop();
    oled_show_t();
  }

  if (lens_motor_run_state_change_count >= 6) {
    lens_light_sensor_stop();
  }
}
