
# Arduino Tresor

Ein Arduino wird zur Steuerung eines Tresors verwendet. Je nach Input am Keypad wird ein Servo-Motor zur Verriegelung angetrieben und der Zustand des Tresors wird an einem LCD-Monitor ausgegeben.

## Features

- Output an einem LCD-Monitor
- Steuerung eines Servo-Motors
- Verriegelung durch die automatische Betätigung eines Schiebereglers
- Ablesen des Inputs durch ein Keypad

## Installation

#### 1. Download Arduino Library
```bash
  Ich habe die Version 2.3.0 genutzt
```
#### 2. Importieren der Libraries
```bash
  Wir benötigen jeweils eine Library für den Servo, den LCD und das Keypad.
  - Servo: Servo.h (enthalten in der Arduino IDE)
  - LCD: LiquidCrystal_I2C.h (nicht enthalten in der IDE, Manuelles Einfügen benötigt)
  - Keypad: Keypad.h (enthalten in der Arduino IDE)
```

#### 3. Verschaltung des Arduinos

![alt text](https://github.com/bekirtahagd/arduino-tresor/blob/main/ProjectPreview/Verschaltung_Tinkercad.png?raw=true)


#### 4. Arduino IDE mit Arduino verbinden
```bash
  Zum Schluss muss der Arduino mit der IDE verbunden werden, sodass das Programm   abgespielt werden kann. 
```
## Aufbau

#### 1. Tresorplatte umbauen

Zuerst kauft man eine Holzplatte und gewisse Ausschnitte getätigt, sodass man Platz für den LCD Monitor und die Kabel für das Keypad hat.

![alt text](https://github.com/bekirtahagd/arduino-tresor/blob/main/ProjectPreview/Tresor_Bau.png?raw=true)

#### 2. LCD und Schieberegler

Danach befestigt man den LCD in die Lücke und schraubt den Servo-Motor, inklusive Schieberegler an die Tresorplatte.

![alt text](https://github.com/bekirtahagd/arduino-tresor/blob/main/ProjectPreview/Tresor_Platte.png?raw=true)
![alt text](https://github.com/bekirtahagd/arduino-tresor/blob/main/ProjectPreview/Verriegelung.png?raw=true)

#### 3. Tresorplatte an Gehäuse montiert
Nun muss man die Tresorplatte an ein Gehäuse montieren. Dafür kann man eine offene Weinkiste benutzen. Somit hat man die Form eines Tresors, aber gleichzeitig auch Löcher um den Verriegelungsprozess innerhalb des Tresors besser sehen zu können.

![alt text](https://github.com/bekirtahagd/arduino-tresor/blob/main/ProjectPreview/Tresor_Tür.png?raw=true)

#### 4. Verschaltung

Verschaltet man das ganze kommt man auf folgendes Ergebniss.

![alt text](https://github.com/bekirtahagd/arduino-tresor/blob/main/ProjectPreview/Verschaltung.png?raw=true)

https://github.com/bekirtahagd/arduino-tresor/assets/70061931/63cf33d0-edce-4b5a-9fae-92e37f12d392


#### 5. Endprodukt
```bash
  Wird das Programm auf den Arduino geladen, so ist unser Tresor fertig. Unser Endprodukt sieht wie folgt aus: 
```
![alt text](https://github.com/bekirtahagd/arduino-tresor/blob/main/ProjectPreview/Endprodukt.png?raw=true)

https://github.com/bekirtahagd/arduino-tresor/assets/70061931/9fd56226-7871-494f-a0fd-1f19792085f1


