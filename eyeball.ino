// 眼球控制主程序 - eyeball.ino


void setup() {

  oled_init();
  button_init();
  button2_init();
  motor_init();
  motor2_init();
  light_sensor_init();
  light_sensor2_init();
  

  // 初始化串口用于调试（可选）
  Serial.begin(9600);

  Serial.println("eyeball.ino initialized.");

}

void loop() {
  button_run();
  button2_run();
  motor_run();
  motor2_run();
  lightSensor_run();
  lightSensor2_run();
}