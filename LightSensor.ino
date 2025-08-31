extern bool motor_running_state;
extern int motor_round_cout;

// 定义引脚
const int lightSensor_DO = A0;    // 光敏模块DO引脚连接数字引脚2
// const int lightSensor_AO = A1;    // 光敏模块AO引脚连接数字引脚2

bool lightSensor_running_state = false;

int lightSensor_num = 2000;
int lightSensor_num_last = 2000;
 
void light_sensor_init() {  
  // 设置光敏传感器DO引脚为输入模式
  // pinMode(lightSensor_DO, INPUT);
  lightSensor_running_state = false;
  lightSensor_num = 2000;
  lightSensor_num_last = 2000;
  Serial.println("光敏传感器DO控制程序启动");
}

void lightSensor_run() {

  if (!lightSensor_running_state) {
    lightSensor_num_last = 2000;
    motor_running_state = false;
    motor_round_cout = 0;
    return;
  }

  // 读取数字输出引脚状态
  // lightSensor_num = digitalRead(lightSensor_DO);
  lightSensor_num = analogRead(lightSensor_DO);
  if (lightSensor_num <= lightSensor_num_last) {
    lightSensor_num_last = lightSensor_num;
  } 
  Serial.print("A0 Light Level: 》》》》》");
 

  int difference = abs(lightSensor_num - lightSensor_num_last);
  // Serial.println(lightSensor_num);
  Serial.println(lightSensor_num);
  // Serial.println(difference);
  // Serial.println(motor_round_cout);
   

  if (motor_round_cout >= 2 && (difference < 10)) {
    Serial.print("stop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    lightSensor_running_state = false;
    motor_running_state = false;
    delay(5000); 
  } else {
    motor_running_state = true;
  }
}