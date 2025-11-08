extern bool lens_light_sensor_running_state;

const int lens_motor_pin1 = 8;
const int lens_motor_pin2 = 9;
const int lens_motor_pin3 = 10;
const int lens_motor_pin4 = 11;

const int lens_motor_control_pin_right = 12; // 输入信号引脚
const int lens_motor_control_pin_left = 13; // 输入信号引脚

int lens_motor_run_state_change_count = 0;
int lens_motor_run_state = HIGH;

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

  pinMode(lens_motor_control_pin_right, INPUT_PULLUP);
  pinMode(lens_motor_control_pin_left, INPUT_PULLUP);

  lens_motor_stop();

  lens_motor_run_state = HIGH;

  Serial.println("Motor2 initialized. Using INPUT_PULLUP, active LOW.");
} 

void lens_motor_step(int dir) {
  if (dir == LOW) { // 顺时针
    for (int i = 0; i < 4; i++) {
      digitalWrite(lens_motor_pin1, lens_step_sequence[i][0]);
      digitalWrite(lens_motor_pin2, lens_step_sequence[i][1]);
      digitalWrite(lens_motor_pin3, lens_step_sequence[i][2]);
      digitalWrite(lens_motor_pin4, lens_step_sequence[i][3]);
      delay(6);
    }
  } else { // 逆时针
    for (int i = 3; i >= 0; i--) {
      digitalWrite(lens_motor_pin1, lens_step_sequence[i][0]);
      digitalWrite(lens_motor_pin2, lens_step_sequence[i][1]);
      digitalWrite(lens_motor_pin3, lens_step_sequence[i][2]);
      digitalWrite(lens_motor_pin4, lens_step_sequence[i][3]);
      delay(6);
    }
  }
}

void lens_motor_run_state_change() {
  Serial.println("Lens motor run state changed!");
  lens_motor_run_state = !lens_motor_run_state;
  lens_motor_run_state_change_count++;
}

void lens_motor_stop() {
  lens_motor_run_state = HIGH;
  lens_motor_run_state_change_count = 0;
  digitalWrite(lens_motor_pin1, LOW);
  digitalWrite(lens_motor_pin2, LOW);
  digitalWrite(lens_motor_pin3, LOW);
  digitalWrite(lens_motor_pin4, LOW);
}

void lens_motor_run() {
  if (!lens_light_sensor_running_state) {
    lens_motor_stop();
    return;
  }

  int signal_right = digitalRead(lens_motor_control_pin_right);
  int signal_left = digitalRead(lens_motor_control_pin_left);

  if (signal_right == LOW && lens_motor_run_state == HIGH) {
    lens_motor_run_state_change();
  }

  if (signal_left == LOW && lens_motor_run_state == LOW) {
    lens_motor_run_state_change();
  }


  lens_motor_step(lens_motor_run_state);
}
