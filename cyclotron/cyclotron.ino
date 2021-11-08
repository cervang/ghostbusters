#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN        6
#define NUMPIXELS 16
#define DELAYVAL_INIT 550
#define STABLEDELAY 250
#define LAST_DELAY 250
#define FADE 4
#define ACTIVE_DURATION 12000

Adafruit_NeoPixel strip(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800);
//for the first set of NEO graph
Adafruit_NeoPixel strip_graph_1(6, 4, NEO_GRB + NEO_KHZ800);
//second set of NEO graph
Adafruit_NeoPixel strip_graph_2(6, 5, NEO_GRB + NEO_KHZ800);

unsigned long startMillis;
unsigned long currentMillis;

uint32_t red = strip.Color(255,0,0);
uint32_t green = strip.Color(0,255,0);
uint32_t blue = strip.Color(0,0,255);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();
  strip_graph_1.begin();
  //strip_graph_2.begin();
}


void loop() {
  int DELAYVAL = DELAYVAL_INIT;
  //run the graph
  runGraph();
  
  //Pulses speed up as they continue, stopping at a constant pace of 250
  int loop = 0;
  for(double i = 1.0; i <= 5; i = i+.5){
    
    DELAYVAL = DELAYVAL/i;
    if(DELAYVAL <= STABLEDELAY){
       break;
    }
    pixalSet(DELAYVAL, loop);   
    loop++;    
  }
  
  currentMillis = millis();
  startMillis = millis();
  //this traps the LEDs in the same pace for the set amount of seconds
  
  for(;;){
    if( (currentMillis - startMillis) >= (ACTIVE_DURATION) ){
      break;
    }
    pixalSet(DELAYVAL, loop);
    currentMillis = millis();
  }

  //strip resets, delay_value resets, flashing red to signify end
  strip.clear();
  DELAYVAL = DELAYVAL_INIT;

  for(int i = 0; i < 2; i++){
    flashDig();
    //flashRed();
    //flashDark();
    //strip.clear();  
  }
  strip.clear();
  delay(2000);
  
}

void circleSet(int START, int END, int LOOP){
  for(int i = 0; i <= 255; i++){
    strip.fill(strip.Color(255-i,0,0), START, END);  
    strip.show();
    if(FADE-LOOP > 1){
      delay( FADE-LOOP );  
    }
    
  }  
}

void pixalSet(int DELAYVAL, int LOOP){
  circleSet(12,4, LOOP);
  strip.clear();

  circleSet(8,4, LOOP);
  strip.clear();

  circleSet(4,4, LOOP);
  strip.clear();

  circleSet(0,4, LOOP);
  strip.clear();

 
}


void flashRed(){
  strip.fill(strip.Color(255,0,0));
  strip.show();
  delay(LAST_DELAY);
}

void flashDig(){
  strip.fill(red, 0, 4); 
  strip.fill(red, 8, 4); 
  strip.show();
  delay(LAST_DELAY);
  flashDark();
  strip.fill(red, 4, 4); 
  strip.fill(red, 12, 4); 
  strip.show();
  delay(LAST_DELAY);
  flashDark();
}

void runGraph(){
  for(int i = 0; i < 6; i++){
    strip_graph_1.fill(blue, 0, i);
    //strip_graph_2.fill(blue, 0, i);
    strip_graph_1.show();
    //strip_graph_2.show();
    delay(500);
    strip_graph_1.clear();
    //strip_graph_2.clear();
  }
  strip_graph_1.clear();
  //strip_graph_2.clear();
}

void flashDark(){
  strip.fill(strip.Color(0,0,0));
  strip.show();
  delay(LAST_DELAY);
}
