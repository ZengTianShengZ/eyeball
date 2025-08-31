extern bool motor2_running_state;
extern bool lightSensor2_running_state;

const int button2_pin = 2;       // 按钮引脚
int button2_state = HIGH;         // 当前按钮状态
int button2_last_state = HIGH;     // 上次按钮状态

void button2_init() {
  // 设置按钮引脚为输入，启用内部上拉电阻
  pinMode(button2_pin, INPUT_PULLUP);
  Serial.println("Button2 press detection initialized.");
}

void button2_run() {
  // 读取按钮的当前状态
  button2_state = digitalRead(button2_pin);

  // 检测按钮按下的边沿（从 HIGH -> LOW）
  if (button2_state == LOW && button2_last_state == HIGH) {
    Serial.println("Button2 pressed!");
    // motor2_running_state = !motor2_running_state;
    lightSensor2_running_state = !lightSensor2_running_state;
    delay(200);  // 防抖延迟，确保按钮按下后信号稳定
  }

  // 更新按钮状态
  button2_last_state = button2_state;

  // 这里可以添加其他需要执行的代码
}