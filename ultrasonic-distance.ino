
// UltraSonic-Distance-Sensor PINs
#define echoPin 4
#define trigPin 3

// Park-Sensor value
unsigned int range2Obstacle;
unsigned int tmp_range2Obstacle;

void setup() {

  // UltraSonic-Distance-Sensor PINs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  range2Obstacle = ultrasonicScan();

  delay(1000);
  return;  
}

// @return: unsigned int
unsigned long ultrasonicScan() {

  // recieve signal to distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  tmp_range2Obstacle = pulseIn(echoPin, HIGH);

  return ((tmp_range2Obstacle / 2) / 29.1);
}

// Annäherungsfunktion
double validateSharpRange(double distance) {
  
  double erg = 11 - squaref((119 - 2 * distance + 3));
  return erg;
}
