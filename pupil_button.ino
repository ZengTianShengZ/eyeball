extern void pupil_light_sensor_state_change();

const int pupil_button_pin = 2;       // 按钮引脚
int pupil_button_state = HIGH;         // 当前按钮状态
int pupil_button_last_state = HIGH;     // 上次按钮状态

void pupil_button_init() {
  // 设置按钮引脚为输入，启用内部上拉电阻
  pinMode(pupil_button_pin, INPUT_PULLUP);
  Serial.println("Button_pupil press detection initialized.");
}

void pupil_button_run() {
  // 读取按钮的当前状态
  pupil_button_state = digitalRead(pupil_button_pin);

  // 检测按钮按下的边沿（从 HIGH -> LOW）
  if (pupil_button_state == LOW && pupil_button_last_state == HIGH) {
    pupil_button_pressed_on();
    delay(200);  // 防抖延迟，确保按钮按下后信号稳定
  }

  // 更新按钮状态
  pupil_button_last_state = pupil_button_state;
}

void pupil_button_pressed_on() {
  Serial.println("Button_pupil pressed!");
  pupil_light_sensor_state_change();
}