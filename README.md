watch-my-back 
-------------

This is an AVR-GCC C project for the Atmel [attiny85](http://www.atmel.com/devices/attiny85.aspx).
It uses the timers w/ fast PWM to create an alarm sound when the Parallax PIR sensor senses something.


### NOTES
- alarm sound is tuned for 4000hz to match the piezo buzzer I used (TDK PS1240P02BT)
- software serial debug lib is by Dimitar Dimitrov