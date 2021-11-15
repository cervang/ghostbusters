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
int cyclo_init_delay = 500;
int runUp = 125;
int set_up = false;
int start = 0;
int graph_pixel_curr = 1;

unsigned long eventTime_1 = 152; //the graph wait time 125
unsigned long eventTime_2 = 200; //the cyclo wait time 200

unsigned long currTime = millis();
unsigned long prevTime_1 = millis();
unsigned long prevTime_2 = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  cyclo.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  currTime = millis();

  //so, every 125 for the bar graph, a light will be lit
  //then the graph will reset
  
  if(currTime - prevTime_1 > eventTime_1){
    if(set_up){
        //run the 
    }else{
      //run steady state => run_up();
      graph.fill(blue, 0, graph_pixel_curr);
      graph.show();
      if(graph_pixel_curr >= GRAPH_PIXEL){
        graph_pixel_curr = 1;
      }else{
        graph_pixel_curr++;
      }
    }
    prevTime_1 = currTime;
  }
  graph.clear();
  
  //at the same time, every cyclo will be fun in a for loop
  if(currTime - prevTime_2 > eventTime_2){
    start = fade_tube(start, 1);
  }
  cyclo.clear();
  
}



/* Fading the individual light tubes */
int fade_tube(int START, int FADE_DELAY){
  if(START >= 16){
    START = 0;
  }
  for(int i = 0; i <= 255; i++){
    cyclo.fill(cyclo.Color(255-i,0,0), START, 4);  
    cyclo.show();
    delay(FADE_DELAY);
  }  
  return START + 4;
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
