watch-my-back 
-------------


### Overview

A simple mcu circuit that detects motion and sounds an alarm from its piezo buzzer. The PIR sensor detects 
motion by measuring changes in the infrared (heat) levels emitted by objects in front of it. Its tuned to
the temperature a human would put off so it works well with people and large animals. It works great indoors
but not so well outdoors.

The code is an AVR-GCC C project for the Atmel [attiny85](http://www.atmel.com/devices/attiny85.aspx).
It uses the timers w/ fast PWM to create an alarm sound when the PIR sensor senses something. It also uses
a pin change interrupt to wake it from sleep and sound the alarm. A timer1 overflow interrupt allows it to 
change pitch at regular intervals. Timer0 handles the frequency generation. CKDIV8 fuse is set with the 
internal oscillator so it runs at 1Mhz.

The [PIR sensor](http://www.parallax.com/tabid/768/ProductID/83/Default.aspx) has a range of between 15 and 30 feet. 
the sensor is an off-the-shelf part I plug into the board.

The battery is a 240mAh lipo battery that is typically used in small R/C toys like indoor helicopters. I like these
because I don't have to provide a power supply (voltage regulator, etc). I just recharge it with a cheap hobby charger
like my Tenergy TB6AC.

### Notes
- alarm sound is tuned for 4000hz to match the piezo buzzer I used (TDK PS1240P02BT)
- I included an ISP programming header that doubles as a header for the PIR sensor
- Header part - [0.100" Female: 1x9-Pin](http://www.pololu.com/catalog/product/1019/pictures)
- switch is handy for breadboarding too. Part# EG1218
- software serial debug lib is by Dimitar Dimitrov

### Board
Video:
http://www.youtube.com/watch?v=me5pYO3vPPQ

![board_top](https://raw.github.com/tacowars/watch-my-back/master/docs/DSC_0119.jpg)
![board_bottom](https://raw.github.com/tacowars/watch-my-back/master/docs/DSC_0120.jpg)