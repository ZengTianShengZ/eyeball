 
void setup() {
  // 启动串口通信，用于调试
  Serial.begin(9600);
  pupil_button_init();
  pupil_light_sensor_init();
  pupil_motor_init();

  lens_button_init();
  lens_light_sensor_init();
  lens_motor_init();

  // oled_init();

}

void loop() {
  pupil_button_run();
  pupil_light_sensor_run();
  pupil_motor_run();

  lens_button_run();
  lens_light_sensor_run();
  lens_motor_run();

}
 