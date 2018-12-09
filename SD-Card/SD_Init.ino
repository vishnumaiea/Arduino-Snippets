/ -------------------------------------------------
//
//  Micro SD Card initialization code.
//  Type "i" or "I" in the serial terminal to
//  initialize the card.
//
//  Author : Vishnu M Aiea
//  Web : www.vishnumaiea.in
//  IST 4:04 PM 28-02-2017, Tuesday
//
//--------------------------------------------------


#include <SPI.h>
#include <SD.h> //include the SD library

byte inByte;
bool sdInitSuccess = false; //card init status

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //wait for the serial port to connect.
  }
}

void loop() {
  if (Serial.available() > 0) {
    inByte = Serial.read();

    if (inByte == 'i' || inByte == 'I')
    {
      if (sdInitSuccess) {
        Serial.println("Already initialized.");
        Serial.println();
      }
      else if (!sdInitSuccess) { //if not already initialized
        Serial.println("Initializing SD Card..");
        if (!SD.begin(10)) { //using pin 10 (SS)
          Serial.println("Initialization failed!");
          Serial.println();
          sdInitSuccess = false;
          return;
        }
        else {
          Serial.println("Intitialization success.");
          Serial.println();
          sdInitSuccess = true;
        }
      }
    }
  }
}
