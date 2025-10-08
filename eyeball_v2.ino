 
void setup() {
  // 启动串口通信，用于调试
  Serial.begin(9600);
  pupil_button_init();
  pupil_light_sensor_init();
  pupil_motor_init();

}

void loop() {
  pupil_button_run();
  pupil_light_sensor_run();
  pupil_motor_run();

}
 