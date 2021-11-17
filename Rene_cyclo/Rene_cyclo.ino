#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_GRAPH 4
#define PIN_CYCLO 6 
#define GRAPH_PIXEL 6
#define CYCLO_PIXEL 20
#define BUTTON_PIN 2

//for the first set of NEO
Adafruit_NeoPixel graph(GRAPH_PIXEL, PIN_GRAPH, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cyclo(CYCLO_PIXEL, PIN_CYCLO, NEO_GRB + NEO_KHZ800);

int bright = 255;
uint32_t blue = graph.Color(0,0,bright);
uint32_t red = graph.Color(bright,0,0);
uint32_t dark = graph.Color(0,0,0);
uint32_t green = graph.Color(0,bright,0);

int runUp = 125;
int set_up = true;
int start = 0;
int graph_pixel_curr = 1;
int j = 0;
int fade_delay = 2;
int buttonState = 0;

unsigned long eventTime_1 = 100; //the graph wait time 125
unsigned long eventTime_2 = 200; //the cyclo wait time 200

unsigned long currTime = millis();
unsigned long prevTime_1 = millis();
unsigned long prevTime_2 = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  cyclo.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  buttonState = digitalRead(BUTTON_PIN);

  //if button is on
  if(buttonState == LOW){
    currTime = millis();
    if(currTime - prevTime_1 > eventTime_1){
      if(set_up){
      
        //run the start up sequence 
        
        if(graph_pixel_curr > (GRAPH_PIXEL-j) ){  
          
          graph.clear();
          graph.fill(blue, 0, graph_pixel_curr);
          graph.show();
          graph_pixel_curr++;
          j = 0;
          if(graph_pixel_curr > GRAPH_PIXEL){
            graph_pixel_curr = 1;
            set_up = false;
            start_up(3);
            start_up(2);
            start_up(1);
            start_up(1);
          }
        }else{
          
          graph.setPixelColor(GRAPH_PIXEL-j, blue);
          graph.show();
          graph.setPixelColor(GRAPH_PIXEL-j, dark);
          j++;
        
        }   
  
      }else{
        //run steady state => run_up();
        //graph_pixel_curr is the variable that keeps track of the pixel count
        
        graph.fill(blue, 0, graph_pixel_curr);
        graph.show();
        //if graph_pixel_curr is at the end of graph pixel count, reset to 1,
        //else have graph_pixel_curr increase by one
        if(graph_pixel_curr >= GRAPH_PIXEL){
          graph_pixel_curr = 1;
        }else{
          graph_pixel_curr++;
        }
      }
      //resets the time piece so that the process can run again
      prevTime_1 = currTime;
    }
    if(!set_up)graph.clear();
    //at the same time, every cyclo will be fun in a for loop
    if( (currTime - prevTime_2 > eventTime_2) && !set_up){
      start = fade_tube(start, fade_delay);
      prevTime_2 = currTime;
    }
    cyclo.clear();
    }

    //if button is off
    if(buttonState == HIGH){

      cyclo.fill(dark, 0, CYCLO_PIXEL);
      graph.fill(dark, 0, GRAPH_PIXEL);
      cyclo.show();
      graph.show();   
      set_up = true;   
      graph_pixel_curr = 1;
    }
  
}



/* Fading the individual light tubes 
START : The index of the neopixal in the area
FADE_DELAY : Delay of the gradient- used in forloop
*/
int fade_tube(int START, int FADE_DELAY){

  //if START is greater than the pixel count, reset it to 0
  //For Rene, change 16 to 20
  if(START >= CYCLO_PIXEL){
    START = 0;
  }
  
  //this for loop creates a fade effect
  for(int i = 0; i <= 255; i++){
    //cyclo.Color(255-i,0,0) -> Allows you to control the color brightness with forloop
    //cyclo.fill(color, starting index, number of LEDs to fill from starting index); 
    //for Rene, change 4 to 5     
    cyclo.fill(cyclo.Color(255-i,0,0), START, 5);  
    cyclo.show();
    //fade_delay is set to 1 when active, 4 when in startup
    delay(FADE_DELAY);
  }  
  //increments the starting index
  //for Rene, change 4 to 5
  return START + 5;
}


void start_up(int wait_time){
  cyclo.clear();
  graph.clear();
  for(int k = 0; k < 255; k++){
    cyclo.fill(graph.Color(255-k,0,0),0,16);
    graph.fill(graph.Color(255-k,0,0),0,6);
    cyclo.show();
    graph.show();
    delay(wait_time);
  }
  cyclo.fill(dark,0,16);
  graph.fill(dark,0,6);
  cyclo.show();
  graph.show();
}
