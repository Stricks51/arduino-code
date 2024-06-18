#include <Keyboard.h> //include the keyboard library

// define is like creating const in JS as we give it a variable that cannot be reassigned
#define PERIOD_DELAY 1000 // the delay time of of registering a keypress

#define LED_PIN_1 9 // LED connected to button 1
#define BUTTON_PIN_1 8 //button 1

#define LED_PIN_2 12 // LED connected to button 2
#define BUTTON_PIN_2 11 //button 2

// stores the time in which the button is pressed for (e.g. holding down button will keep LED on until released)
unsigned long button1TimeNow = 0;
unsigned long button2TimeNow = 0;

// boolean to keep track of which button is pressed
bool wasButton1Pressed = false;
bool wasButton2Pressed = false;

// boolean to keep track of which LED has finished according to the "PREIOD_DELAY"
bool led1DelayCompleted = true; // initially set to true so either button can be pressed first
bool led2DelayCompleted = true;

//needed to setup the arduino and its connections
void setup() {
  Serial.begin(9600); //allows the serial to communicate to help debug (like console.log)
  pinMode(BUTTON_PIN_1, INPUT_PULLUP); // sets the mode for pins: input_pullup to show it as an input pin with pull up resistors
  pinMode(LED_PIN_1, OUTPUT); // sets the mode for pins: output to show they will provide an output (e.g. light up led)
  pinMode(BUTTON_PIN_2, INPUT_PULLUP); // sets the mode for pins: input_pullup to show it as an input pin with pull up resistors
  pinMode(LED_PIN_2, OUTPUT); // sets the mode for pins: output to show they will provide an output (e.g. light up led)

  Keyboard.begin(); // initiating the keyboard library
}

// the function continuously runs after setup
void loop() {
  // check current state of the buttons (if the are pressed or not)
  bool currentButton1State = digitalRead(BUTTON_PIN_1);
  bool currentButton2State = digitalRead(BUTTON_PIN_2);

  // handling the button 1 & led 1

  //setup to prevent overlapping presses with the delay, setting it up to ensure wasButton1Pressed is only true once per loop
  if (currentButton1State == LOW && !wasButton1Pressed && led2DelayCompleted) { 
    //first checks button state, LOW means buttons has been pressed an pin pulls to 0 volts
    // and checks if button1 was pressed for the first time, prevents code from repeating when button is held down
    // and ensures that the other LED (led2) has finished its delay time to not overlap the LED's
    
    wasButton1Pressed = true; // if all conditions are true, turn the wasButton1pressed to true, and begin executing code inside "if (wasButton1Pressed){}"
    button1TimeNow = millis(); //records current time of the button for the delay
    led1DelayCompleted = false; // false indicates that delay period is now running for LED 1

    Keyboard.write(' '); //send w press (for testing)
  }

// main code for button press to turn on and off the LED
  if (wasButton1Pressed) { // when button 1 is pressed (since it was set to true in previous code)
    if (millis() - button1TimeNow < PERIOD_DELAY) { // check if current time - the time from when the button was pressed is smaller than the delay period set 
      digitalWrite(LED_PIN_1, HIGH); // if true have the LED on
    } else {
      digitalWrite(LED_PIN_1, LOW); //if false (delay period is finished) have the LED off
      wasButton1Pressed = false; // reset the button press value to false meaning it is no longer being pressed
      led1DelayCompleted = true; // mark the period delay completed, meaning LED is off
    }
  }

  // same as above but for Button 2
  if (currentButton2State == LOW && !wasButton2Pressed && led1DelayCompleted) {
    wasButton2Pressed = true;
    button2TimeNow = millis();
    led2DelayCompleted = false; 
    Keyboard.write(' '); 
  }

  if (wasButton2Pressed) {
    if (millis() - button2TimeNow < PERIOD_DELAY) {
      digitalWrite(LED_PIN_2, HIGH);
    } else {
      digitalWrite(LED_PIN_2, LOW);
      wasButton2Pressed = false;
      led2DelayCompleted = true; 
    }
  }
}
