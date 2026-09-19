#define LDR_PIN A0
#define PIR_PIN 2

#define STREET_LIGHT_1 9
#define STREET_LIGHT_2 10
#define STREET_LIGHT_3 11

// Adjust this value according to your LDR setup
const int DARK_THRESHOLD = 500;

void setup() {
  Serial.begin(9600);

  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  pinMode(STREET_LIGHT_1, OUTPUT);
  pinMode(STREET_LIGHT_2, OUTPUT);
  pinMode(STREET_LIGHT_3, OUTPUT);

  analogWrite(STREET_LIGHT_1, 0);
  analogWrite(STREET_LIGHT_2, 0);
  analogWrite(STREET_LIGHT_3, 0);

  Serial.println("Smart Street Light Started");
}

void setLights(int brightness) {
  analogWrite(STREET_LIGHT_1, brightness);
  analogWrite(STREET_LIGHT_2, brightness);
  analogWrite(STREET_LIGHT_3, brightness);
}

void loop() {
  int lightLevel = analogRead(LDR_PIN);
  int motion = digitalRead(PIR_PIN);

  Serial.print("LDR: ");
  Serial.print(lightLevel);

  Serial.print(" | Motion: ");
  Serial.println(motion ? "YES" : "NO");

  // Dark condition
  if (lightLevel < DARK_THRESHOLD) {

    // Motion detected
    if (motion == HIGH) {

      // Full brightness
      setLights(255);

      Serial.println("Night + Motion -> Lights FULL");

    } else {

      // Low brightness
      setLights(80);

      Serial.println("Night + No Motion -> Lights DIM");
    }

  } else {

    // Daytime - lights OFF
    setLights(0);

    Serial.println("Daytime -> Lights OFF");
  }

  delay(500);
}
