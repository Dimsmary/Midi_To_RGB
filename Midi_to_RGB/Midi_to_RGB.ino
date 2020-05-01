#include <FastLED.h>
#define NUM_LEDS 36
// 灯珠个数定义
#define DATA_PIN 2
// 控制脚定义
#define KICK_NOTE 36
#define HIHAT_NOTE 37
#define SNARE_NOTE 38
// 响应的MIDI消息定义

int noteON = 144;
int noteOFF = 128;
// MIDI命令中的ON/OFF

CRGB leds[NUM_LEDS];
CRGB KICK = CRGB(55,122,55);
CRGB SNARE = CRGB(0,55,122);
CRGB HIHAT = CRGB(122,22,55);
CRGB STANDBY;
void setup() { 
      Serial.begin(38400);
      FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}

// 切换颜色
void color_switch(CRGB color,unsigned char part){
  // 判断亮灯范围
  int begin_num = (NUM_LEDS / 3) * part;
  int end_num = begin_num + (NUM_LEDS / 3);
  for(int i = begin_num; i < end_num; i++){
    leds[i] = color;
  }
//    for(int i = 0; i < NUM_LEDS; i++){
//    leds[i] = color;
//  }
  FastLED.show();
}

// 切换颜色
void color_switchT(CRGB color){
  // 判断亮灯范围
    for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = color;
  }
  FastLED.show();
}
void loop() { 
    int incomingByte;
    // 接收MIDI
    if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 144 || incomingByte == 128){
        unsigned char sta = incomingByte;
        incomingByte = Serial.read();
        int part = -1;
        
        // 判断音高
        switch(incomingByte){
          case KICK_NOTE:
            part = 0;
            STANDBY = KICK;
            break;
          case HIHAT_NOTE:
            part = 1;
            STANDBY = HIHAT;
            break;
          case SNARE_NOTE:
            part = 2;
            STANDBY = SNARE;
            break;
        }
        // 判断ON/OFF
        if(sta == 144 && part > -1){
          color_switch(STANDBY, part);
        }
        else{
          color_switch(CRGB::Black, part);
          
        }
    }
  }
}
