#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// 使用 U8X8 模式（字符模式，内存占用小）
// 驱动：SSD1306 128x64，I2C，SCL=A5，SDA=A4
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);  

void oled_init(void) {
  // 初始化 OLED
  u8x8.begin();    

  // 设置字体（小字体更省内存）
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  // 显示初始化文字
  u8x8.drawString(0, 1, "Hello, Arduino!");
  u8x8.drawString(0, 3, "U8g2 Low RAM");
}

void oled_showx(void) {
  static int counter = 0;
  char buf[16];  

  // 清空一行，再写入计数
  sprintf(buf, "Count: %d", counter++);
  u8x8.drawString(0, 5, "             "); // 清空
  u8x8.drawString(0, 5, buf);

  delay(500);
}
