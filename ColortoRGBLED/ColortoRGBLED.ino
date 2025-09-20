#include <Wire.h>
#include "Adafruit_TCS34725.h"
/*
Example code for color deection and reproduction
Uses Adafruit TCS3472 library
Connect TCS3472 as follows

Connect SCL    to analog 5
Connect SDA    to analog 4
Connect VDD    to 5V DC
Connect GROUND to common ground

RGB LED used in this sketch is common Cathode (common pin connected to ground)
Pick analog outputs, for the UNO 9,10,11 work well
Use 220 Ohm / 1kOhm resistors between supply and RGB LED
See schematic for connections
*/

const int redpin = 9;
const int greenpin = 10;
const int bluepin = 11;

// array to represent the gamma function
int gammatable[256];

// Initalize an object 'tcs" with integration time 600 ms and gain 16X
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_16X);

// Define C++ stucture to hold results of black / white calibaration
struct colorCalibration {
  unsigned int blackValue;
  unsigned int whiteValue;
};

// initiate three stuctures to hold calibration of Red, Green and LED's in TCS3472
colorCalibration redCal, greenCal, blueCal;


void setup() {
  Serial.begin(115200);
  Serial.println("Color Swatch to RGB LED");

  // Initiate TCS3472 IC
  if (tcs.begin()) {
    Serial.println("Found TCS3472 sensor");
  } 
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // These values result from calibration of the TCS3472 looking at a black sample and a white sample
  // Must be edited here once calibration values have been determined
  redCal.blackValue = 1525;
  redCal.whiteValue = 9078;
  greenCal.blackValue = 1851;
  greenCal.whiteValue = 13787;
  blueCal.blackValue = 1847;
  blueCal.whiteValue = 14972;

  // use these three pins to drive an RGB LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Gamma function is Out = In^2.5
  // Required to correct for human vision
  // Store values in an array
  // normalized for 0 to 255
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    gammatable[i] = int(x);
    }
    
  Serial.println("Type any character into Serial Monitor to begin");  
}


void loop() {
  unsigned int r, g, b, c; // raw values of r,g,b,c as read by TCS3472
  // Variables used to hold RGB values between 0 and 255
  int redValue;
  int greenValue;
  int blueValue;
  int clearValue;
  // Dummy string used to read in input from serial monitor
  String incomingString;

  delay(500);

  // Typing any character into Serial Monitor will kick off a read / output cycle
  if (Serial.available() > 0){
    incomingString = Serial.readString();
    // Get raw data from the TCS3472
    tcs.getRawData(&r, &g, &b, &c);
    
    // Print out raw data resulting from read cycle
    Serial.print("R: "); Serial.print(r); Serial.print(" ");
    Serial.print("G: "); Serial.print(g); Serial.print(" ");
    Serial.print("B: "); Serial.print(b); Serial.print(" ");
    Serial.print("C: "); Serial.print(c); Serial.print(" ");
    Serial.println(" ");

    delay(50);

    // Convert TCS3472 raw reading into value between 0 and 255 for analogwrite function
    redValue = RGBmap(r, redCal.blackValue, redCal.whiteValue, 0, 255);
    greenValue = RGBmap(g, greenCal.blackValue, greenCal.whiteValue, 0, 255);
    blueValue = RGBmap(b, blueCal.blackValue, blueCal.whiteValue, 0, 255);

    // Print out values
    Serial.print("R: "); Serial.print(redValue); Serial.print(" ");
    Serial.print("G: "); Serial.print(greenValue); Serial.print(" ");
    Serial.print("B: "); Serial.print(blueValue); Serial.print(" ");
    Serial.println(" ");

    // Write out values to RGB LED
    // Gamma function applied to raw values
    analogWrite(redpin, gammatable[redValue]);
    analogWrite(greenpin, gammatable[greenValue]);
    analogWrite(bluepin, gammatable[blueValue]);

  }
  
}

// Function to map TCS3472 values to 0 to 255
// Same as Arduino map() function - rewritten to make variables compatiable with inputs and outputs
int RGBmap(unsigned int x, unsigned int inlow, unsigned int inhigh, int outlow, int outhigh){
  float flx = float(x);
  float fla = float(outlow);
  float flb = float(outhigh);
  float flc = float(inlow);
  float fld = float(inhigh);

  float res = ((flx-flc)/(fld-flc))*(flb-fla) + fla;

  return int(res);
}
