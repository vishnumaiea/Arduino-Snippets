//**************************************************************//
//  Name    : SevenSegment using 595                            //
//  Author  : Vishnu M Aiea (www.vishnumaiea.in)                //
//  Date    : 15-06-2014                                        //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//            to dispaly all possible characters on a           //
//            seven segment display (coommon cathode)           //
//****************************************************************

int latchPin = 8; //Pin connected to ST_CP of 74HC595
int clockPin = 12; //Pin connected to SH_CP of 74HC595
int dataPin = 11; //Pin connected to DS of 74HC595

int segMap[19] = {252,96,218,242,102,182,190,224,254,246,238,156,158,142,110,28,206,124,2};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  //count up routine
  for (int j = 0; j<19; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, segMap[j]);   
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(300);
  }
}
