#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define bright 50
#define GRAPH_COUNT 20
#define GUN_PIN 33
//TODO: Implement later if we want this.
//For now, allow it to control the pack with just the third
//#define FIRST_SWITCH_PIN 27
//#define SECOND_SWITCH_PIN 28

//#define OUTPUT_SECOND_SWITCH 24
#define THIRD_SWITCH_PIN 2 
//pins we write to turn on the gun 
#define OUTPUT_THIRD_SWITCH 3
#define OUTPUT_THIRD_SWITCH_PIN_2 4

//controls the state of the gun, allowing us to moniter change
#define STATE_CHANGE_PIN 5
#define OUTPUT_modePin 6

//tells the second arduino to turn off the gun
#define ON_PIN 12
//#define OFF_PIN 11

unsigned long currTime = millis();
unsigned long prevTime = millis();
unsigned long eventTime = 40;



//default button state
//int FIRST_SWITCH = 0;
//int SECOND_SWITCH = 0;
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
  pinMode(THIRD_SWITCH_PIN, INPUT_PULLUP);
  pinMode(STATE_CHANGE_PIN, INPUT_PULLUP);
  
}

void loop() {

  //state of the first switch check
  //FIRST_SWITCH = digitalRead(FIRST_SWITCH_PIN);
  //state of the second switch
  //SECOND_SWITCH = digitalRead(SECOND_SWITCH_PIN); 
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
   * TODO: Rewire the switch back to original
   * This would be the logic when it is done
  */ 
  if(THIRD_SWITCH == LOW){
    //third switch is active
    //send message to the gun to turn it on
    Serial.print("\n\t\tTHIRD_SWITCH ON");
    digitalWrite(OUTPUT_THIRD_SWITCH, HIGH); 
    digitalWrite(OUTPUT_THIRD_SWITCH_PIN_2, HIGH);
    //send message to second arduino to turn on
    digitalWrite(ON_PIN, HIGH);
  }else if(THIRD_SWITCH == HIGH){
    //third switch is off
    //send message via arduino to turn it off
    Serial.print("\n\t\tTHIRD_SWITCH OFF HIGH");
    digitalWrite(OUTPUT_THIRD_SWITCH, LOW);
    digitalWrite(OUTPUT_THIRD_SWITCH_PIN_2, LOW); 
    //send message to second arduino to turn off
    digitalWrite(ON_PIN, LOW);
  }
  
  if(currTime - prevTime > eventTime){
    //need time for the gun to acknledge the change, this will be the way
    //turn off the signal
    digitalWrite(OUTPUT_modePin, LOW); 
    prevTime = currTime;
  }
  
  /**
   * STATE_CHANGE shows the modes of the gun. 
   * TODO: Make a function to return the state of the gun
  */
  if(STATE_CHANGE == LOW && THIRD_SWITCH == LOW){
    //this switches the modes of the gun
    //if the button is low (meaning it's pressed)
    Serial.print("\t\n\t\tSTATE_CHANGE is LOW ");
    //send signal to the board showing that change
    digitalWrite(OUTPUT_modePin, HIGH);
    //wait for a second for hasbro to acknowledge it
    //take currentTime to compare for later
    currTime == millis();
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
