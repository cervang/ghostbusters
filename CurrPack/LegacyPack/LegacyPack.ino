#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// TODO: Make a header file with all the helper functions

/////////////////////// Variables for the NeoPixels ///////////////////////

// might keep these, might not, but these would be for the colors
#define blue_pin 2
#define red_pin 3
#define green_pin 4
#define orange_pin 5


#define BRIGHT 25

// length of the neopixel strips for each 'bulb'
#define LEN_CYCLO 4
// There are four bulbs, make a variable for each
Adafruit_NeoPixel FIRST(LEN_CYCLO, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SECOND(LEN_CYCLO, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel THIRD(LEN_CYCLO, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel FOURTH(LEN_CYCLO, 9, NEO_GRB + NEO_KHZ800);

uint32_t BLUE = FIRST.Color(0,0,BRIGHT);
uint32_t RED = FIRST.Color(BRIGHT,0,0);
uint32_t DARK = FIRST.Color(0,0,0);
uint32_t GREEN = FIRST.Color(0,BRIGHT,0);

int DELAY_VAL = 30;
uint32_t CURR_COLOR = RED;

void setup(){
    FIRST.begin();
    SECOND.begin();
    THIRD.begin();
    FOURTH.begin();
}

void loop(){

    // for each for each of these 'bulbs', 
    // we want it to start slow, then light up as we go
    // warm up sequence? Start them slower and then get to full speed

    setBulb(FIRST);
    clearStrip(FIRST);

    setBulb(SECOND);
    clearStrip(SECOND);

    setBulb(THIRD);
    clearStrip(THIRD);

    setBulb(FOURTH);
    clearStrip(FOURTH);

}

void setBulb(Adafruit_NeoPixel currStrip){
    /**
     * @brief Fills the current strip with the currColor
     * There is an adjustable delay value in this function
    */
    currStrip.fill(CURR_COLOR, 0, LEN_CYCLO);
    currStrip.show();
    delay(DELAY_VAL);
}

void clearStrip(Adafruit_NeoPixel currStrip){
    /**
     * @brief Clears current Strip
     * 
    */
    currStrip.clear();
    currStrip.show();
}