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
#define BRIGHT 255
//colors used in the program and for testing
uint32_t BLUE = graph.Color(0,0,BRIGHT);
uint32_t RED = graph.Color(BRIGHT,0,0);
//make it a percentage to correlate with variable BRIGHT
uint32_t ORANGE = graph.Color(BRIGHT, int(BRIGHT*(165/255)), 0);
uint32_t PURPLE = graph.Color(BRIGHT,0,int(BRIGHT*(150/255)));
uint32_t GREEN = graph.Color(0,BRIGHT,0);
uint32_t DARK = graph.Color(0,0,0);
////////////////////// ////////////////////// //////////////////////


////////////////////// Main Loop Values //////////////////////
//int thirdSwitchState = 0;
int start_up = true;
int warm_up = false;
int active = false;
int START = 0;
int run_down_index = 0;
int graph_pixel_curr = 1;

////////////////////// ////////////////////// //////////////////////  
//it takes three seconds to start up the gun and fire
////////////////////// Gun Variables //////////////////////
#define GUN_SWITCH_PIN 2
uint32_t currColor = RED;
int CUR_GUN_STATE = 1;
int gunSwitchWait = 150;
unsigned long currGunTime = millis(); 
unsigned long prevGunTime = millis();
////////////////////// ////////////////////// //////////////////////

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  cyclo.begin();
  pinMode(THIRD_SWITCH_PIN, INPUT_PULLUP);
  pinMode(GUN_SWITCH_PIN, INPUT_PULLUP);

}


void loop() {
    //redesigning the system so start up sequence is more fluid
    int thirdSwitchState = digitalRead(THIRD_SWITCH_PIN);
    int gunButtonVal = digitalRead(GUN_SWITCH_PIN);

    Serial.print("\nThirdSwitch: ");
    Serial.print(thirdSwitchState);

    if(thirdSwitchState == LOW){
        Serial.print("\n\t\tThirdSwitch is LOW\n");
        Serial.print("\n\t\tPack is ON\n");
        currGunTime = millis();
        //this means the button is active - let the sequence run

        
        if(start_up){
            //run the set up sequence
            if(graph_pixel_curr <= (GRAPH_PIXEL-run_down_index) ){  
                //the pixel is still running down the graph
                //set the pixel to blue
                graph.setPixelColor(GRAPH_PIXEL-run_down_index, BLUE);
                graph.show();
                //program the restep to be dark
                graph.setPixelColor(GRAPH_PIXEL-run_down_index, DARK);
                //increment the rundown pixel
                run_down_index++;
            }else{
                //all pixels have been filled on the graph- the time for set_up is over
                //clear the graph
                graph.clear();
                //fill the graph from the bottom with color
                graph.fill(BLUE, 0, graph_pixel_curr);
                graph.show();
                //make the cyclo light up a bit
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
                    start_up = false;
                    //start the warm up
                    warm_up = true;
                }
            }
        }
        
        if(warm_up){
          //TODO: Adding warm up sequence
            //fade_tube(1);
            //if(done){
                warm_up = false;
                active = true;
            //}
        }

        if(gunButtonVal == LOW){
          if(currGunTime - prevGunTime > gunSwitchWait){
            gun_state();
            graph.fill(DARK, 0, GRAPH_PIXEL);
            graph.show();
            prevGunTime = currGunTime;
          }
        }

        if(active){
          //cyclotron is in an active state, make the thing spin
        }

    }else{
        //button is high - turn the pack off
        Serial.print("\n\t\tThirdSwitch is HIGH\n");
        Serial.print("\n\t\tPack is OFF\n");
        //reset warm up and start up sequences
        active = false;
        warm_up = false;
        start_up = true;
        graph_pixel_curr = 1;
        //clear function not workin in these cases
        graph.fill(DARK, 0, GRAPH_PIXEL);
        cyclo.fill(DARK, 0, CYCLO_PIXEL);
        graph.show();
        cyclo.show();


    }

}

/**
 *Returns an color to change the NEOPIXEL lights
*/
void gun_state(){
  //uint32_t GunColor;
  if(CUR_GUN_STATE > 3){
    //reset to 0
    CUR_GUN_STATE = 0;
  }
  switch (CUR_GUN_STATE) {
    case 0:
      // Orange would be the default
      //this would be the default state
      currColor = RED;
      break;
    case 1:
      // slime
      // return green
      currColor = GREEN;
      break;
    case 2:
      // ice
      // return blue
      currColor = BLUE;
      break;
    case 3:
      // firing
      currColor = PURPLE;
      break;
    default:
      //default would be red
      currColor = RED;
      break;
  }
  //increment
  CUR_GUN_STATE++;
  
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
    delay(4);
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
    cyclo.fill(currColor-i, START, CYCLO_TUBE);  
    cyclo.show();
    //fade_delay is set to 1 when active, 4 when in startup
    delay(FADE_DELAY);
  }  
  //increments the starting index
  //return START + CYCLO_TUBE;
}
