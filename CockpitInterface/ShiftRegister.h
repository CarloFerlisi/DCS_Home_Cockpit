// ShiftRegister.h
//
// Author : Carlo Ferlisi
#ifndef _INPUTOUTPUT_SHIFTREGISTER_H_
#define _INPUTOUTPUT_SHIFTREGISTER_H_

namespace InputOutput
{

unsigned int charSize = sizeof(char);

enum DataTransferType 
{
    None         = 0
   ,Serial    // = 1
   ,Parallel  // = 2
};

class ShiftRegister
{
  public:
    // Constructors
    ShiftRegister();

    // Destructor
    ~ShiftRegister();

    // Methods
    void SetLatchPin(int pinLocation);                                      // Set the latch pin location
    void SetClockPin(int pinLocation);                                      // Set the clock pin location
    void SetDataSize(unsigned int dataSize);                                // Set the size of the shift register in bits

    void SetInput(DataTransferType inputType,   unsigned int *inputPins);   // Set the input type/pin(s)
    void SetOutput(DataTransferType outputType, unsigned int *outputPins);  // Set the output type/pin(s)

    unsigned char* ReadData(unsigned int dataSize) const;                  // Read data from shift register if output is defined
    void WriteData(unsigned char dataToWrite[], unsigned int dataSize);   // Write data into shift register if input is defined

  private:
    void resetInputPins();
    void resetOutputPins();

    // Member Variables
  private:
    int latchPin;                                                           // Location of the latch pin
    int clockPin;                                                           // Location of the clock pin
    unsigned int dataSize;                                                  // Size of the shift register in bits

    DataTransferType inputType;                                             // Defines shift register input type
    DataTransferType outputType;                                            // Defines shift register output type

    unsigned int *inputPins;                                                // Location of input pin(s)
    unsigned int *outputPins;                                               // Location of output pin(s)
};

} // namespace InputOutput

#endif // _INPUTOUTPUT_SHIFTREGISTER_H_