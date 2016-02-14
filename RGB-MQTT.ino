//Importing Necessary Libraries
//If Using Neopixel strip instead of traditional RGB strip also import the following library
//#include "neopixel/neopixel.h"

#include "MQTT/MQTT.h"

//Defining Pins for RGB strip control
#define RED D0
#define GREEN D1
#define BLUE A7

//If Using Neopixel strip define following
//#define PIXEL_PIN    2
//#define PIXEL_COUNT 30    // 30 pixels in the NeoPixel strip
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//Callback function declaration
void callback(char* topic, byte* payload, unsigned int length);

/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * MQTT client("www.sample.com", 1883, callback);

MQTT client("server_name", 1883, callback);
**/

byte server[] = { 192,168,1,85 }; //Server where OpenHab is running with MQTT binding along with Mosquitto MQTT broker 
MQTT client(server, 1883, callback); //1883 default port for MQTT



void callback(char* topic, byte* payload, unsigned int length) {
    
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);
    
    //Parseing String to fetch RGB values independently in each variable:
    int c1 = message.indexOf(','); 
    int c2 = message.indexOf(',',c1+1);
    int red = message.toInt();
    int green =  message.substring(c1+1).toInt();
    int blue =  message.substring(c2+1).toInt();
    
    //Generating 8-bit PWM corresponding to the RGB values
    analogWrite(RED,red);
    analogWrite(GREEN,green);
    analogWrite(BLUE,blue);
    
    //In case of NeoPixel Strip
    //for(int i=0;i<=PIXEL_COUNT;i++)
    //strip.setPixelColor(i, red, green, blue);
    
    delay(1);
}


void setup() {
    
    //If RGB strip
    pinMode(RED,OUTPUT);
    pinMode(GREEN,OUTPUT);
    pinMode(BLUE,OUTPUT);
    
    //If NeoPixel Strip
    //strip.begin();
    
    // connect to the particle server
    client.connect("sparkclient");

    // publish/subscribe
    if (client.isConnected()) {
        //Successfully Publish Message
        client.publish("/outTopic","Photon's Ready :D"); //Topic , Messagee --> Published  
        client.subscribe("/OpenHab/RGB/#"); //Topic <--- Subscribed
    }
}

void loop() {
    
    if (client.isConnected())
        client.loop();
}


