extern bool pupil_light_sensor_running_state;

const int pupil_motor_pin1 = 4;
const int pupil_motor_pin2 = 5;
const int pupil_motor_pin3 = 6;
const int pupil_motor_pin4 = 7;

const int pupil_motor_control_pin = 13; // 输入信号引脚

int pupil_motor_run_state = HIGH;
int pupil_motor_last_state = HIGH;

unsigned long pupil_last_direction_change_time = 0;
const unsigned long pupil_direction_grace_period = 1500; // 宽限时间（毫秒）

const int pupil_step_sequence[4][4] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void pupil_motor_init() {
  pinMode(pupil_motor_pin1, OUTPUT);
  pinMode(pupil_motor_pin2, OUTPUT);
  pinMode(pupil_motor_pin3, OUTPUT);
  pinMode(pupil_motor_pin4, OUTPUT);

  pinMode(pupil_motor_control_pin, INPUT_PULLUP);

  pupil_motor_run_state = HIGH;
  pupil_motor_last_state = HIGH;

  Serial.println("Motor2 initialized. Using INPUT_PULLUP, active LOW.");
} 

void pupil_motor_step(int dir) {
  if (dir == LOW) { // 顺时针
    for (int i = 0; i < 4; i++) {
      digitalWrite(pupil_motor_pin1, pupil_step_sequence[i][0]);
      digitalWrite(pupil_motor_pin2, pupil_step_sequence[i][1]);
      digitalWrite(pupil_motor_pin3, pupil_step_sequence[i][2]);
      digitalWrite(pupil_motor_pin4, pupil_step_sequence[i][3]);
      delay(6);
    }
  } else { // 逆时针
    for (int i = 3; i >= 0; i--) {
      digitalWrite(pupil_motor_pin1, pupil_step_sequence[i][0]);
      digitalWrite(pupil_motor_pin2, pupil_step_sequence[i][1]);
      digitalWrite(pupil_motor_pin3, pupil_step_sequence[i][2]);
      digitalWrite(pupil_motor_pin4, pupil_step_sequence[i][3]);
      delay(6);
    }
  }
}

void pupil_motor_control_low_pin_check() {
  int signal = digitalRead(pupil_motor_control_pin);

  if (signal != LOW) {
    pupil_motor_stop();
    return;
  } 

  for (int i = 60; i >= 0; i--) {
    pupil_motor_step(HIGH);
  }

  signal = digitalRead(pupil_motor_control_pin);
  if (signal != LOW) {
    pupil_motor_stop();
    return;
  } 

  for (int i = 60; i >= 0; i--) {
    pupil_motor_step(LOW);
  }
}

void pupil_motor_run_state_change(int state) {
  if (pupil_motor_run_state != state) {
    pupil_motor_run_state = state;
    pupil_last_direction_change_time = millis(); // 记录方向切换时间
    Serial.println("Direction changed!");
  }
}

void pupil_motor_stop() {
  digitalWrite(pupil_motor_pin1, LOW);
  digitalWrite(pupil_motor_pin2, LOW);
  digitalWrite(pupil_motor_pin3, LOW);
  digitalWrite(pupil_motor_pin4, LOW);
}

void pupil_motor_run() {
  if (!pupil_light_sensor_running_state) {
    pupil_motor_control_low_pin_check();
    return;
  }

  int signal = digitalRead(pupil_motor_control_pin);
  unsigned long now = millis();

  // 如果不是刚换方向，并且信号 LOW，且方向和上次相同 → 停止
  if ((now - pupil_last_direction_change_time > pupil_direction_grace_period) &&
      signal == LOW &&
      pupil_motor_last_state == pupil_motor_run_state) {
    pupil_motor_stop();
    return;
  }

  // 否则允许运动
  pupil_motor_step(pupil_motor_run_state);
  pupil_motor_last_state = pupil_motor_run_state;
}
