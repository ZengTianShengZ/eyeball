// 定义引脚
const int motor2_pin1 = 4;
const int motor2_pin2 = 5;
const int motor2_pin3 = 6;
const int motor2_pin4 = 7;

const int motor2_control_pin = 13; // 输入信号引脚


// 步序（半步 8 步）
const int step2_sequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

bool motor2_clockwise = true;   // 当前方向

bool motor2_running_state = false;   // 控制电机启动/停止

int motor2_lastSignal = HIGH;   // 上次信号

int motor2_round_cout = 0; // 电机往返次数

void motor2_init() {
  pinMode(motor2_pin1, OUTPUT);
  pinMode(motor2_pin2, OUTPUT);
  pinMode(motor2_pin3, OUTPUT);
  pinMode(motor2_pin4, OUTPUT);

  // 启用内部上拉
  pinMode(motor2_control_pin, INPUT_PULLUP);

  motor2_running_state = false;

  motor2_round_cout = 0;


  // 读取初始信号
  motor2_lastSignal = digitalRead(motor2_control_pin);

  Serial.println("Motor2 initialized. Using INPUT_PULLUP, active LOW.");
} 

void motor2_step(bool dir) {
  if (dir) { // 顺时针
    for (int i = 0; i < 8; i++) {
      digitalWrite(motor2_pin1, step2_sequence[i][0]);
      digitalWrite(motor2_pin2, step2_sequence[i][1]);
      digitalWrite(motor2_pin3, step2_sequence[i][2]);
      digitalWrite(motor2_pin4, step2_sequence[i][3]);
      delay(2);
    }
  } else { // 逆时针
    for (int i = 7; i >= 0; i--) {
      digitalWrite(motor2_pin1, step2_sequence[i][0]);
      digitalWrite(motor2_pin2, step2_sequence[i][1]);
      digitalWrite(motor2_pin3, step2_sequence[i][2]);
      digitalWrite(motor2_pin4, step2_sequence[i][3]);
      delay(2);
    }
  }
}

void motor2_run() {
  if (!motor2_running_state) {
    motor2_stop();
    return;
  }


  // 读取信号
  int signal = digitalRead(motor2_control_pin);

  // 如果接触到 GND（LOW），直接反向
  if (signal == LOW && motor2_lastSignal == HIGH) {
    motor2_running_state = false;
  }

  motor2_lastSignal = signal;

  // 持续转动当前方向
  motor2_step(motor2_clockwise);
}


void motor2_stop() {
  digitalWrite(motor2_pin1, LOW);
  digitalWrite(motor2_pin2, LOW);
  digitalWrite(motor2_pin3, LOW);
  digitalWrite(motor2_pin4, LOW);
} 
