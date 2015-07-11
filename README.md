![Bread](http://aps.s3.amazonaws.com/fhXiG.png)

# The Bread Detector

A DIY WiFi sensor to measure the size and temperature of rising bread. 

*Watch your boule from the bar*

![Phone bread](http://aps.s3.amazonaws.com/sslXk.png)

Bread Detector visualizes the shape and internal temperature your dough as it rises, so you can do other things and check up on it from your phone once in a while. 

*You can build it yourself!* We used the great -- and free -- [Phant](http://data.sparkfun.com) data logging service and the [Sparkfun Thing](https://www.sparkfun.com/products/13231) platform. The raw parts are about $60, and is a lot of fun to build and play with. You get to eat a lot of bread. We hope you enjoy it,

-- *Maureen and Brian*

## Parts List

 - `BATT` = [Lithium Ion Battery](https://www.sparkfun.com/products/341)
 - `MCU` = [ESP8266 Thing] (https://www.sparkfun.com/products/13231)
 - `TEMP` = [Waterproof Temperature Sensor] (https://www.sparkfun.com/products/11050)
 - `DIST` = [Infrared Distance Sensor] (https://www.sparkfun.com/products/12728)
 
And some tools you might already have to make it easier
 
 - [FTDI Basic Breakout] (https://www.sparkfun.com/products/9873) for programming
 - breakaway headers
 - hookup wire
 - 3-pin JST cables / terminals
 - a breadboard 
 - 3 resistors: 
     - `R1` = 2.2kΩ
     - `R2` = 1kΩ
     - `R3` = 4.7kΩ
 
We've made a [Sparkfun Wist List](https://www.sparkfun.com/wish_lists/114168) with all the things in it, for convenience. 

## Hookup

 - `DIST` `Vo` (yellow on JST) to `R1` to `MCU` `ADC`. `MCU` `ADC` to `R2` to `MCU` `Vin`.
 - `DIST` `GND` (black) to `MCU` `GND`.
 - `DIST` `Vcc` (red) to `MCU` `Vin`.
 - `TEMP` `DQ` (yellow) to `R3` to `TEMP` `Vcc` (red). `TEMP` `DQ` also to `MCU` `12`.
 - `TEMP` `GND` (black) to `MCU` `GND`.
 - `TEMP` `Vdd` (red) to `MCU` `Vin`.
 - `BATT` to `MCU` JST connector
 - FTDI breakout board into the `MCU` header pins (only for programming)
 
We made a very simple breakout using a thru-hole breadboard, with JST connectors for the two sensors:

![Bread Detector in action](http://aps.s3.amazonaws.com/oryNG.png)

The micro-USB jack on the ESP8266 charges the battery, which is handy. The battery seems to last a long time.

## Setting up
 
 - Fork or clone this repository
 - Make sure to follow [Sparkfun's guide to setting up the Arduino environment for the ESP8266.](https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon)
 - Create a sketch with the files in the master branch of this repository: the `BreadDetector.ino`, `OneWire.h` and `OneWire.cpp`.
 - Create a [free stream](https://data.sparkfun.com/streams/make) on data.sparkfun.com with the fields `distance`, `raw_distance`, and `temp`.
 - Create a file called `auth.h` in the sketch with the following
```
     const char WiFiSSID[] = "your wifi SSID";
     const char WiFiPSK[] = "your wifi's password";
     const char PublicKey[] = "your data.sparkfun.com's public key";
     const char PrivateKey[] = "your data.sparkfun.com's private key";
```
 - Set up a [GitHub Page](https://pages.github.com/) for your forked repository, or place the [index.html that is in the `gh-pages` branch](https://github.com/bwhitman/bread-detector/blob/gh-pages/index.html) on a publicly available web server. You can also just open `index.html` locally on your computer to see the graph.
 - In the `index.html` file, change the `public_key` variable to yours, otherwise, you'll only see our bread.
 - Connect and program the sketch to the ESP8266 in Arduino

## Getting ready to rise

You should make something nice to hold the distance sensor over the rising bowl. We took a [plastic mixer "splash guard"](http://www.amazon.com/Hutzler-3555-Mixer-Splatter-Guard/dp/B005BPZ7UW) and cut a little slot for the distance sensor. The temperature wire just snakes in and gets put under the dough. You want the distance sensor in the middle, with at least a few inches over the dough. (The minimum accurate reading seems to be about 0.8 inches from the sensor, maximum is about 12 inches.) 

![Detecting some bread](http://aps.s3.amazonaws.com/NPyd0.png)

## How to get started

 - Set up your bowl with the sensors in the right place
 - Flip on the power switch of the ESP8266
 - After a few seconds, watch your data come in on your data.sparkfun.com stream: you can look at the raw data on the site itself, or navigate to your own copy of the visualization. 
 - The data should update every 20 seconds.
 - The graph will stop updating after 17 hours of rising, so you don't get old rises in your graph from the day before. 
 - If you add it to your home screen on your phone, you'll get a nice icon, mostly reminding you to make bread


