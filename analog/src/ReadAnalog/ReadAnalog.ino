/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
  Modified Toni Klopfenstein
  SparkFun Electronics
  2016

  Based off of David Holthouser's COSMOS Blink demo: 
  https://bitbucket.org/dholshouser/alagna/wiki/HowTo
*/

//Create structure for the COSMOS commands/telemetry
struct analogVal
{
  byte msgSize; //Packet length for COSMOS (COSMOS item 'length')
  byte id; //Command Identifier for COSMOS (COSMOS item id)
  byte pinID; //ATMega328 pin to read (COSMOS item 'readAnalogPin')
  byte reading; //Analog reading (COSMOS item 'analogReading')
  byte cmdsReceived; //Number of commands received from COSMOS (COSMOS item 'cmdsSent')
  byte cmdsAccepted; //Number of commands actually used from COSMOS (COSMOS item 'cmdsAccepted')
};


//Initialize instance of command/telemetry structure
analogVal analogInput;

//Create variable to store pin selection from COSMOS
int analogPin;

void setup() {

  //Set initial values for structure
  analogInput.id = 1;
  analogInput.pinID=4;
  analogInput.reading = 0;
  analogInput.cmdsReceived = 0;
  analogInput.cmdsAccepted =0;
  
  //Initialize serial connection at 9600bps
  Serial.begin(9600);
}

void loop() {
  //Determine analog pin to read from COSMOS input
  bool cmd = false;
  
  while (Serial.available()){
    cmd = true;
    analogInput.pinID = Serial.read();
    analogPin = analogInput.pinID;
    analogInput.cmdsReceived++;
  }

  if(cmd ==true)
  {
    analogInput.cmdsAccepted++;
  }

//Take analog reading
 analogInput.reading = analogRead(analogPin);

 //Send analog reading and current configuration back to COSMOS
 sendData();
  
}

void sendData(){
  analogInput.msgSize = sizeof(analogInput);
  //Write all variables back to the structure
  writeData((const char*)&analogInput, sizeof(analogInput));
}

void writeData(const char* pkt, byte tlmSize){
  for(int i=0; i<tlmSize; i++)
  {
    Serial.write(pkt[i]);
  }
}


