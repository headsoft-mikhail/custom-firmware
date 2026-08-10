const byte INPUT_PIN = A7;
const byte RELAY_PIN = 4;
const byte LED_PIN = LED_BUILTIN;

const int THRESHOLD_ADC = 41; // ≈0.2V * 1024 / 5V

const int SAMPLE_PERIOD = 100; // мс
const int TURN_ON_TIME_DELAY = 10000;     // мс
const int TURN_OFF_TIME_DELAY = 1000;     // мс

bool relayState = false;
bool isAboveThresholdPrev = false;

int timeAboveThreshold = 0;
int timeBelowThreshold = 0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  bool isAboveThreshold = analogRead(INPUT_PIN) >= THRESHOLD_ADC;

  digitalWrite(LED_PIN, isAboveThreshold);

  // При смене состояния входа сбрасываем счетчики
  if (isAboveThreshold != isAboveThresholdPrev) {
    timeAboveThreshold = 0;
    timeBelowThreshold = 0;
    isAboveThresholdPrev = isAboveThreshold;
  }

  if (isAboveThreshold) {
    if (!relayState && timeAboveThreshold < TURN_ON_TIME_DELAY) {
      timeAboveThreshold += SAMPLE_PERIOD;

      if (timeAboveThreshold >= TURN_ON_TIME_DELAY) {
        relayState = true;
        digitalWrite(RELAY_PIN, HIGH);
      }
    }
  } else {
    if (relayState && timeBelowThreshold < TURN_OFF_TIME_DELAY) {
      timeBelowThreshold += SAMPLE_PERIOD;

      if (timeBelowThreshold >= TURN_OFF_TIME_DELAY) {
        relayState = false;
        digitalWrite(RELAY_PIN, LOW);
      }
    }
  }

  delay(SAMPLE_PERIOD);
}
