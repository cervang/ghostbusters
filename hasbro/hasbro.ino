#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define bright 50
#define PIN_BUTTON 29
#define GUN_PIN 33
#define TEST_1 31 //green
#define modePin 41
#define TEST_2 37 //orange


//default button state
int buttonState = 0;
int test1 = 0;
int orange = 0;
//tesing button
int prev_button = 0;
int val = 0;

Adafruit_NeoPixel graph(20, 6, NEO_GRB + NEO_KHZ800);

uint32_t green = graph.Color(0,bright,0);
uint32_t dark = graph.Color(0,0,0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  graph.begin();
  digitalWrite(GUN_PIN, 0);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(TEST_1, INPUT_PULLUP);
  pinMode(TEST_2, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  buttonState = digitalRead(PIN_BUTTON);
  test1 = digitalRead(TEST_1);
  orange = digitalRead(TEST_2);
  Serial.print("\n_____________________________\n ");
  Serial.print("\nButtonState: ");
  Serial.print(buttonState);
  Serial.print("\n");
  
  Serial.print("\nGreen: ");
  Serial.print(test1);
  Serial.print("\n");
  
  Serial.print("\nOrange: ");
  Serial.print(orange);
  Serial.print("\n");
  
  /**/
  if(buttonState == HIGH){
    //the button is in the on state
    //this will be the start up sequence here 
    graph.fill(green, 0, 20);
    graph.show();
  }else{
    //button is off
    //this would be the turning off / power down sequence 
    graph.fill(dark, 0, 20);
    graph.show();
  }
  if(orange == LOW){
    //send a charge to the pin
    //this switches the modes of the gun
    //if the button is low (meaning it's pressed)
    Serial.print("\t\tOrange is LOW ");
    //send signal to the board showing that change
    digitalWrite(modePin, HIGH);
    //wait for a second for it to acknowledge it
    delay(100); 
    //turn off the signal
    digitalWrite(modePin, LOW); 
 
  }
      

  //delay(1500);
}
