#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif
#define GUN_SWITCH_PIN 2
#define PIN_GRAPH 4
#define GRAPH_PIXEL 6
//graph LEDs
Adafruit_NeoPixel graph(GRAPH_PIXEL, PIN_GRAPH, NEO_GRB + NEO_KHZ800);

//bright is mostly for not burning my eyes during testing
//used to control the brightness of LEDs
int BRIGHT = 50;
//delay value is 4 for BRIGHT 255 and 30 for BRIGHT 50
int DELAY_STROBE = 30;
//colors used in the program and for testing
uint32_t blue = graph.Color(0,0,BRIGHT);
uint32_t red = graph.Color(BRIGHT,0,0);
uint32_t orange = graph.Color(255, 165, 0);
uint32_t purple = graph.Color(255,0,150);
uint32_t green = graph.Color(0,BRIGHT,0);
uint32_t dark = graph.Color(0,0,0);
//default currColor is red

uint32_t currColor = red;
int CUR_GUN_STATE = 1;
int gunSwitchWait = 150;
unsigned long currTime = millis(); 
unsigned long prevTime = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  graph.show();
  pinMode(GUN_SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  currTime = millis();
  //read the switch
  int gunButtonVal = digitalRead(GUN_SWITCH_PIN);
  Serial.print("\ngunButtonVal: ");
  Serial.print(gunButtonVal);
  Serial.print("\n\t");
  Serial.print(HIGH);
  
  //if button is active
  if(gunButtonVal == LOW){
    if(currTime - prevTime > gunSwitchWait){
      gun_state();
      graph.fill(dark, 0, GRAPH_PIXEL);
      graph.show();
      prevTime = currTime;
    }
  }
  graph.fill(currColor, 0, GRAPH_PIXEL);
  graph.show();
  //graph.clear();
  Serial.print("\n\tGun Value: ");
  Serial.print(CUR_GUN_STATE);
  //delay(20);
  
}



/**
 *Returns an color to change the NEOPIXEL lights
*/
void gun_state(){
  //uint32_t GunColor;
  if(CUR_GUN_STATE > 3){
    //reset to 0
    CUR_GUN_STATE = 0;
  }
  switch (CUR_GUN_STATE) {
    case 0:
      // Orange would be the default
      //this would be the default state
      currColor = red;
      break;
    case 1:
      // slime
      // return green
      currColor = green;
      break;
    case 2:
      // ice
      // return blue
      currColor = blue;
      break;
    case 3:
      // firing
      currColor = purple;
      break;
    default:
      //default would be red
      currColor = red;
      break;
  }
  //increment
  CUR_GUN_STATE++;
  
}
