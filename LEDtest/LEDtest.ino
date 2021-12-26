#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif
 
////////////////////// Neo Pixel and Related Vairables ////////////////////// 
//pin associated with graph
#define PIN_GRAPH 4
//total count of LEDs in graph
#define GRAPH_PIXEL 30

//graph LEDs
Adafruit_NeoPixel graph(GRAPH_PIXEL, PIN_GRAPH, NEO_GRB + NEO_KHZ800);
uint32_t PURPLE = graph.Color(255,0,150.0);
uint32_t RED = graph.Color(255,0,0);
uint32_t DARK = graph.Color(0,0,0);

unsigned long delayTime = 10;
unsigned long currentTime = millis();
unsigned long previousTime = millis();
//true is increasing
//false is decreasing
bool increaseORdecrease = true;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  graph.begin();
  graph.show();
  Serial.begin(9600);
  Serial.print(PURPLE);
  Serial.print("\n");
}

void loop() {
  currentTime = millis();

  if(previousTime - currentTime < delayTime){
    //this means that enough time has passed for the lights to darken/lighten
    
    if(i > 255 && increaseORdecrease){
      //Start decrementing the i count
      increaseORdecrease = false;
    }
    
    if(i < 0){
      //Start incrementing the i count
      increaseORdecrease = true;
    }

    if(increaseORdecrease){
      i++;
    }else{
      i--;
    }
    //fill the graph
    graph.fill(DARK, 0, GRAPH_PIXEL);
    graph.show();
    graph.fill(graph.Color(i,0, (i*(150.0/255.0))), 0, GRAPH_PIXEL);
    graph.show();
    previousTime = millis();  
  }
  
}