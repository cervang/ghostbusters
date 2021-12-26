


#define GUN_PIN 33
//TODO: Implement later if we want this.
//For now, allow it to control the pack with just the third
//#define FIRST_SWITCH_PIN 27
//#define SECOND_SWITCH_PIN 28

//#define OUTPUT_SECOND_SWITCH 24
#define THIRD_SWITCH_PIN 2 
//pins we write to turn on the gun 
#define OUTPUT_THIRD_SWITCH 4
#define OUTPUT_THIRD_SWITCH_PIN_2 6

//controls the state of the gun, allowing us to moniter change
#define STATE_CHANGE_PIN 8
#define OUTPUT_modePin 10

//tells the second arduino to turn off the gun
#define ON_PIN 12
//#define OFF_PIN 11

unsigned long currTime = millis();
unsigned long prevTime = millis();
unsigned long eventTime = 45;



//default button state
//int FIRST_SWITCH = 0;
//int SECOND_SWITCH = 0;
int THIRD_SWITCH = 0;

int STATE_CHANGE = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
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

  currTime = millis();
  if(currTime - prevTime > eventTime){
    //need time for the gun to acknowledge the change, this will be the way
    //turn off the signal
    digitalWrite(OUTPUT_modePin, LOW); 
    //digitalWrite(7, LOW);
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
    //digitalWrite(7, HIGH);
    //wait for a second for hasbro to acknowledge it
    //take currentTime to compare for later 
  }
      
}
