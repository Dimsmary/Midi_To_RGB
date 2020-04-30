#include <FastLED.h>
#define NUM_LEDS 36
#define DATA_PIN 2

int noteON = 144;
int noteOFF = 128;
// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB KICK = CRGB(122,22,80);
CRGB SNARE = CRGB(22,55,166);
CRGB HIHAT = CRGB(12,122,80);
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
#ifdef mode1
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
          case 36:
            part = 0;
            STANDBY = KICK;
            break;
          case 37:
            part = 1;
            STANDBY = HIHAT;
            break;
          case 38:
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
#else
        color_switchT(CRGB:: White);
#endif
}
