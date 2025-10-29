extern void pupil_motor_run_state_change();

// 定义引脚
const int pupil_light_sensor_DO = A3;    // 光敏模块DO引脚连接 A3

const int pupil_light_sensor_num_max = 2000;
bool pupil_light_sensor_running_state = false; // 是否开启光敏传感器
int pupil_light_sensor_last_state = HIGH;

void pupil_light_sensor_init() {  
  pinMode(pupil_light_sensor_DO, INPUT);
  pupil_light_sensor_running_state = false;
  pupil_light_sensor_last_state = digitalRead(pupil_light_sensor_DO);
  Serial.println("光敏传感器_pupil DO控制程序启动");
}

/**
改变光敏传感器的状态
*/
void pupil_light_sensor_state_change() {
  Serial.println("光敏传感器_pupil 状态改变");
  pupil_light_sensor_running_state = !pupil_light_sensor_running_state;
  pupil_motor_run_state_change(HIGH); // HIGH 向上运动， LOW 向下运动

}

void pupil_light_sensor_run() {
  if (!pupil_light_sensor_running_state) {
    pupil_light_sensor_last_state = digitalRead(pupil_light_sensor_DO);
    return;
  }

  int pupil_light_sensor_num = digitalRead(pupil_light_sensor_DO);

  if (pupil_light_sensor_num == LOW) {
    pupil_motor_run_state_change(LOW);
   } else {
    pupil_motor_run_state_change(HIGH);
   }

}