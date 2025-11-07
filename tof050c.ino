#include <Wire.h>
#include "Adafruit_VL6180X.h"

Adafruit_VL6180X vl = Adafruit_VL6180X();
bool tof_sensor_ready = false;  // 传感器初始化状态标志

// 移动平均滤波参数
#define FILTER_SIZE 5  // 滤波窗口大小，可以调整（3-10之间效果较好）
int filter_buffer[FILTER_SIZE] = {0};
int filter_index = 0;
bool filter_initialized = false;

void tof050c_init() {
  if (!vl.begin()) {
    Serial.println("ToF sensor: Failed to find sensor, continuing without it...");
    tof_sensor_ready = false;
    return;
  }
  Serial.println("ToF sensor: Sensor found!");
  tof_sensor_ready = true;
}
 
// 读取距离值（单位：mm，范围0-200mm）
// 返回-1表示读取失败或传感器未初始化
// 使用移动平均滤波消除波动
int tof050c_getRange() {
  if (!tof_sensor_ready) {
    return -1;  // 传感器未初始化，直接返回-1
  }
  
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();
  
  if (status != VL6180X_ERROR_NONE) {
    // 读取失败，返回-1
    return -1;
  }
  
  int raw_value = (int)range;
  
  // 移动平均滤波：将新值加入缓冲区
  filter_buffer[filter_index] = raw_value;
  filter_index = (filter_index + 1) % FILTER_SIZE;
  
  // 如果缓冲区未填满，标记为已初始化
  if (!filter_initialized) {
    if (filter_index == 0) {
      filter_initialized = true;  // 缓冲区已填满
    }
  }
  
  // 计算平均值
  long sum = 0;
  int count = filter_initialized ? FILTER_SIZE : filter_index;
  
  for (int i = 0; i < count; i++) {
    sum += filter_buffer[i];
  }
  
  return (int)(sum / count);
}

void tof050c_run() {
  if (!tof_sensor_ready) {
    // 传感器未初始化，跳过读取
    return;
  }
  
  int distance = tof050c_getRange();
  
  if (distance >= 0) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" mm");
  } else {
    Serial.println("Distance read failed");
  }
  
  delay(50);
}