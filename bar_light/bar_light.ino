#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_1 4 
#define PIN_2 5
#define NUMPIXELS 6
//for the first set of NEO
Adafruit_NeoPixel strip(NUMPIXELS, PIN_1, NEO_GRB + NEO_KHZ800);
//second set of NEO
Adafruit_NeoPixel strip(NUMPIXELS, PIN_2, NEO_GRB + NEO_KHZ800);
uint32_t blue = strip.Color(0,0,255);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //flashDark();
  //strip.clear();
  for(int i = 0; i < 6; i++){
    strip.fill(blue, 0, i);
    strip.show();
    delay(500);
    strip.clear();
  }
  strip.clear();
}

void flashDark(){
  strip.fill(strip.Color(0,0,0));
  strip.show();
  delay(500);
}
