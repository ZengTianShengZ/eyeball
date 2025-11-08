extern int lens_motor_run_state_change_count;
extern unsigned long lens_motor_run_state_change_time;
extern void lens_motor_stop();
extern void oled_show_init();
extern void oled_show_t();
extern int tof050c_getRange();

// 定义引脚
const int lens_light_sensor_DO = A0;    // 光敏模块DO数字引脚连接 A0

const int lens_light_sensor_num_max = 2000;
bool lens_light_sensor_running_state = false; // 是否开启光敏传感器
int lens_light_sensor_last_num = lens_light_sensor_num_max;  // 初始值

// 滤波相关参数
const float lens_light_sensor_filter_alpha = 0.3;  // 滤波系数 (0.0-1.0)，越小越平滑但响应越慢
int lens_light_sensor_filtered_num = lens_light_sensor_num_max;  // 滤波后的数值

void lens_light_sensor_init() {  
  pinMode(lens_light_sensor_DO, INPUT);
  lens_light_sensor_running_state = false;
  lens_light_sensor_last_num = lens_light_sensor_num_max; // 初始化为当前状态
  lens_light_sensor_filtered_num = lens_light_sensor_num_max; // 初始化滤波值
  Serial.println("光敏传感器_lens DO控制程序启动");
}

/**
改变光敏传感器的状态
*/
void lens_light_sensor_state_change() {
  Serial.println("光敏传感器_lens 状态改变");
  oled_show_init();
  lens_light_sensor_last_num = lens_light_sensor_num_max; // 初始化为当前状态
  lens_light_sensor_filtered_num = lens_light_sensor_num_max; // 重置滤波值
  lens_light_sensor_running_state = !lens_light_sensor_running_state;
}

void lens_light_sensor_stop() {
  lens_light_sensor_running_state = false;
  lens_motor_stop();
  lens_light_sensor_last_num = lens_light_sensor_num_max;
  lens_light_sensor_filtered_num = lens_light_sensor_num_max;
}

void lens_light_sensor_run() {
  if (!lens_light_sensor_running_state) {
    return;
  }

  // 读取原始传感器值
  int lens_light_sensor_raw = analogRead(lens_light_sensor_DO);
  
  // 使用低通滤波器平滑数据: filtered = alpha * raw + (1-alpha) * filtered_prev
  lens_light_sensor_filtered_num = (int)(lens_light_sensor_filter_alpha * lens_light_sensor_raw + 
                                         (1.0 - lens_light_sensor_filter_alpha) * lens_light_sensor_filtered_num);
  
  // 使用滤波后的数值进行后续处理
  int lens_light_sensor_num = lens_light_sensor_filtered_num;

  // 如果当前数值小于等于最后数值，且大于10，则更新最后数值，且电机运行状态改变次数大于等于1（防止首次启动光敏电阻记录的数值有误）
  if ((lens_light_sensor_num <= lens_light_sensor_last_num) 
      && lens_light_sensor_num > 10 
      && lens_motor_run_state_change_count >= 1) {
    lens_light_sensor_last_num = lens_light_sensor_num;
  }

  
  if ( lens_motor_run_state_change_count >=1 && (millis() - lens_motor_run_state_change_time) > 2000) {
    if (lens_light_sensor_num - lens_light_sensor_last_num  > 5) {
      lens_light_sensor_stop();
      oled_show_t();
    }
  }
}
