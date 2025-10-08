extern void lens_light_sensor_state_change();

const int lens_button_pin = 3;       // 按钮引脚
int lens_button_state = HIGH;         // 当前按钮状态
int lens_button_last_state = HIGH;     // 上次按钮状态

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
    lens_button_pressed_on();
    delay(200);  // 防抖延迟，确保按钮按下后信号稳定
  }

  // 更新按钮状态
  lens_button_last_state = lens_button_state;
}

void lens_button_pressed_on() {
  Serial.println("Button_lens pressed!");
  lens_light_sensor_state_change();
}