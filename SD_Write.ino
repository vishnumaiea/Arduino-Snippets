//---------------------------------------------------//
//
//  Writing to SD Card.
//
//  Type "i" or "I" in the serial terminal to
//  initialize the card.
//
//  Type "r" to open and write to a file.
//
//  Author : Vishnu M Aiea
//  Web : www.vishnumaiea.in
//  IST 7:02 PM 28-02-2017, Tuesday
//
//----------------------------------------------------//

#include <SPI.h>
#include <SD.h>

byte inByte; //byte read from terminal
bool sdInitSuccess = false; //card init status
File myFile;

//------------------------------------------------------

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //wait for the serial port to connect.
  }
}

//------------------------------------------------------

void loop() {
  if (Serial.available() > 0) {
    inByte = Serial.read();

    if (inByte == 'i' || inByte == 'I')
    {
      if (sdInitSuccess) { //check if card is initialized already
        Serial.println("Already initialized.\n");
      }
      else if (!sdInitSuccess) { //if not already initialized
        Serial.println("Initializing SD Card..");

        if (!SD.begin(10)) { //using pin 10 (SS)
          Serial.println("Initialization failed!\n");
          sdInitSuccess = false; //failure
          return;
        }
        else {
          Serial.println("Intitialization success.\n");
          sdInitSuccess = true;
        }
      }
    }

    else if (inByte == 'n' || inByte == 'N') {
      if (sdInitSuccess) { //proceed only if card is initialized
        myFile = SD.open("TEST.txt", FILE_WRITE);

        if (myFile) {
          Serial.println("File opened successfully.");
          Serial.println("Writing to TEST.text..");
          myFile.println("Some Text");
          myFile.close(); //this writes to the card
          Serial.println("Done.\n");
        }
        else { //else show error
          Serial.println("Error opeing file.\n");
        }
      }
      else {
        Serial.println("SD Card not initialized.");
        Serial.println("Type \"i\" to initialize.\n");
      }
    }

    else {
      Serial.println("Not recognized."); //unknown cmd
      Serial.println();
    }
  }
}

//--------------------------------------------------------
