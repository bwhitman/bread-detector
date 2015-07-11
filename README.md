# Bread Detector

A simple WiFi sensor to measure the rise and temperature of rising bread. 

*Watch your boule from the bar*

![Bread Detector](http://aps.s3.amazonaws.com/g3ICa.png)

Bread Detector uses the great [Phant](http://data.sparkfun.com) and [Thing](https://www.sparkfun.com/products/13231) platform on Sparkfun for a free data logging service, and visualizes your bread as it rises, so you can do other things and check it from your phone. The raw parts are about $60 US, and kind of fun to build and play with -- you also get to eat a lot of bread.

We hope you enjoy it,

-- *Maureen and Brian*

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
 - 3 resistors: `R1` = 2.2kΩ, `R2` = 1kΩ , `R3` = 4.7kΩ
 
We've made a [Sparkfun Wist List](https://www.sparkfun.com/products/12728) with the main things in it, for convenience.

## Hookup

 - Distance sensor `Vo` (yellow on JST) to `R1` to pin `ADC` on the ESP8266. `ADC` to `R2` to `Vin`.
 - Distance sensor `GND` (black) to `GND` on the ESP8266.
 - Distance sensor `Vcc` (red) to `Vin` on the ESP8266.
 - Temperature sensor `DQ` (yellow) to `R3` to temperature sensor `Vcc` (red). `DQ` also to pin `12` on the ESP8266.
 - Temperature sensor `GND` (black) to `GND` on the ESP8266
 - Temperature sensor `Vcc` (red) to `Vin` on the ESP8266
 - Battery into connector on ESP8266
 - FTDI breakout board into the header pins for it on the ESP8266 (only for programming)
 
We made a very simple breakout using a thru-hole breadboard, with JST connectors for the two sensors:

![Bread Detector in action](http://aps.s3.amazonaws.com/oryNG.png)

The micro-USB jack on the ESP8266 charges the battery, which is handy. The battery seems to last a long time.

## Setting up
 
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
 - Set up a [GitHub Page](https://pages.github.com/) for your forked repository, or place the html that is in the `gh-pages` branch on a publicly available web server. (You can also just load `index.html` locally on your computer to see the graph.)
 - On the `index.html` file, change the `public_key` variable to the one you have (otherwise, you'll only see our bread)
 - Program the ESP8266 in Arduino

## Using

You should make something nice to hold the distance sensor over the proofing bowl. We took a [plastic mixer "splash guard"](http://www.amazon.com/Hutzler-3555-Mixer-Splatter-Guard/dp/B005BPZ7UW) and cut a little slot for the distance sensor. The temperature wire just snakes in and gets put under the dough. You want the distance sensor in the middle, with at least a few inches over the dough. (The minimum accurate reading seems to be about 0.8 inches from the sensor, maximum is about 12 inches.) 

![Detecting some bread](http://aps.s3.amazonaws.com/NPyd0.png)

 - Set up your bowl with the sensors in the right place
 - Flip on the power switch of the ESP8266
 - After a few seconds, watch your data come in on your data.sparkfun.com stream: you can look at the raw data on the site itself, or navigate to your own copy of the visualization. 
 - The data should update every 20 seconds.
 - The graph will stop updating after 17 hours of rising, so you don't get old rises in your graph from the day before. 
 - If you add it to your home screen on your phone, you'll get a nice icon, mostly reminding you to make bread

[!Phone bread](http://aps.s3.amazonaws.com/sslXk.png)
