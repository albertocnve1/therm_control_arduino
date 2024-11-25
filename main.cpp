const int relayPin = 7;       // Pin relè
const int buttonPin = 12;     // Pin pulsante

bool relayState = LOW;        // Stato iniziale del relè
bool lastButtonState = HIGH;  // Stato iniziale del pulsante (HIGH per pull-up)
bool currentButtonState = HIGH;

void setup() {
  pinMode(relayPin, OUTPUT);    // Imposta il pin del relè come output
  pinMode(buttonPin, INPUT_PULLUP); // Abilita pull-up interno sul pulsante
  digitalWrite(relayPin, LOW); // Spegne il relè all'avvio
}

void loop() {
  currentButtonState = digitalRead(buttonPin); // Leggi lo stato del pulsante

  // Controlla se il pulsante è stato premuto (transizione da HIGH a LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    relayState = !relayState; // Inverti lo stato del relè
    digitalWrite(relayPin, relayState ? HIGH : LOW); // Applica il nuovo stato al relè
    delay(50); // Debounce per evitare doppie letture rapide
  }

  lastButtonState = currentButtonState; // Aggiorna lo stato precedente del pulsante
}