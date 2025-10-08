extern bool lens_light_sensor_running_state;

const int lens_motor_pin1 = 4;
const int lens_motor_pin2 = 5;
const int lens_motor_pin3 = 6;
const int lens_motor_pin4 = 7;

const int lens_motor_control_pin = 13; // 输入信号引脚

int lens_motor_run_state = HIGH;
int lens_motor_last_state = HIGH;

unsigned long lens_last_direction_change_time = 0;
const unsigned long lens_direction_grace_period = 1000; // 宽限时间（毫秒）

const int lens_step_sequence[4][4] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void lens_motor_init() {
  pinMode(lens_motor_pin1, OUTPUT);
  pinMode(lens_motor_pin2, OUTPUT);
  pinMode(lens_motor_pin3, OUTPUT);
  pinMode(lens_motor_pin4, OUTPUT);

  pinMode(lens_motor_control_pin, INPUT_PULLUP);

  lens_motor_run_state = HIGH;
  lens_motor_last_state = HIGH;

  Serial.println("Motor2 initialized. Using INPUT_PULLUP, active LOW.");
} 

void lens_motor_step(int dir) {
  if (dir == LOW) { // 顺时针
    for (int i = 0; i < 4; i++) {
      digitalWrite(lens_motor_pin1, lens_step_sequence[i][0]);
      digitalWrite(lens_motor_pin2, lens_step_sequence[i][1]);
      digitalWrite(lens_motor_pin3, lens_step_sequence[i][2]);
      digitalWrite(lens_motor_pin4, lens_step_sequence[i][3]);
      delay(3);
    }
  } else { // 逆时针
    for (int i = 3; i >= 0; i--) {
      digitalWrite(lens_motor_pin1, lens_step_sequence[i][0]);
      digitalWrite(lens_motor_pin2, lens_step_sequence[i][1]);
      digitalWrite(lens_motor_pin3, lens_step_sequence[i][2]);
      digitalWrite(lens_motor_pin4, lens_step_sequence[i][3]);
      delay(3);
    }
  }
}

void lens_motor_run_state_change(int state) {
  if (lens_motor_run_state != state) {
    lens_motor_run_state = state;
    lens_last_direction_change_time = millis(); // 记录方向切换时间
    Serial.println("Direction changed!");
  }
}

void lens_motor_stop() {
  digitalWrite(lens_motor_pin1, LOW);
  digitalWrite(lens_motor_pin2, LOW);
  digitalWrite(lens_motor_pin3, LOW);
  digitalWrite(lens_motor_pin4, LOW);
}

void lens_motor_run() {
  if (!lens_light_sensor_running_state) {
    return;
  }

  int signal = digitalRead(lens_motor_control_pin);
  unsigned long now = millis();

  // 如果不是刚换方向，并且信号 LOW，且方向和上次相同 → 停止
  if ((now - lens_last_direction_change_time > lens_direction_grace_period) &&
      signal == LOW &&
      lens_motor_last_state == lens_motor_run_state) {
    lens_motor_stop();
    return;
  }

  // 否则允许运动
  lens_motor_step(lens_motor_run_state);
  lens_motor_last_state = lens_motor_run_state;
}
