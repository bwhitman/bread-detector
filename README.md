# Bread Detector

A simple WiFi sensor to measure the rise and temperature of rising bread. 

*Watch your boule from the bar*

![Bread Detector](http://aps.s3.amazonaws.com/g3ICa.png)

Bread Detector uses the great [Phant](http://data.sparkfun.com) and [Thing](https://www.sparkfun.com/products/13231) platform on Sparkfun for a free data logging service, and visualizes your bread as it rises, so you can do other things and check it from your phone. The raw parts are about $60 US, and kind of fun to build and play with -- you also get to eat a lot of bread.

## Parts List

 - [Lithium Ion Battery](https://www.sparkfun.com/products/341)
 - [ESP8266 Thing] (https://www.sparkfun.com/products/13231)
 - [FTDI Basic Breakout] (https://www.sparkfun.com/products/9873)
 - [Waterproof Temperature Sensor] (https://www.sparkfun.com/products/11050)
 - [Infrared Distance Sensor] (https://www.sparkfun.com/products/12728)
 
And some tools you already have to make it easier

 - breakaway headers
 - hookup wire
 - 3-pin JST cables / terminals
 - a breadboard 
 - 3 resistors: `R1` = 2.2 kOhm, `R2` = 1 kOhm, `R3` = 4.7 kOhm
 
I've made a [Sparkfun Wist List](https://www.sparkfun.com/products/12728) with the main things in it, for convenience.

## Hookup

 - Distance sensor `Vo` (yellow on JST) to `R1` to pin `ADC` on the ESP8266. `ADC` to `R2` to `Vin`.
 - Distance sensor `GND` (black) to `GND` on the ESP8266.
 - Distance sensor `Vcc` (red) to `Vin` on the ESP8266.
 - Temperature sensor `DQ` (yellow) to `R3` to temperature sensor `Vcc` (red). `DQ` also to pin `12` on the ESP8266.
 - Temperature sensor `GND` (black) to `GND` on the ESP8266
 - Temperature sensor `Vcc` (red) to `Vin` on the ESP8266
 - Battery into connector on ESP8266
 - FTDI breakout board into the header pins for it on the ESP8266 (only for programming)
 
## Programming
 
 - Fork or clone this repository
 - Make sure to follow [Sparkfun's guide to setting up the Arduino environment for the ESP8266.](https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon)
 - Create a sketch with the three files in the master branch of this repository: the .ino, and the OneWire.h / .cpp
 - Create a [free stream](https://data.sparkfun.com/streams/make) on data.sparkfun.com with the fields `distance`, `raw_distance`, and `temp`. Note the keys
 - Create a file called `auth.h` in the sketch with the following
```
     const char WiFiSSID[] = "your wifi SSID";
     const char WiFiPSK[] = "your wifi's password";
     const char PublicKey[] = "your data.sparkfun.com's public key";
     const char PrivateKey[] = "your data.sparkfun.com's private key";
```
 - Set up a [GitHub Page](https://pages.github.com/) for your forked repository, or place the html in the `gh-pages` branch on a publicly available web server. 
 - Program the ESP8266 in Arduino

## Using
 - x,y,z
 - Watch your data come in on your data.sparkfun.com stream


