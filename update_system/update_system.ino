#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

////////////////////// Neo Pixel and Related Vairables ////////////////////// 
//pin associated with graph
#define PIN_GRAPH 4
//total count of LEDs in graph
#define GRAPH_PIXEL 6
//graph LEDs
Adafruit_NeoPixel graph(GRAPH_PIXEL, PIN_GRAPH, NEO_GRB + NEO_KHZ800);

//pin associated with cyclo
#define PIN_CYCLO 6 
//total count of LEDs in cyclo
#define CYCLO_PIXEL 16
//count of LEDs in each individual tube
#define CYCLO_TUBE 4
//cyclo LEDs
Adafruit_NeoPixel cyclo(CYCLO_PIXEL, PIN_CYCLO, NEO_GRB + NEO_KHZ800);
////////////////////// ////////////////////// ////////////////////// 

////////////////////// SWITCH PIN ////////////////////// 
//#define BLUE_THIRD_PIN_SWITCH 2
#define THIRD_SWITCH_PIN 3

////////////////////// ////////////////////// ////////////////////// 

////////////////////// COLOR VARIABLES ////////////////////// 
//bright is for not burning my eyes during testing
//used to control the brightness of LEDs
// 0 <= BRIGHT <= 255
#define BRIGHT 255;
//colors used in the program and for testing
uint32_t BLUE = graph.Color(0,0,BRIGHT);
uint32_t RED = graph.Color(BRIGHT,0,0);
//make it a percentage to correlate with variable BRIGHT
uint32_t ORANGE = graph.color(BRIGHT*(255/255), BRIGHT*(165/255), 0);
uint32_t GREEN = graph.Color(0,BRIGHT,0);
uint32_t DARK = graph.Color(0,0,0);
////////////////////// ////////////////////// //////////////////////

////////////////////// Main Loop Values //////////////////////
int thirdSwitchState = 0;
int set_up = true;
int warm_up = false;
int START = 0;
////////////////////// ////////////////////// //////////////////////  


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  cyclo.begin();
  pinMode(THIRD_SWITCH_PIN, INPUT_PULLUP);

}


void loop{
    //redesigning the system so start up sequence is more fluid
    thirdSwitchState = digitalRead(THIRD_SWITCH_PIN);
    Serial.print("\nThirdSwitch: ");
    Serial.print(thirdSwitchState);

    if(buttonState == LOW){
        Serial.print("\n\t\tThirdSwitch is LOW\n");
        Serial.print("\n\t\tPack is ON\n");
        //this means the button is active - let the sequence run

        
        if(set_up){
            //run the set up sequence
            if(graph_pixel_curr <= (GRAPH_PIXEL-run_down_index) ){  
                //the pixel is still running down the graph
                //set the pixel to blue
                graph.setPixelColor(GRAPH_PIXEL-run_down_index, blue);
                graph.show();
                //program the restep to be dark
                graph.setPixelColor(GRAPH_PIXEL-run_down_index, dark);
                //increment the rundown pixel
                run_down_index++;
            }else{
                //all pixels have been filled on the graph- the time for set_up is over
                //clear the graph
                graph.clear();
                //fill the graph from the bottom with color
                graph.fill(blue, 0, graph_pixel_curr);
                graph.show();
                //make the cyclo light up a bit
                wake_up_cyclo(graph_pixel_curr);
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
                    //start the warm up
                    warm_up = true;
                }
            }
        }
        else if(warm_up){
            fade_tube(1);
            if(done){
                warm_up = false;
            }
        }



    }else{
        //button is high - turn the pack off
        Serial.print("\n\t\tThirdSwitch is HIGH\n");
        Serial.print("\n\t\tPack is OFF\n");
        //reset warm up and start up sequences
        warm_up = false;
        start_up = true;
        graph_pixel_curr = 1;
        //clear function not workin in these cases
        graph.fill(dark, 0, GRAPH_PIXEL);
        cyclo.fill(dark, 0, CYCLO_PIXEL);
        graph.show();
        cyclo.show();


    }

}

void wake_up_cyclo(int curr_pixel){
    //Each time the graph pixel is incremented, the cyclo is increased in brightness
    for(int i = 0; i <= int( BRIGHT / ((GRAPH_PIXEL+1) - curr_pixel)); i++){
    //cyclo.Color(255-i,0,0) -> Allows you to control the color brightness with forloop
    //cyclo.fill(color, starting index, number of LEDs to fill from starting index); 
    //for Rene, change 4 to 5     
    cyclo.fill(cyclo.Color(i,0,0), 0, CYCLO_PIXEL);  
    cyclo.show();
    //fade_delay is set to 1 when active, 4 when in startup
    delay(fade_delay+4);
  } 
  cyclo.fill(DARK, 0, CYCLO_PIXEL);  
  cyclo.show();
}

void fade_tube(int FADE_DELAY){
    /*START = start FADE_DELAY = delay*/
  //if START is greater than the pixel count, reset it to 0
  if(START >= CYCLO_PIXEL){
    START = 0;
  }
  
  //this for loop creates a fade effect
  for(int i = 0; i <= BRIGHT; i++){
    //cyclo.Color(255-i,0,0) -> Allows you to control the color brightness with forloop
    //cyclo.fill(color, starting index, number of LEDs to fill from starting index);     
    cyclo.fill(cyclo.Color(BRIGHT-i,0,0), START, CYCLO_TUBE);  
    cyclo.show();
    //fade_delay is set to 1 when active, 4 when in startup
    delay(FADE_DELAY);
  }  
  //increments the starting index
  //return START + CYCLO_TUBE;
}