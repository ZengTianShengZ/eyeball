#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

String oled_current_text = "";

// 使用 U8X8 模式（字符模式，内存占用小）
// 驱动：SSD1306 128x64，I2C，SCL=A5，SDA=A4
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);  

void oled_init(void) {
  u8x8.begin();
  oled_show_init();

}

void oled_show_init() {
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_inb33_3x6_r);
  u8x8.drawString(3, 1, "^-^");
}

void oled_show_t() {
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_inb33_3x6_r);
  u8x8.drawString(6, 1, "T");
}