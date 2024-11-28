#include <Wire.h>
#include <RTClib.h>

// Costanti dei pin
const int BUTTON_PIN = 12; // Arduino pin collegato al pulsante
const int RELAY_PIN = 7;   // Arduino pin collegato al relè

// Variabili
int relayState = LOW;       // Stato corrente del relè
int lastButtonState;        // Stato precedente del pulsante
int currentButtonState;     // Stato corrente del pulsante

RTC_DS3231 rtc;             // Oggetto RTC

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Pulsante in modalità input pull-up
  pinMode(RELAY_PIN, OUTPUT);        // Relè in modalità output

  currentButtonState = digitalRead(BUTTON_PIN);

  if (!rtc.begin()) {
    Serial.println("Errore: RTC non trovato!");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC ha perso l'ora, impostare l'orologio.");
    // Imposta l'ora iniziale (esempio: 1 gennaio 2024, 00:00:00)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void toggleButton() {
  lastButtonState = currentButtonState;      // Salva lo stato precedente
  currentButtonState = digitalRead(BUTTON_PIN); // Legge lo stato attuale

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("Pulsante premuto");
    // Cambia lo stato del relè manualmente
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState);
  }
}

void timedControl() {
  DateTime now = rtc.now(); // Ottieni l'ora corrente

  // Controlla se è lunedì-venerdì (1-5)
  if (now.dayOfTheWeek() >= 1 && now.dayOfTheWeek() <= 5) {
    // Accensione alle 7:00
    if (now.hour() == 7 && now.minute() == 0 && relayState == LOW) {
      relayState = HIGH;
      Serial.println("Relè attivato automaticamente");
      digitalWrite(RELAY_PIN, relayState);
    }

    // Spegnimento alle 8:30
    if (now.hour() == 8 && now.minute() == 30 && relayState == HIGH) {
      relayState = LOW;
      Serial.println("Relè disattivato automaticamente");
      digitalWrite(RELAY_PIN, relayState);
    }
  }
}

void loop() {
  toggleButton(); // Controlla il pulsante
  timedControl(); // Controlla l'attivazione/disattivazione temporale
  delay (200);
  /*DateTime now = rtc.now();
  Serial.print("Ora attuale: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.println(now.minute());
  */
}
