#include "ShiftRegister.h"

InputOutput::ShiftRegister iRegister; // Input register chain
InputOutput::ShiftRegister oRegister; // Output register chain

int counter;

unsigned int *iPins;
unsigned int *oPins;

bool *joystickButton;


void setup() {
  // Set up input shift register
  iPins = new unsigned int[1];
  iPins[0] = 33;
  iRegister.SetInput(InputOutput::DataTransferType::Serial, iPins);
  iRegister.SetClockPin(34);
  iRegister.SetLatchPin(35);
  iRegister.SetDataSize(16);

  // Set up output shift register
  oPins = new unsigned int[1];
  oPins[0] = 30;
  oRegister.SetOutput(InputOutput::DataTransferType::Serial, oPins);
  oRegister.SetClockPin(31);
  oRegister.SetLatchPin(32);
  oRegister.SetDataSize(16);

  // Set up joystick input
  counter = 0;
  
  joystickButton = new bool[16];

  for (int i = 0; i < 16; ++i)
  {
    joystickButton[i] = false;
  }


  Joystick.useManualSend(true);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Read input register and send information through Serial and HID interface
  bool *dataToRead  = new bool[16];
  bool *dataToWrite = new bool[16];

  for (int i = 0; i < 16; ++i)
  {
    dataToRead[i]  = false;
    dataToWrite[i] = false;
  }

  iRegister.ReadData(dataToRead, 16);

  // Serial.println("================");
  // Serial.println("Button Debugging");
  // Serial.println("================");
  for (int i = 0; i < 16; ++i)
  {
    // Serial.println(dataToRead[i] ? "True" : "False");
    Joystick.button(i + 1, dataToRead[i]);
  }
  // Serial.println("================");

  Joystick.send_now();

  // Write to output register

  Serial.println("================");
  Serial.println("Output Debugging");
  Serial.println("================");
  for (int i = 0; i < 16; ++i)
  {
    dataToWrite[i] = (counter >> i) & 0b1;
    Serial.println(dataToWrite[i] ? "True" : "False");
  }
  Serial.println("================");

  oRegister.WriteData(dataToWrite, 16);

  ++counter;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}
