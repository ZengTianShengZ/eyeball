extern int lens_motor_run_state_change_count;
extern void lens_motor_stop();

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
  lens_light_sensor_last_num = lens_light_sensor_num_max; // 初始化为当前状态
  lens_motor_run_state_change_count = 0;
  lens_light_sensor_running_state = !lens_light_sensor_running_state;
}

void lens_light_sensor_run() {
  if (!lens_light_sensor_running_state) {
    return;
  }

  int lens_light_sensor_num = analogRead(lens_light_sensor_DO);

  // 如果当前数值小于等于最后数值，且大于10，则更新最后数值
  if ((lens_light_sensor_num <= lens_light_sensor_last_num) && lens_light_sensor_num > 10) {
    lens_light_sensor_last_num = lens_light_sensor_num;
  }

  int difference = abs(lens_light_sensor_num - lens_light_sensor_last_num);

  Serial.println(lens_motor_run_state_change_count);
  Serial.println(difference);
  if (lens_motor_run_state_change_count >= 2 &&  difference < 10) {
    lens_light_sensor_running_state = false;
    lens_light_sensor_last_num = lens_light_sensor_num_max;
    lens_motor_stop();
  }

  if (lens_motor_run_state_change_count >= 3 &&  difference < 20) {
    lens_light_sensor_running_state = false;
    lens_motor_stop();
    lens_light_sensor_last_num = lens_light_sensor_num_max;
  }

  if (lens_motor_run_state_change_count >= 4 &&  difference < 50) {
    lens_light_sensor_running_state = false;
    lens_motor_stop();
    lens_light_sensor_last_num = lens_light_sensor_num_max;
  }
  
  if (lens_motor_run_state_change_count >= 5 &&  difference < 100) {
    lens_light_sensor_running_state = false;
    lens_motor_stop();
    lens_light_sensor_last_num = lens_light_sensor_num_max;
  }
}
