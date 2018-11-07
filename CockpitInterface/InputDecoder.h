// InputDecoder.h
//
// Author : Carlo Ferlisi
#ifndef _INPUTOUTPUT_INPUTDECODER_H_
#define _INPUTOUTPUT_INPUTDECODER_H_

#include <string>

namespace InputOutput
{

class ShiftRegister;

struct InputMap
{
    unsigned int sizeOfData;
    unsigned char *rawData;
};

class InputDecoder
{
  public:
    // Constructor
    InputDecoder();

    // Destructor
    ~InputDecoder();

    // Methods
    void DecodeData(unsigned int dataSize, unsigned char *data);

    // Member Variables
    InputMap *dataMap;

    unsigned int numberOfInputs;
};

} // namespace InputOutput

#endif // _INPUTOUTPUT_INPUTDECODER_H_