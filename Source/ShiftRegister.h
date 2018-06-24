// ShiftRegister.h
// 
// Author : Carlo Ferlisi

#ifndef INPUTOUTPUT_SHIFTREGISTER
#define INPUTOUTPUT_SHIFTREGISTER

#include <list>

namespace InputOutput{


class ShiftRegister
{
// Methods
  private:
  public:
    ShiftRegister();
    ShiftRegister(int clockPin, int latchPin, int writeDelay=50, int readDelay=50);
    ShiftRegister(std::list<int> inputPins, std::list<int> outputPins, int clockPin, int latchPin, int writeDelay=50, int readDelay=50, bool isInputDevice=false);
    ~ShiftRegister();

    void SetInputPins(std::list<int> inputPinLocations){inputPins = inputPinLocations;}
    void SetOutputPins(std::list<int> outputPinLocations){outputPins = outputPinLocations;}
    
    void SetClockPin(int clockPinLocation){clockPin = clockPinLocation;}
    void SetLatchPin(int latchPinLocation){latchPin = latchPinLocation;}

    void SetWriteDelay(int writeDelay);
    void SetReadDelay(int readDelay);

    void SetAsInputRegister(){isInputDevice = true;}
    void SetAsOutputRegister(){isInputDevice = false;}

    virtual int  ReadOutput() = 0;
    virtual void WriteInput() = 0;

// Member Variables
  private:
    std::list<int> inputPins;
    std::list<int> outputPins;

    int clockPin;
    int latchPin;
    int writeDelay;
    int readDelay;

    bool isInputDevice;

};


} // InputOutput


#endif //INPUTOUTPUT_SHIFTREGISTER