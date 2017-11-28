I2C Weather Monitor

Written by Larry Bank
Copyright (c) 2017 BitBank Software, Inc.

bitbank@pobox.com

A simple C program which makes use of my other libraries to collect weather
data (temperature, humidity, pressure and total volatile compounds). The data
is recorded in a CSV (comma separated value) text file.
The data is also displayed in real time on a SSD1306 OLED display.
Data is sampled once every ten seconds. This program is a simple example of
how to use the I2C sensors and record the data and is not meant to be a
complete solution.

Requires:
CCS811 air quality sensor
BME280 temp/humidity/pressure sensor
SSD1306 128x64 monochrome OLED display

Here's my prototyping setup

![Prototype](/proto.jpg?raw=true "Example Use")
