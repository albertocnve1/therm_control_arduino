// Configurazione dei pin
const int relayPin = 7;       // Pin relè
const int buttonPin = 12;     // Pin pulsante


void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT); // Resistenza di pull-up interna
  digitalWrite(relayPin, LOW);      // Spegne il relè all'inizio
  startMillis = millis();          // Inizializza il tempo
}

void loop() 
{
    if (digitalRead(buttonPin) == HIGH) {
        digitalWrite(relayPin, HIGH);
    } else {
        digitalWrite(relayPin, LOW);
    }
}
