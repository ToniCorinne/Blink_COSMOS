/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

struct soh_t
{
  byte length;
  byte id;
  byte delay;
};

// Global variable to hold State of Health tlm packet.
soh_t mySoh;

// the setup function runs once when you press reset or power the board
void setup()
{
  mySoh.id = 1;
  mySoh.delay = 250;
  
  pinMode(13, OUTPUT); // initialize digital pin 13 as an output.
  Serial.begin(9600);  // initialize serial:
}

// the loop function runs over and over again forever
void loop()
{
  processCmds();
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(mySoh.delay);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(mySoh.delay);
  sendTlm();
}

void processCmds()
{
  while (Serial.available())
  {
    // get the new byte:
    mySoh.delay = Serial.read();  
  }
}

void sendTlm()
{
  mySoh.length = sizeof(mySoh);
  writeTlm((const char*)&mySoh, sizeof(mySoh));
}

void writeTlm(const char* pkt, byte size)
{
  for(int i=0; i<size; i++)
  {
    Serial.write(pkt[i]);
  }
}
