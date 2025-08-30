// 引入外部变量
extern bool motor_running_state;

const int button_pin = 6;       // 按钮引脚
int button_state = HIGH;         // 当前按钮状态
int button_last_state = HIGH;     // 上次按钮状态

void button_init() {
  // 设置按钮引脚为输入，启用内部上拉电阻
  pinMode(button_pin, INPUT_PULLUP);
  Serial.println("Button press detection initialized.");
}

void button_run() {
  // 读取按钮的当前状态
  button_state = digitalRead(button_pin);

  // 检测按钮按下的边沿（从 HIGH -> LOW）
  if (button_state == LOW && button_last_state == HIGH) {
    Serial.println("Button pressed!");
    // 在这里控制电机的启动/停止
    // 你可以在这儿添加控制电机的代码，例如：
    // motor_start();  // 电机启动
    // motor_stop();   // 电机停止
    motor_running_state = !motor_running_state;
    delay(200);  // 防抖延迟，确保按钮按下后信号稳定
  }

  // 更新按钮状态
  button_last_state = button_state;

  // 这里可以添加其他需要执行的代码
}