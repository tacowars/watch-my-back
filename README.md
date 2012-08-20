watch-my-back 
-------------

This is an AVR-GCC C project for the Atmel [attiny85](http://www.atmel.com/devices/attiny85.aspx).
It uses the timers w/ fast PWM to create an alarm sound when the Parallax PIR sensor senses something.

Video:
http://www.youtube.com/watch?v=me5pYO3vPPQ

### NOTES
- alarm sound is tuned for 4000hz to match the piezo buzzer I used (TDK PS1240P02BT)
- I included an ISP programming header that doubles as a header for the PIR sensor
- Header part - [0.100" Female: 1x9-Pin](http://www.pololu.com/catalog/product/1019/pictures)
- switch is handy for breadboarding too. Part# EG1218
- software serial debug lib is by Dimitar Dimitrov

### Pictures of the board
![board_top](https://raw.github.com/tacowars/watch-my-back/master/docs/DSC_0119.jpg)
![board_bottom](https://raw.github.com/tacowars/watch-my-back/master/docs/DSC_0120.jpg)