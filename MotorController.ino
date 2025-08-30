// 定义引脚
const int motor_pin1 = 8;
const int motor_pin2 = 9;
const int motor_pin3 = 10;
const int motor_pin4 = 11;

const int motor_control_pin = 12; // 输入信号引脚

// 步序（半步 8 步）
const int step_sequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

bool motor_clockwise = true;   // 当前方向
int motor_lastSignal = HIGH;   // 上次信号

void motor_init() {
  Serial.begin(115200);

  pinMode(motor_pin1, OUTPUT);
  pinMode(motor_pin2, OUTPUT);
  pinMode(motor_pin3, OUTPUT);
  pinMode(motor_pin4, OUTPUT);

  // 启用内部上拉
  pinMode(motor_control_pin, INPUT_PULLUP);

  // 读取初始信号
  motor_lastSignal = digitalRead(motor_control_pin);

  Serial.println("Motor initialized. Using INPUT_PULLUP, active LOW.");
}

void motor_step(bool dir) {
  if (dir) { // 顺时针
    for (int i = 0; i < 8; i++) {
      digitalWrite(motor_pin1, step_sequence[i][0]);
      digitalWrite(motor_pin2, step_sequence[i][1]);
      digitalWrite(motor_pin3, step_sequence[i][2]);
      digitalWrite(motor_pin4, step_sequence[i][3]);
      delay(2);
    }
  } else { // 逆时针
    for (int i = 7; i >= 0; i--) {
      digitalWrite(motor_pin1, step_sequence[i][0]);
      digitalWrite(motor_pin2, step_sequence[i][1]);
      digitalWrite(motor_pin3, step_sequence[i][2]);
      digitalWrite(motor_pin4, step_sequence[i][3]);
      delay(2);
    }
  }
}

void motor_run() {
  // 读取信号
  int signal = digitalRead(motor_control_pin);

  // 如果接触到 GND（LOW），直接反向
  if (signal == LOW && motor_lastSignal == HIGH) {
    motor_clockwise = !motor_clockwise;  // 翻转方向
    Serial.print("GND detected! Now direction: ");
    Serial.println(motor_clockwise ? "CW" : "CCW");
  }

  motor_lastSignal = signal;

  // 持续转动当前方向
  motor_step(motor_clockwise);
}
