#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//data in
#define LED_PIN    2
// How many NeoPixels are attached to the Arduino?
//#define LED_COUNT 60
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

#define strip2LED_COUNT 16
#define LED_PIN_2    7

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(strip2LED_COUNT, LED_PIN_2, NEO_RGB + NEO_KHZ800);


void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show(); 
  strip2.begin();
  strip2.show();
}



void loop() {
  // put your main code here, to run repeatedly:
  uint32_t COLOR = strip.Color(0,255,0);
  int START = 0;
  int END = 10;
  strip.fill(strip.Color(255,0,0), START, END);
  strip.show();
  delay(1000);
  strip.clear();

  for(int CURRENT =0; CURRENT < 10; CURRENT++){
    strip.fill(COLOR, CURRENT, 10);
    strip.show();
    delay(1000);

     uint32_t COLOR = strip2.Color(0,0,255);
  int START = 0;
  int END = 16;
  strip2.fill(strip2.Color(0,0,255), START, END);
  strip2.show();
  delay(1000);
 }
}
