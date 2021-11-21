#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define bright 50
#define GRAPH_COUNT 20
#define GUN_PIN 33
#define FIRST_SWITCH_PIN 27
#define OUTPUT_FIRST_SWITCH 23
#define SECOND_SWITCH_PIN 28
#define OUTPUT_SECOND_SWITCH 24
#define THIRD_SWITCH_PIN 29 
//because of rewiring, we don't need this for now 
//#define OUTPUT_THIRD_SWITCH 25
#define OUTPUT_modePin 41
#define STATE_CHANGE_PIN 37 //orange


//default button state
int FIRST_SWITCH = 0;
int SECOND_SWITCH = 0;
int THIRD_SWITCH = 0;
int CUR_GUN_STATE = 0;
int STATE_CHANGE = 0;

Adafruit_NeoPixel graph(GRAPH_COUNT, 6, NEO_GRB + NEO_KHZ800);


uint32_t red = graph.Color(bright,0,0);
uint32_t green = graph.Color(0,bright,0);
uint32_t blue = graph.Color(0,0,bright);
uint32_t orange = graph.Color(255,165,0);
uint32_t dark = graph.Color(0,0,0);
//default color would be red
uint32_t currColor = red;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  digitalWrite(GUN_PIN, 0);
  pinMode(FIRST_SWITCH_PIN, INPUT_PULLUP);
  pinMode(SECOND_SWITCH_PIN, INPUT_PULLUP);
  pinMode(THIRD_SWITCH_PIN, INPUT_PULLUP);
  pinMode(STATE_CHANGE_PIN, INPUT_PULLUP);
  
}

void loop() {

  //state of the first switch check
  FIRST_SWITCH = digitalRead(FIRST_SWITCH_PIN);
  //state of the second switch
  SECOND_SWITCH = digitalRead(SECOND_SWITCH_PIN); 
  //state of the third switch
  THIRD_SWITCH = digitalRead(THIRD_SWITCH_PIN);
  //state of the gun button
  STATE_CHANGE = digitalRead(STATE_CHANGE_PIN);
  
  Serial.print("\n_____________________________\n ");
  Serial.print("\nTHIRD_SWITCH: ");
  Serial.print(THIRD_SWITCH);
  Serial.print("\n");
  
  Serial.print("\nSTATE_CHANGE: ");
  Serial.print(STATE_CHANGE);
  Serial.print("\n");
  
  /**
   * TODO: Add logic for first switch 
   */
  if(FIRST_SWITCH == LOW){
    //if the switch is conencted, we need to ackknoledge it
    //if it is low, that means it is active
    //send a message via the arduino to help with activate it
    digitalWrite(OUTPUT_FIRST_SWITCH), HIGH); 
  }else{
    //if FIRST_SWITCH == HIGH, this means it needs to be off
    //send message via arduino to turn it off
    digitalWrite(OUTPUT_FIRST_SWITCH), LOW);
  }
  /**
   * TODO: Add logic for second switch 
   */
  if(SECOND_SWITCH == LOW){
    //second switch is active
    //send a message via the arduino to help with activate it
    digitalWrite(OUTPUT_SECOND_SWITCH), HIGH); 
  }else{
    //second switch is off
    //send message via arduino to turn it off
    digitalWrite(OUTPUT_SECOND_SWITCH), LOW); 
  }


  
  /**
   * Turning on the lights
   * TODO: Adding the other three buttons with this in the logic
   * All three switches must be high for the wand to work, so the pack should reflect that
  */
  if( (THIRD_SWITCH == HIGH) && (SECOND_SWITCH == LOW) && (FIRST_SWITCH == LOW)){
    //the button is in the on state
    //run start up start up sequence here 
    graph.fill(green, 0, 20);
    graph.show();
  }else{
    //button is off
    //this would be the turning off / power down sequence 
    graph.fill(dark, 0, 20);
    graph.show();
  }

  /**
   * STATE_CHANGE shows the modes of the gun. 
   * TODO: Make a function to return the state of the gun
  */
  if(STATE_CHANGE == LOW){
    //this switches the modes of the gun
    //if the button is low (meaning it's pressed)
    Serial.print("\t\nSTATE_CHANGE is LOW ");
    //send signal to the board showing that change
    digitalWrite(OUTPUT_modePin, HIGH);
    //wait for a second for hasbro to acknowledge it
    delay(100); 
    //turn off the signal
    digitalWrite(OUTPUT_modePin, LOW); 
    //get color for the neopixals
    gun_state();
    //currColor would be changed now, so update the strips
    //TODO: Add the start up sequence 
    //For now, just update the strip
    graph.fill(currColor, 0, GRAPH_COUNT);
  }
      
}

/**
 *Returns an color to change the NEOPIXEL lights
*/
void gun_state(){
  uint32_t GunColor;
  if(CUR_GUN_STATE > 3){
    //reset to 0
    CUR_GUN_STATE = 0;
  }
  switch (CUR_GUN_STATE) {
    case 0:
      // Orange would be the default
      //this would be the default state
      currColor = red;
      break;
    case 1:
      // slime
      // return green
      currColor = green;
      break;
    case 2:
      // ice
      // return blue
      currColor = blue;
      break;
    case 3:
      // firing
      currColor = orange;
      break;
    default:
      //default would be red
      currColor = red;
      break;
  }
  //increment
  CUR_GUN_STATE++;
}
