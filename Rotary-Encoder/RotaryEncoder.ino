//------------------------------------------------------------//
//  Incremental Rotary Encoder Interfacing using Interrupts   //
//                                                            //
//  Author : Vishnu M Aiea                                    //
//  E-Mail : vishnumaiea@gmail.com                            //
//  Date : 8:36 AM 18-09-2016, Sunday (IST)                   //
//  Web : https://goo.gl/xf8Ntc                               //
//  Github : https://github.com/vishnumaiea/Arduino-Snippets  //
//  See my project website on www.vishnumaiea.in              //
//                                                            //
//------------------------------------------------------------//
//                                                            //
//  Notes : The pins are configured for working with Arduino  //
//          Uno. Digital pin 2 and 3 are interrupt capable    //
//          pins in Uno. So connect your encoder outputs to   //
//          digital pins 2 and 3 of your Uno or any other     //
//          board accordingly. Also add RC filters to the     //
//          pins.                                             //
//------------------------------------------------------------//

int pulseCount; //rotation step count
int SIG_A = 0; //pin A output
int SIG_B = 0; //pin B output

int lastSIG_A = 0; //last state of SIG_A
int lastSIG_B = 0; //last state of SIG_B

int Pin_A = 2; //interrupt pin (digital) for A (change your pins here)
int Pin_B = 3; //interrupt pin (digital) for B


void setup()
{
  SIG_B = digitalRead(Pin_B); //current state of B
  SIG_A = SIG_B > 0 ? 0 : 1; //let them be different

  //attach iterrupt for state change, not rising or falling edges
  attachInterrupt(digitalPinToInterrupt(Pin_A), A_CHANGE, CHANGE);
  Serial.begin(9600);
}


void loop() {
  //does nothing here. Add your code here
}


void A_CHANGE() //Interrupt Service Routine (ISR)
{
  detachInterrupt(0); //important
  SIG_A = digitalRead(Pin_A); //read state of A
  SIG_B = digitalRead(Pin_B); //read state of B
 
  if((SIG_B == SIG_A) && (lastSIG_B != SIG_B))
  {
    pulseCount--; //anti-clockwise rotation
    lastSIG_B = SIG_B;
    Serial.print(pulseCount);
    Serial.println(" - CC");
  }
 
  else if((SIG_B != SIG_A) && (lastSIG_B == SIG_B))
  {
    pulseCount++; //clockwise rotation
    lastSIG_B = SIG_B > 0 ? 0 : 1; //save last state of B
    Serial.print(pulseCount);
    Serial.println(" - CW");
  }
  attachInterrupt(digitalPinToInterrupt(Pin_A), A_CHANGE, CHANGE);
}
