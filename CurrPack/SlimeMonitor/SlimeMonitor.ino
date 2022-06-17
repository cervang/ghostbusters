#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

/////////////////////// Variables for the NeoPixels ///////////////////////

#define GRAPH_PIN 5
#define SLIME_PIN 3

#define LEN_GRAPH 12
#define LEN_SLIME 7

Adafruit_NeoPixel GRAPH(LEN_GRAPH, GRAPH_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SLIME(LEN_SLIME, SLIME_PIN, NEO_GRB + NEO_KHZ800);

// So I don't burn my eyes with testing
#define BRIGHT 25
uint32_t GREEN = SLIME.Color(0,BRIGHT,0);
uint32_t BLUE = SLIME.Color(0,0,BRIGHT);

int slimeCount = 1;
int graphCount = 1;
unsigned long prevTime = millis();
unsigned long currTime = millis();

void setup(){
    GRAPH.begin();
    SLIME.begin();
}

void loop(){

    currTime = millis();

    if (currTime - prevTime > 100){
      // this is when we update the different slime and graph indexes 
      // they are of different lengeths, make sure it's reflected 
      // slime
      if (slimeCount <= LEN_SLIME){
        SLIME.fill(GREEN, 0, slimeCount);
        SLIME.show();
        slimeCount++;
      }else{
        SLIME.clear();
        SLIME.show();
        slimeCount = 1;
      }

      // graph
      if (graphCount <= LEN_GRAPH){
        GRAPH.fill(BLUE, 0, graphCount);
        GRAPH.show();
        graphCount++;
      }else{
        GRAPH.clear();
        GRAPH.show();
        graphCount = 1;
      }
      // update the prevTime
      prevTime = millis();
    }
    // do it all over again

    
    



}
