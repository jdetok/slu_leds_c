# SLU Fleur de Lis Lights - User Guide/Instructions
- ## [Demo Video](https://youtu.be/l19p7q0IOvI)
## POWER/CHARGING
- The device accepts 5V of power via the attached battery or the USB-C port attached to the Arduino
- #### Battery
    - The battery is a rechargeable lithium-ion 18650 cell
    - Recharge with any of the 3 USB ports on the battery module itself 
        - Plugging into the Arduino itself <b>will not</b> charge the device
- If the device does not have a battery or the battery is not operating, the device can be powered by wire using the USB-C port on the Arduino
#
<img src="img/back.png" width=500/>

## BUTTONS
There are 8 buttons referred to as b1-b8 - the name of each button is labeled to the left of the button
### Brightness
- b1 - BRIGHTNESS DOWN
- b2 - BRIGHTNESS UP
### Delay/Speed
- b7 - SPEED DOWN (longer delay between effects)
- b7 - SPEED UP (shorter delay between effects)
### Effects
- b3 - PULSE BRIGHTNESS EFFECT
    - pulse effect works with solid LEDs and with bit chaser effect active
- b4 - BIT CHASER EFFECT
- b5 & b6 - ONLY OPERATIONAL WHEN BIT CHASER IS ACTIVE (b4 is pressed)
    - b5 - BIT CHASER MODE
        - increase the number of lights that are lit at a time
    - b6 - REVERSE DIRECTION OF BIT CHASER
        - change the direction of the bit chaser effect

<img src="img/front.png" width=500/>