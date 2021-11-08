#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_1 4 
#define NUMPIXELS 6

//for the first set of NEO
Adafruit_NeoPixel strip(NUMPIXELS, PIN_1, NEO_GRB + NEO_KHZ800);
uint32_t blue = strip.Color(0,0,255);
uint32_t red = strip.Color(255,0,0);
uint32_t dark = strip.Color(0,0,0);

int waitDown = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  runGraph();
  //strip.fill(red, 0, 5);
  //flashDark();
  //strip.clear();
}

void runDown(int currPix){
  for(int j = NUMPIXELS; j >= currPix; j--){
    Serial.print("\n\tJ: ");
    Serial.print(j);
    Serial.print("\n");
    strip.setPixelColor(j, red);
    strip.show();
    delay(waitDown);
    strip.setPixelColor(j, dark);
  }
  
}

void runGraph(){
  /*lights are coded in parallel - this treats the code as the same in terms of receptors,
   * meaning we only have to code one of the strips to get the same amount of code in both of them
  */
  Serial.print("\t\t_______Start__________\n");
  for(int i = 1; i <= 6; i++){
    
    
    Serial.print("_________________\nvalue i: ");
    Serial.print(i);
    Serial.print("\n");
    runDown(i);
    strip.fill(blue, 0, i);
    strip.show();
    delay(100);
  }
  strip.clear();

}

void flashDark(){
  strip.fill(strip.Color(0,0,0));
  strip.show();
  delay(500);
}