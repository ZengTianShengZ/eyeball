// 眼球控制主程序 - eyeball.ino


void setup() {
  button_init();
  motor_init();

  // 初始化串口用于调试（可选）
  Serial.begin(9600);
}

void loop() {
  button_run();
  motor_run();
}