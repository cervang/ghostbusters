#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

//circuito.io for breadboard

#define PIN_GRAPH 4
#define PIN_CYCLO 6 
//#define BLUE_THIRD_PIN_SWITCH 2
#define THIRD_SWITCH_PIN 11
//#define OUTPUT_THIRD_SWITCH 5
//total LEDs in graph
#define GRAPH_PIXEL 15
//total LEDs in cyclo
#define CYCLO_PIXEL 20
//count of LEDs in each individual tube
#define CYCLO_TUBE 5


//graph LEDs
Adafruit_NeoPixel graph(GRAPH_PIXEL, PIN_GRAPH, NEO_GRB + NEO_KHZ800);
//cyclo LEDs
Adafruit_NeoPixel cyclo(CYCLO_PIXEL, PIN_CYCLO, NEO_GRB + NEO_KHZ800);

//bright is mostly for not burning my eyes during testing
//used to control the brightness of LEDs
int bright = 255;
//colors used in the program and for testing
uint32_t blue = graph.Color(0,0,bright);
uint32_t red = graph.Color(bright,0,0);
uint32_t green = graph.Color(0,bright,0);
uint32_t dark = graph.Color(0,0,0);


int set_up = true;
//start is used to store the value of the cyclo index
int start = 0;
//graph pixel curr used to store value of current index of graph pixel
int graph_pixel_curr = 1;
//used in start_up sequence- used to keep track of rundown index
int run_down_index = 0;
//default fade delay
int fade_delay = 2;
//default button state
int buttonState = 0;
//tesing button
int buttonState2 = 0;

//used to keep track of event times- making sure they don't get stuck in a process
unsigned long eventTime_1 = 25; //default graph wait time 125
unsigned long eventTime_2 = 200; //default cyclo wait time 200
//also used to make sure time is divided between the two
unsigned long currTime = millis();
unsigned long prevTime_1 = millis();
unsigned long prevTime_2 = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  cyclo.begin();
  pinMode(THIRD_SWITCH_PIN, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  buttonState = digitalRead(THIRD_SWITCH_PIN);
  Serial.print("\nButtonState: ");
  Serial.print(buttonState);
  
  //if button is on
  if(buttonState == LOW){
    //tell the board to make the gun go burr
    Serial.print("\n\t\tButtonStat LOW\n");
    Serial.print("\n\t\tButton On\n");
    
    currTime = millis();
    
    if(currTime - prevTime_1 > eventTime_1){
      
      if(set_up){
        //run the start up sequence 
        //took me a little bit to figure out, but this is the rundown logic
        //if curr pixal is greater than the current pixel running down, then fill the graph
        //otherwise, let the running down pixal keep going
        if(graph_pixel_curr > (GRAPH_PIXEL-run_down_index) ){  
          //clear the graph
          graph.clear();
          //fill the graph from the bottom with color
          graph.fill(blue, 0, graph_pixel_curr);
          graph.show();
          //make the cyclo light up a bit
          cyclo.fill(dark, 0, CYCLO_PIXEL);
          cyclo.show();
          cyclo.fill(graph.Color( ( bright / ((GRAPH_PIXEL+1) - graph_pixel_curr)) , 0 , 0), 0, CYCLO_PIXEL);
          cyclo.show();
          //wake_up_cyclo(graph_pixel_curr);
          //increment the curr pixal
          graph_pixel_curr++;
          //reset rundown pixel
          run_down_index = 0;

          //this means that the graph is now filled for the first time, meaning startup is over
          if(graph_pixel_curr > GRAPH_PIXEL){
            //setting bargraph values back to start so graph fills from bottom
            graph_pixel_curr = 1;
            //make sure it doesn't run the setup again
            set_up = false;
            //I added this function because it looks cool
            //start_up(3);
            //start_up(2);
            //start_up(1);
            //start_up(1);
          }
        }else{
          //set the pixel to blue
          graph.setPixelColor(GRAPH_PIXEL-run_down_index, blue);
          graph.show();
          //program the restep to be dark
          graph.setPixelColor(GRAPH_PIXEL-run_down_index, dark);
          //increment the rundown pixel
          run_down_index++;
          
        }   
  
      }else{
        //run steady state => run_up();
        //graph_pixel_curr is the variable that keeps track of the pixel count
        graph.fill(blue, 0, graph_pixel_curr);
        graph.show();
        
        if(graph_pixel_curr >= GRAPH_PIXEL){
          //if graph_pixel_curr is at the end of graph pixel count, reset to 1,
          graph_pixel_curr = 1;
        }else{
          //else have graph_pixel_curr increase by one
          graph_pixel_curr++;
        }
      }
      //resets the time piece so that the process can run again
      prevTime_1 = currTime;
    }
    //this was added because the graph was clearing before it would fully fill during 
    //rundown sequence in start_up
    if(!set_up)graph.clear();

    //cyclo controls - this will not run during start up
    if( (currTime - prevTime_2 > eventTime_2) && !set_up){
      //returns the starting pixel index, allowing for next itteration to acknowledge it
      start = fade_tube(start, fade_delay);
      prevTime_2 = currTime;
    }
    cyclo.clear();
    }

    //if button is off
    if(buttonState == HIGH){
      //Clear is not working- turn all the pixels to dark
      Serial.print("\n\t\tButtonStat HIGH\n");
      Serial.print("\n\t\tButton Off\n");
      //digitalWrite(OUTPUT_THIRD_SWITCH, LOW);
      //digitalWrite(BLUE_THIRD_PIN_SWITCH, LOW);
      cyclo.fill(dark, 0, CYCLO_PIXEL);
      graph.fill(dark, 0, GRAPH_PIXEL);
      //show all pixels as dark
      cyclo.show();
      graph.show();   
      //reset start_up so sequence will happen again
      set_up = true;   
      //reset graph so starts from bottom next time sequence runs again
      graph_pixel_curr = 1;
    }
  
}

void wake_up_cyclo(int curr_pixel){
  //theoretically, this would be cool
  //okay yeah it's cool lmao
    for(int i = 0; i <= int( bright / ((GRAPH_PIXEL+1) - curr_pixel)); i++){
    //cyclo.Color(255-i,0,0) -> Allows you to control the color brightness with forloop
    //cyclo.fill(color, starting index, number of LEDs to fill from starting index); 
    //for Rene, change 4 to 5     
    cyclo.fill(cyclo.Color(i,0,0), 0, CYCLO_PIXEL);  
    cyclo.show();
    //fade_delay is set to 1 when active, 4 when in startup
    delay(fade_delay+4);
  } 
  cyclo.fill(dark, 0, CYCLO_PIXEL);  
  cyclo.show();
}

/* Fading the individual light tubes 
START : The index of the neopixal in the area
FADE_DELAY : Delay of the gradient- used in for loop
*/
int fade_tube(int START, int FADE_DELAY){

  //if START is greater than the pixel count, reset it to 0
  if(START >= CYCLO_PIXEL){
    START = 0;
  }
  
  //this for loop creates a fade effect
  for(int i = 0; i <= bright; i++){
    //cyclo.Color(255-i,0,0) -> Allows you to control the color brightness with forloop
    //cyclo.fill(color, starting index, number of LEDs to fill from starting index);     
    cyclo.fill(cyclo.Color(bright-i,0,0), START, CYCLO_TUBE);  
    cyclo.show();
    //fade_delay is set to 1 when active, 4 when in startup
    delay(FADE_DELAY);
  }  
  //increments the starting index
  return START + CYCLO_TUBE;
}


void start_up(int wait_time){
  /**
   * Start_up is a function that looks cool- both Graph and Cyclo flash red. 
   * Wait time is a variable that should be between the values of 4 and 1. 
   *  This controls the 'fade' time 
  */
  cyclo.clear();
  graph.clear();
  for(int k = 0; k < bright; k++){
    cyclo.fill(graph.Color(bright-k,0,0),0,CYCLO_PIXEL);
    graph.fill(graph.Color(bright-k,0,0),0,GRAPH_PIXEL);
    cyclo.show();
    graph.show();
    delay(wait_time);
  }
  cyclo.fill(dark,0,CYCLO_PIXEL);
  graph.fill(dark,0,GRAPH_PIXEL);
  cyclo.show();
  graph.show();
}
