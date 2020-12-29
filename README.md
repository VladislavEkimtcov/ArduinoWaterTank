# ArduinoWaterTank
Simple Arduino program to engage a water pump when a water tank level is low. Useful for humidifiers, etc.

## How it works
Once the distance to water is above a threshold, the system will activate the pump with a transistor. Once the water reaches a certain level, the pump will be disengaged. Pump battery dying or water touching the 

## Setup
Modify the pump as described further. Aseemble the breadboard. Set the reservoirDepth variable to however deep the water sensor belives your water tank to be. Modify the level at which the pump is engaged in the loop() function. Attach the sonic sensor so it can ping the deepest point in the tank and tape the water presence sensor at a level that would be considered an overflow.

## Cool safety tricks
If water touches the overflow sensor or is too far, the system will try to disengage the pump (it's either overflowing or the pump ran out of battery and water is running low). A red LED will light up.

## Known problems
Pump engagement level and levle indicating pump failure are hardcoded in the loop() function. Pump battery may run out.

## Hardware
Arduino

Breadboard (optional)

[HC-SR04 Ultrasonic Sensor](https://www.amazon.com/Organizer-Ultrasonic-Distance-MEGA2560-ElecRight/dp/B07RGB4W8V)

[Water Presence Detector](https://www.amazon.com/Sensor-Module-Detection-Surface-Arduino%EF%BC%8810pcs%EF%BC%89/dp/B07THDH7Y4/) (substitutable for two wires)

LED

[LCD Display](https://www.amazon.com/gp/product/B019D9TYMI/) (optional)

1x resistor for LED

1x transistor

[External Water Pump](https://www.amazon.com/gp/product/B07HFPC7HB)

## Pinouts

#### Ultrasonic sensor

Gnd to Gnd

Echo to 9

Trig to 10

Vcc to 5v

#### Display

Basically [like this](https://howtomechatronics.com/tutorials/arduino/lcd-tutorial/), the code is using these pins:

Rs to 12

E to 13

D4 to 5

D5 to 4

D6 to 3

D7 to 2

#### Water Presence Detector

S to A5

+ to 5v

- to Gnd

#### Alarm LED

Pin 11 and ground with resistor somewhere in there also

#### Water Pump

Water pump should be powered by an external source. Find two points on the pump's board that make it run continuously and bridge them with a transistor. The transistor's middle pin connects to Pin 8. 
