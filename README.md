I2C Weather Monitor

Written by Larry Bank<br>
Copyright (c) 2017 BitBank Software, Inc.

bitbank@pobox.com

A simple C program which makes use of my other libraries to collect weather
data (temperature, humidity, pressure and total volatile compounds). The data
is recorded in a CSV (comma separated value) text file.
The data is also displayed in real time on a SSD1306 OLED display.
Data is sampled once every N seconds. This program is a simple example of
how to use the I2C sensors and record the data and is not meant to be a
complete solution.

Requires:
CCS811 air quality sensor
BME280 temp/humidity/pressure sensor
SSD1306 128x64 monochrome OLED display

Here's my prototyping setup

![Prototype](/proto.jpg?raw=true "Example Use")

requires use of my other libraries:<br>
https://github.com/bitbank2/oled_96<br>
https://github.com/bitbank2/bme280<br>
https://github.com/bitbank2/CCS811<br>

Features:<br>
---------<br>
- Command line settings for interval, output filename and total samples<br>
- Simple UI allows easy exit by pressing ENTER<br>
- Writes each line of csv data with a time/date stamp<br>

