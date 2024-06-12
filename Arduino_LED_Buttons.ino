#define PERIOD_DELAY 1000

#define LED_PIN_1 9
#define BUTTON_PIN_1 8

#define LED_PIN_2 11
#define BUTTON_PIN_2 10

unsigned long button1TimeNow = 0;
unsigned long button2TimeNow = 0;

bool wasButton1Pressed = false;
bool wasButton2Pressed = false;

bool led1DelayCompleted = true; // Initially true so either button can be pressed first
bool led2DelayCompleted = true;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
  bool currentButton1State = digitalRead(BUTTON_PIN_1);
  bool currentButton2State = digitalRead(BUTTON_PIN_2);

  // Handle Button 1
  if (currentButton1State == LOW && !wasButton1Pressed && led2DelayCompleted) {
    wasButton1Pressed = true;
    button1TimeNow = millis();
    led1DelayCompleted = false; // Reset delay completion flag for button 1
  }

  if (wasButton1Pressed) {
    if (millis() - button1TimeNow < PERIOD_DELAY) {
      digitalWrite(LED_PIN_1, HIGH);
    } else {
      digitalWrite(LED_PIN_1, LOW);
      wasButton1Pressed = false;
      led1DelayCompleted = true; // Mark delay completion for button 1
    }
  }

  // Handle Button 2
  if (currentButton2State == LOW && !wasButton2Pressed && led1DelayCompleted) {
    wasButton2Pressed = true;
    button2TimeNow = millis();
    led2DelayCompleted = false; // Reset delay completion flag for button 2
  }

  if (wasButton2Pressed) {
    if (millis() - button2TimeNow < PERIOD_DELAY) {
      digitalWrite(LED_PIN_2, HIGH);
    } else {
      digitalWrite(LED_PIN_2, LOW);
      wasButton2Pressed = false;
      led2DelayCompleted = true; // Mark delay completion for button 2
    }
  }
}
