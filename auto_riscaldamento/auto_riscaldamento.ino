// constants won't change
const int BUTTON_PIN = 12; // Arduino pin connected to button's pin
const int RELAY_PIN  = 7; // Arduino pin connected to relay's pin

// variables will change:
int relayState = LOW;   // the current state of relay
int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN, OUTPUT);        // set arduino pin to output mode

  currentButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");
    // toggle state of relay
    relayState = !relayState;
    // control relay arccoding to the toggled state
    digitalWrite(RELAY_PIN, relayState); 
  }
}
