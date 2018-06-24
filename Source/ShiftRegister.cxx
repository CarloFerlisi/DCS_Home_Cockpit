#include "ShiftRegister.h"

InputOutput::ShiftRegister::ShiftRegister()
{
    ShiftRegister(-1, -1);
}

InputOutput::ShiftRegister::ShiftRegister(int clockPin, int latchPin, int writeDelay=50, int readDelay=50)
{
    ShiftRegister(std::list<int>()
                 ,std::list<int>()
                 ,clockPin
                 ,latchPin
                 ,writeDelay
                 ,readDelay
                 ,isInputDevice
                 );
}

InputOutput::ShiftRegister::ShiftRegister(std::list<int> inputPins, std::list<int> outputPins, int clockPin, int latchPin, int writeDelay, int readDelay, bool isInputDevice) :
 inputPins(inputPins)
,outputPins(outputPins)
,clockPin(clockPin)
,latchPin(latchPin)
,writeDelay(writeDelay)
,readDelay(readDelay)
,isInputDevice(isInputDevice)
{
}
