This project is an extension of RGB Neopixel strip control using OpenHab, MQTT binding and Mosquitto MQTT broker by Make Magazine as a weekend project series.
The original project is based on ESP8266 wifi module and since I dont have one around I decided to port this project on Particle Photon WiFi development module and using MQTT library.

The Project can also be used to control both NeoPixels strips and analog RGB LED strip. If using RGB strip(4-wires, +V,R,G,B) you will need 3 PWM enabled pins along with 3 transistors to switch high voltages, please refer the attached circuit reference for the same. Neopixels can be controlled directly from any one GPIO pins. 
