#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_GRAPH 4
#define PIN_CYCLO 6 
#define GRAPH_PIXEL 6
#define CYCLO_PIXEL 16

//for the first set of NEO
Adafruit_NeoPixel graph(GRAPH_PIXEL, PIN_GRAPH, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cyclo(CYCLO_PIXEL, PIN_CYCLO, NEO_GRB + NEO_KHZ800);
uint32_t blue = graph.Color(0,0,255);
uint32_t red = graph.Color(255,0,0);
uint32_t dark = graph.Color(0,0,0);
uint32_t green = graph.Color(0,255,0);

int waitDown = 100;
int runUp = 125;
int set_up = true;

unsigned long startTime = millis();
unsigned long currTime = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  cyclo.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  startTime = millis();
  if(startTime - currTime > waitDown){
    if(set_up){
      start_graph();
    }else{
      run_up();
    }
  }
  
  run_cyclo();
}

void run_cyclo(){
  cyclo.fill(green, 0, CYCLO_PIXEL);
  cyclo.show();
  delay(waitDown);
  flashDark();
}

void runDown(int currPix){
  for(int j = GRAPH_PIXEL; j >= currPix; j--){
    graph.setPixelColor(j, blue);
    graph.show();
    delay(waitDown);
    graph.setPixelColor(j, dark);
  }
}

void run_up(){
  
  for(int i = 1; i <= GRAPH_PIXEL; i++){
    graph.fill(blue, 0, i);
    graph.show();
    delay(runUp);
    graph.clear();
  }
}

void start_graph(){
  /*lights are coded in parallel - this treats the code as the same in terms of receptors,
   * meaning we only have to code one of the strips to get the same amount of code in both of them
  */
  for(int i = 1; i <= 6; i++){
    runDown(i);
    graph.fill(blue, 0, i);
    graph.show();
    delay(100);
  }
  graph.clear();
  set_up = false;
  
}

void flashDark(){
  cyclo.fill(cyclo.Color(0,0,0));
  cyclo.show();
  delay(500);
}
