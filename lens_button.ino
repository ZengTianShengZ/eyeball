extern void lens_light_sensor_state_change();
extern void tof050c_get_current_value();
extern bool lens_light_sensor_running_state;

const int lens_button_pin = 3;       // 按钮引脚
int lens_button_state = HIGH;         // 当前按钮状态
int lens_button_last_state = HIGH;     // 上次按钮状态

// 短按和长按相关变量
unsigned long lens_button_press_start_time = 0;  // 按钮按下开始时间
bool lens_button_is_pressed = false;             // 按钮是否正在被按下
const unsigned long DEBOUNCE_TIME = 50;           // 防抖时间阈值（毫秒），小于此时间的按下视为干扰
const unsigned long LONG_PRESS_TIME = 1000;       // 长按时间阈值（毫秒），大于等于此时间为长按

void lens_button_init() {
  // 设置按钮引脚为输入，启用内部上拉电阻
  pinMode(lens_button_pin, INPUT_PULLUP);
  Serial.println("Button_lens press detection initialized.");
}

void lens_button_run() {
  // 读取按钮的当前状态
  lens_button_state = digitalRead(lens_button_pin);

  // 检测按钮按下的边沿（从 HIGH -> LOW）
  if (lens_button_state == LOW && lens_button_last_state == HIGH) {
    // 按钮刚被按下，记录按下时间
    lens_button_press_start_time = millis();
    lens_button_is_pressed = true;
  }

  // 检测按钮释放的边沿（从 LOW -> HIGH）
  if (lens_button_state == HIGH && lens_button_last_state == LOW) {
    // 按钮被释放，计算按下时长
    if (lens_button_is_pressed) {
      unsigned long press_duration = millis() - lens_button_press_start_time;
      lens_button_is_pressed = false;

      // 防抖：如果按下时间太短，可能是干扰，忽略
      if (press_duration < DEBOUNCE_TIME) {
        return;
      }

      // 根据按下时长判断是短按还是长按
      if (press_duration >= LONG_PRESS_TIME) {
        // 长按（>= 1000ms）
        lens_button_long_press();
      } else {
        // 短按（50ms - 999ms）
        lens_button_short_press();
      }
    }
  }

  // 更新按钮状态
  lens_button_last_state = lens_button_state;
}

void lens_button_short_press() {
  Serial.println("Button_lens short press!");

  // 如果光敏传感器正在运行，则停止光敏传感器
  if (lens_light_sensor_running_state) {
    lens_light_sensor_stop();
    return;
  } 
  
  // 获取当前TOF传感器值
  tof050c_get_current_value();
}

void lens_button_long_press() {
  Serial.println("Button_lens long press!");  
  lens_light_sensor_state_change();
}