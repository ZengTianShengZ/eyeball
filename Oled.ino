#include <U8g2lib.h>
#include <Wire.h>

// 初始化U8g2 for SH1106
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void initOLED() {
    u8g2.begin();
    
    // 显示启动信息
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 15, "SH1106 OLED");
    u8g2.drawStr(0, 30, "初始化成功!");
    u8g2.sendBuffer();
    delay(2000);
    showOLED();
}

void showOLED() {
  // 显示Hello World
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(10, 30, "Hello");
  u8g2.drawStr(20, 50, "World!");
  u8g2.sendBuffer();
//   delay(3000);
  
//   // 显示不同字体
//   showDifferentFonts();
//   delay(3000);
  
//   // 显示滚动文本
//   scrollText();
//   delay(2000);
}

void showDifferentFonts() {
  u8g2.clearBuffer();
  
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.drawStr(0, 10, "5x7字体 - 小字");
  
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 25, "6x10字体 - 中字");
  
  u8g2.setFont(u8g2_font_10x20_tr);
  u8g2.drawStr(0, 50, "Hello World!");
  
  u8g2.sendBuffer();
}

void scrollText() {
  for (int i = 0; i < 10; i++) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr(i, 32, "SH1106滚动文本");
    u8g2.sendBuffer();
    delay(100);
  }
}
