# Ultrasonic Distance Meter (HC-SR04 + I2C LCD)

An Arduino-based digital rangefinder that measures distance in real time using an **HC-SR04 ultrasonic sensor** and shows the result on a **16x2 I2C LCD**.

## ✨ Features

- Real-time distance measurement in centimeters (cm)
- Out-of-range detection (below 2 cm or above 400 cm)
- Clean, easy-to-read display over I2C (only 2 data lines)
- Lightweight, simple Arduino code

## 🧰 Hardware Components

| Component              | Quantity | Description                                  |
| ---------------------- | :------: | -------------------------------------------- |
| Arduino Uno / Nano     | 1        | Microcontroller board                        |
| HC-SR04 Sensor         | 1        | Ultrasonic distance measurement sensor       |
| I2C 16x2 LCD Display   | 1        | LCD module with PCF8574 I2C adapter          |
| Breadboard & Wires     | —        | Jumper wires for connections                 |

## 🔌 Wiring

### Pictorial Wiring Diagram

![Ultrasonic Distance Meter pictorial wiring diagram](Ultrasonic%20Arduino%20Radar%20System%20Public%20pictorial%20wiring%20diagram%20%281%29.png)

### HC-SR04 Ultrasonic Sensor

| Sensor Pin | Arduino Pin     |
| ---------- | --------------- |
| VCC        | 5V              |
| GND        | GND             |
| Trig       | Digital Pin 9   |
| Echo       | Digital Pin 8   |

### 16x2 I2C LCD

| LCD Pin | Arduino Pin                        |
| ------- | ---------------------------------- |
| VCC     | 5V                                 |
| GND     | GND                                |
| SDA     | A4 (SDA on Uno/Nano)               |
| SCL     | A5 (SCL on Uno/Nano)               |

### Schematic Overview

```
  HC-SR04 Sensor          Arduino Uno / Nano          16x2 I2C LCD
 +--------------+        +------------------+        +--------------+
 |          VCC |--------| 5V            5V |--------| VCC          |
 |          GND |--------| GND          GND |--------| GND          |
 |         TRIG |--------| D9            A4 |--------| SDA          |
 |         ECHO |--------| D8            A5 |--------| SCL          |
 +--------------+        +------------------+        +--------------+
```

> Both modules share the Arduino's **5V** and **GND** rails.

## 📐 How It Works

The sensor measures distance using the speed of sound in air
(≈ 343 m/s = **0.0343 cm/µs**):

1. A **10 µs** HIGH pulse on the **Trig** pin makes the sensor send an ultrasonic burst.
2. The **Echo** pin stays HIGH for the time `t` (in µs) the sound takes to reach an object and bounce back.
3. Since the sound travels there *and* back, the distance is:

$$
d = \frac{t \times 0.0343}{2}
$$

Readings below 2 cm or above 400 cm are outside the HC-SR04's reliable range and are shown as **"Out of Range"**.

## 💻 Code

The sketch is in [`arduino-ultrasonic-meter.ino`](arduino-ultrasonic-meter.ino).

It requires the **LiquidCrystal_I2C** library. In the Arduino IDE, go to
**Sketch → Include Library → Manage Libraries...**, search for `LiquidCrystal I2C`, and install it.

Default settings (change them at the top of the sketch if needed):

| Setting      | Value  |
| ------------ | ------ |
| LCD address  | `0x27` |
| LCD size     | 16x2   |
| Trig pin     | 9      |
| Echo pin     | 8      |
| Refresh rate | 250 ms |

## 🚀 How to Run

1. Open the Arduino IDE.
2. Install the **LiquidCrystal_I2C** library through the Library Manager.
3. Wire the circuit as shown in the [Wiring](#-wiring) section.
4. Open `arduino-ultrasonic-meter.ino`.
5. Select your board (**Tools → Board → Arduino Uno / Nano**) and COM port.
6. Click **Upload**. The LCD shows *"Distance Meter / Initializing..."* and then the live distance.

## 🛠️ Troubleshooting

| Problem                              | Solution |
| ------------------------------------ | -------- |
| LCD shows blue blocks or no text     | Turn the contrast potentiometer on the back of the I2C backpack. |
| Nothing appears on the LCD           | Check the I2C address. Run an I2C scanner sketch; if it reports `0x3F`, change `0x27` to `0x3F` in the code. |
| Always shows "Out of Range"          | Check the Trig/Echo wiring (Trig → D9, Echo → D8) and make sure the sensor is powered from 5V. |
| Readings jump around                 | Make sure the wires are firmly connected and the target is a flat surface more than 2 cm away. |
