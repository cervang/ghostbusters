#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

/////////////////////// Variables for the Strips ///////////////////////
#define BRIGHT 25

#define LEN_FIRST 28
#define LEN_SECOND 32
#define LEN_WEAK 7
#define PULSE_LEN 10

Adafruit_NeoPixel FIRST(LEN_FIRST, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SECOND(LEN_SECOND, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel WEAK(LEN_WEAK, 7, NEO_GRB + NEO_KHZ800);

uint32_t BLUE = FIRST.Color(0,0,BRIGHT);
uint32_t RED = FIRST.Color(BRIGHT,0,0);
uint32_t DARK = FIRST.Color(0,0,0);
uint32_t GREEN = FIRST.Color(0,BRIGHT,0);


/////////////////////// Loop Variables ///////////////////////
uint32_t currColor = RED;
int delayVal = 15;

/////////////////////// Helper Functions ///////////////////////
//void StripClear(Adafruit_NeoPixel currStrip){
//  // clear function is not working, this is my work around
//  // None of the strips have a length above 50, so 50 is a good max number  
//  // This function also doesn't work- looks like Neo Pixal really hates the clear function for some reason
//  Serial.print("\t\tIn Function\n");
//  currStrip.fill(DARK, 0, LEN_FIRST);
//  currStrip.show();
//  Serial.print("\t\tEnd of Function\n");
//  return ;
//}


void setup() {
  // put your setup code here, to run once:
  FIRST.begin();
  SECOND.begin();
  WEAK.begin();
  Serial.begin(9600);
}

void loop() {

//  if there is not a color change, continue with the cyclone
// I want to fade the individual lights
// itterate over each of them
//do the brute force first

//  pulse(FIRST, LEN_FIRST);

 for(int i = 0; i < LEN_FIRST; i++){
     //    we're going to light them one by one
     //    for each, fill them with the color red
     FIRST.setPixelColor(i, RED);
     FIRST.show();
     Serial.print("i value:");
     Serial.print(i);
     Serial.print("\n");
    if(i >= PULSE_LEN){
     FIRST.setPixelColor(i-PULSE_LEN, DARK);
     FIRST.show();
    }
     delay(delayVal);
 }
 FIRST.clear();
 FIRST.show();


 for(int i = 0; i < LEN_SECOND; i++){
     //    we're going to light them one by one
     //    for each, fill them with the color red
     SECOND.setPixelColor(i, RED);
     SECOND.show();
     Serial.print("i value:");
     Serial.print(i);
     Serial.print("\n");
    if(i >= PULSE_LEN){
     SECOND.setPixelColor(i-PULSE_LEN, DARK);
     SECOND.show();
    }
     delay(delayVal);
 }
 SECOND.clear();
 SECOND.show();
//
//
 for(int i = 0; i < LEN_WEAK; i++){
     //    we're going to light them one by one
     //    for each, fill them with the color red
     WEAK.setPixelColor(i, RED);
     WEAK.show();
     Serial.print("i value:");
     Serial.print(i);
     Serial.print("\n");
    if(i >= 5){
     Serial.print("\t"); 
     Serial.print(i-5);
     Serial.print("\n");
     WEAK.setPixelColor(i-5, DARK);
     WEAK.show();
    }
     delay(delayVal+50);
 }
 WEAK.clear();
 WEAK.show();

  Serial.print("End of Loop\n");
  Serial.print("_______________________\n");

}


//This is what I would like to use, but the function doesn't work with the NANO for some reason
void pulse(Adafruit_NeoPixel NEO_STRIP, int LEN_VAL){
   for(int i = 0; i < LEN_VAL; i++){
     //    we're going to light them one by one
     //    for each, fill them with the color red
     NEO_STRIP.setPixelColor(i, RED);
     NEO_STRIP.show();
     Serial.print("i value:");
     Serial.print(i);
     Serial.print("\n");
    if(i >= 5){
     Serial.print("\t"); 
     Serial.print(i-5);
     Serial.print("\n");
     NEO_STRIP.setPixelColor(i-5, DARK);
     NEO_STRIP.show();
    }
     delay(delayVal);
 }
 NEO_STRIP.clear();
 NEO_STRIP.show();
}
