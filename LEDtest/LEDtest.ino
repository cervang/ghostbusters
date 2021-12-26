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
void setup() {
  // put your setup code here, to run once:
  graph.begin();
  graph.show();
  Serial.begin(9600);
  Serial.print(PURPLE);
  Serial.print("\n");
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(PURPLE);
  Serial.print("\n");
  //light up
  for(double i = 0.0; i < 255.0; i++){
    graph.fill(DARK, 0, GRAPH_PIXEL);
    graph.show();
    graph.fill(graph.Color(i,0, (i*(150.0/255.0))), 0, GRAPH_PIXEL);
    graph.show();
    delay(10);
  }
  //darken
  for(double i = 255.0; i > 0.0; i--){
    graph.fill(DARK, 0, GRAPH_PIXEL);
    graph.show();
    graph.fill(graph.Color(i,0, (i*(150.0/255.0))), 0, GRAPH_PIXEL);
    graph.show();
    delay(10);
  }

}
