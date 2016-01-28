/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
  Modified Toni Klopfenstein
  SparkFun Electronics
  2016
*/
struct analogVal
{
  byte length;
  byte id;
  byte pinID;
  int reading;
};


analogVal analogInput;

int analogPin;

void setup() {
  analogInput.id = 1;
  analogInput.pinID=1;
  analogInput.reading = 1023;
  
  //Initialize serial connection at 9600bps
  Serial.begin(9600);
}

void loop() {
  //Determine analog pin to read from COSMOS input
  while (Serial.available()){
    analogInput.pinID = Serial.read();
    analogPin = analogInput.pinID;
  }

 analogInput.reading = analogRead(analogPin);
 
 sendData();
  
}

void sendData(){
  analogInput.length = sizeof(analogInput);
  writeData((const char*)&analogInput, sizeof(analogInput));
}

void writeData(const char* pkt, byte size){
  for(int i=0; i<size; i++)
  {
    Serial.write(pkt[i]);
  }
}


