// 眼球控制主程序 - eyeball.ino


void setup() {

  oled_init();
  button_init();
  motor_init();
  light_sensor_init();
  

   // 初始化串口用于调试（可选）
   Serial.begin(9600);

   Serial.println("eyeball.ino initialized.");

}

void loop() {
  button_run();
  motor_run();
  lightSensor_run();

  oled_update(7, 2, "F");
}