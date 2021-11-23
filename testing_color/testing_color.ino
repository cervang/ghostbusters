#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define bright 50
#define GRAPH_COUNT 20
#define GRAPH_PIN 4

int CUR_GUN_STATE = 0; 


Adafruit_NeoPixel graph(GRAPH_COUNT, GRAPH_PIN, NEO_GRB + NEO_KHZ800);


uint32_t red = graph.Color(bright,0,0);
uint32_t green = graph.Color(0,bright,0);
uint32_t blue = graph.Color(0,0,bright);
uint32_t orange = graph.Color(255,165,0);
uint32_t dark = graph.Color(0,0,0);
//default color would be red
uint32_t currColor = red;

void setup() {
  // put your setup code here, to run once:
  graph.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}

/**
 *Returns an color to change the NEOPIXEL lights
*/
void gun_state(){
  uint32_t GunColor;
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
      currColor = orange;
      break;
    default:
      //default would be red
      currColor = red;
      break;
  }
  //increment
  CUR_GUN_STATE++;
}
