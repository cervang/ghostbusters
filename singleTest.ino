#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        6
#define NUMPIXELS 16
#define DELAYVAL_INIT 1000
#define LAST_DELAY 250
#define ACTIVE_DURATION 14000

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long startMillis;
unsigned long currentMillis;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();
  //strip.show();
}

void loop() {
  int DELAYVAL = DELAYVAL_INIT;
  
  //Pulses speed up as they continue, stopping at a constant pace of 250
  for(double i = 1.0; i <= 5; i = i+.5){
    
    DELAYVAL = DELAYVAL/i;
    if(DELAYVAL <= 250){
       break;
    }
    pixalSet(DELAYVAL);       
  }
  
  currentMillis = millis();
  startMillis = millis();
  //this traps the LEDs in the same pace for the set amount of seconds
  for(;;){
    if( (currentMillis - startMillis) >= (ACTIVE_DURATION) ){
      break;
    }
    pixalSet(DELAYVAL);
    currentMillis = millis();
  }

  //strip resets, delay_value resets, flashing red to signify end
  strip.clear();
  DELAYVAL = DELAYVAL_INIT;

  for(int i = 0; i < 3; i++){
    flashRed();
    flashDark();
    //strip.clear();  
  }
  strip.clear();
  delay(2000);
  
}

void pixalSet(int DELAYVAL){
  strip.setPixelColor(0, strip.Color(250, 0, 0));
  strip.setPixelColor(1, strip.Color(250, 0, 0));
  strip.setPixelColor(2, strip.Color(250, 0, 0));
  strip.setPixelColor(3, strip.Color(250, 0, 0));
  strip.show();
  delay(DELAYVAL-1);  
  strip.clear();
  strip.setPixelColor(4, strip.Color(250, 0, 0));
  strip.setPixelColor(5, strip.Color(250, 0, 0));
  strip.setPixelColor(6, strip.Color(250, 0, 0));
  strip.setPixelColor(7, strip.Color(250, 0, 0));
  strip.show();
  delay(DELAYVAL);
  strip.clear();
  
  strip.setPixelColor(8, strip.Color(250, 0, 0));
  strip.setPixelColor(9, strip.Color(250, 0, 0));
  strip.setPixelColor(10, strip.Color(250, 0, 0));
  strip.setPixelColor(11, strip.Color(250, 0, 0));
  strip.show();
  delay(DELAYVAL);
  strip.clear();
  strip.setPixelColor(12, strip.Color(250, 0, 0));
  strip.setPixelColor(13, strip.Color(250, 0, 0));
  strip.setPixelColor(14, strip.Color(250, 0, 0));
  strip.setPixelColor(15, strip.Color(250, 0, 0));
  strip.show();
  delay(DELAYVAL);
  strip.clear();
  
}


void flashRed(){
  strip.fill(strip.Color(255,0,0));
  strip.show();
  delay(LAST_DELAY);
}

void flashDark(){
  strip.fill(strip.Color(0,0,0));
  strip.show();
  delay(LAST_DELAY);
}
