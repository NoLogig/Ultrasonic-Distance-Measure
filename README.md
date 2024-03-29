# Ermitteln der Distanz anhand eines Ultraschalls

(JSN-SROT4-2.0_UltraSonicDistance-Sensor)

Der Abstand vom Sende -/ Empfängermodul (Parksensor JSN-SROT4-2.0) zum reflektierenden Objekt ergibt sich durch Multiplikation der Zeit, in der der Echo-PIN HIGH aktiv war (in Abb. 24 als 12ms dargestellt) mit der Schallgeschwindigkeit, durch die Division 2. 

## Funktionsweise

Ein Impuls von mindestens 10µs wird an den Trigger-PIN angelegt. 
![JSN](https://github.com/NoLogig/Ultrasonic-Distance-Measure/blob/master/img/JSN-SROT4-2.0_0.png)
Abb. 21 Ein 10µs Impuls am Trigger-PIN

Sensor generiert automatisch 8 Impulse 40kHz über das Sende-/Empfängermodul.  
![JSN](https://github.com/NoLogig/Ultrasonic-Distance-Measure/blob/master/img/JSN-SROT4-2.0_1.png)
Abb. 22 Erzeugte Rechteckschwingung mit 8, 40kHz Impulse.

Impulse werden von einer Oberfläche reflektiert und am Sende-/Empfängermodul empfangen.
![JSN](https://github.com/NoLogig/Ultrasonic-Distance-Measure/blob/master/img/JSN-SROT4-2.0_2.png)
Abb. 23 Impulse werden vom Objekt zurück zum Sende-/Empfängermodul reflektiert.

Am Echo-PIN wird ein Signal generiert, das der Zeit zwischen den gesendeten Schallimpulsen und den empfangenen Schallreflexionen entspricht.
Der nächste Impuls kann gesendet werden, wenn das Echo nachgelassen hat.
Werden keine reflektierten Schallwellen empfangen, wird ein Zeitsignal t = 38ms erzeugt. 
![JSN](https://github.com/NoLogig/Ultrasonic-Distance-Measure/blob/master/img/JSN-SROT4-2.0_3.png)
Abb. 24 Das Signal vom Echo-PIN korrespondiert mit der Zeit.

## Code
```cpp

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

```

Im Programmcode wandelt der Rückgabewert ((Echo / 2) / 29.1) von der Funktion `detectObstacleRange()` das Signal des Sensors, von Mikrosekunden in Zentimeter um.
Weil der Ping hin und her wandert, wird die Hälfte der zurückgelegten Strecke genommen, um die Entfernung des Objektes zu ermitteln.
Die Schallgeschwindigkeit ist gegeben und legt 343,5 m/s oder 29.1 μs/cm zurück.

Schallgeschwindigkeit in (m/s) bei einer gegebenen Lufttemperatur t (Grad Celsius)
```bash
  331,5 + 0,6 * t 
```
Bei einer Temperatur von 20 °C 
```bash
   331,5 + 0,6 * 20 = 331,5 + 12 = 343,5 m/s
```
Geschwindigkeit in Zentimeter pro Sekunden umwandeln
```bash
 	343,5 * 100 = 34350 cm/s 
```
In Mikrosekunden (μs)
```bash
 	34350 / 1000000 = 0,03435 cm/μs 
```
Geschwindigkeit in Tempo umwandeln, cm/μs 
```bash
 	1 / 0.03435 = 29.112 cm/μs 
```
