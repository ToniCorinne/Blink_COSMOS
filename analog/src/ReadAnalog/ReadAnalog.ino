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
  byte reading;
};

//struct voltageVal
//{
//  byte length;
//  byte id;
//  byte translation;
//};

analogVal analogInput;
//voltageVal translatedVoltage;

int analogPin;

void setup() {
  analogInput.id = 1;
  analogInput.pinID=1;
  analogInput.reading = 1024;
  
 // translatedVoltage.id = 2;
  //translatedVoltage.translation = 5.0;
  //Initialize serial connection at 9600bps
  Serial.begin(9600);
}

void loop() {
  //Determine analog pin to read from COSMOS input
  while (Serial.available()){
    analogInput.pinID = Serial.read();
    analogPin = (int) analogInput.pinID;
  }

 analogInput.reading = analogRead(analogPin);
// translatedVoltage.translation = analogInput.reading*(5.0/1023.0);
 
 sendData();
  
}

void sendData(){
  analogInput.length = sizeof(analogInput);
 // translatedVoltage.length = sizeof(translatedVoltage);
  writeData((const char*)&analogInput, sizeof(analogInput));
  //writeData((const char*)&translatedVoltage, sizeof(translatedVoltage));
}

void writeData(const char* pkt, byte size){
  for(int i=0; i<size; i++)
  {
    Serial.write(pkt[i]);
  }
}


