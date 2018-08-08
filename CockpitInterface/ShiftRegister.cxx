// ShiftRegister.cxx
//
// Author : Carlo Ferlisi
//

#include <cstddef>

#include "ShiftRegister.h"

namespace InputOutput
{

ShiftRegister::ShiftRegister() :
 latchPin(-1)
,clockPin(-1)
,dataSize(-1)
,inputType(DataTransferType::None)
,outputType(DataTransferType::None)
,inputPins(NULL)
,outputPins(NULL)
{
}

ShiftRegister::~ShiftRegister()
{
    // Deallocate input/output pin locations
    resetInputPins();
    resetOutputPins();
}

void ShiftRegister::SetLatchPin(int pinLocation)
{
    // Check if pin location is valid
    if (pinLocation >= 0)
    {
        latchPin = pinLocation;
    }
    else
    {
        // Placeholder for error checking
    }
}

void ShiftRegister::SetClockPin(int pinLocation)
{
    // Check if pin location is valid
    if (pinLocation >= 0)
    {
        clockPin = pinLocation;
    }
    else
    {
        // Placeholder for error checking
    }
}

void ShiftRegister::SetDataSize(unsigned int dataSize)
{
    this->dataSize = dataSize;
}

void ShiftRegister::SetInput(DataTransferType inputType, unsigned int *inputPins)
{
    this->inputType = inputType;
    resetInputPins();

    if (inputType != DataTransferType::None)
    {
        this->inputPins = inputPins;
    }
}

void ShiftRegister::SetOutput(DataTransferType outputType, unsigned int *outputPins)
{
    this->outputType = outputType;
    resetOutputPins();

    if (outputType != DataTransferType::None)
    {
        this->outputPins = outputPins;
    }
}

unsigned char* ShiftRegister::ReadData(unsigned int dataSize) const
{
    // Data is transfered byte by byte
    // Array of bytes is therefore used to collect data
    unsigned char* data = NULL;

    // Verify if the size of data to read matches the shift regiser size
    if (outputType != DataTransferType::None && this->dataSize == dataSize)
    {
        // Allocate minimum required space
        data = new unsigned char[(dataSize - 1) / charSize + 1]();

        // Read data
        if (outputType == DataTransferType::Serial)
        {
            // Read data from the shift register using a single output pin
            // Based on Carlyn Maw's code, found here : https://www.arduino.cc/en/Tutorial/ShftIn22
            unsigned int dataPin = inputPins[0];

            // Set the pin modes
            pinMode(latchPin, OUTPUT);
            pinMode(clockPin, OUTPUT);
            pinMode(dataPin, INPUT);

            // Pulse the latch pin to collect data into the shift register
            // TODO : Synchronize the pulse latch among shift registers to reduce delay
            digitalWrite(latchPin, HIGH);
            delayMicroseconds(20);
            digitalWrite(latchPin, LOW);

            // Shift the data through the register into the data array
            // The data pin will be set on the rising edge of the clock pin
            for (int i = 0; i < dataSize; ++i)
            {
                digitalWrite(clockPin, HIGH);
                delayMicroseconds(2);

                // Write data into appropriate byte and bit
                if (digitalRead(dataPin))
                {
                    data[i / charSize] |= (1 << (i % charSize));
                }

                digitalWrite(clockPin, LOW);
            }
        }
        else if (outputType == DataTransferType::Parallel)
        {
            // Read data from shift register using multiple output pins
            for (int i = 0; i < dataSize; ++i)
            {
                if (digitalRead(inputPins[i]))
                {
                    data[i / charSize] |= (1 << (i % charSize));
                }
            }
        }
    }
    else
    {
        // Placeholder for error checking
    }

    return data;
}

void ShiftRegister::WriteData(unsigned char dataToWrite[], unsigned int dataSize)
{
    // Verify if the size of data to be transfered matches the shift register size
    if (inputType != DataTransferType::None && this->dataSize == dataSize)
    {
        if (inputType == DataTransferType::Serial)
        {
            // Read data from the shift register using a single output pin
            // Based on Carlyn Maw's and Tom Igoe's code, found here : https://www.arduino.cc/en/Tutorial/ShftOut21

            unsigned int dataPin = outputPins[0];

            // Set pin modes
            pinMode(clockPin, OUTPUT);
            pinMode(dataPin, OUTPUT);

            digitalWrite(dataPin, LOW);
            digitalWrite(clockPin, LOW);

            for (int i = 0; i < dataSize; ++i)
            {
                // Set data pin to data value
                digitalWrite(dataPin, dataToWrite[i / charSize] & (1 << (i % charSize)));

                // Pulse the clock pin to store the value on the data pin
                digitalWrite(clockPin, HIGH);
                digitalWrite(dataPin,  LOW);  // Prevents bleed through

                delayMicroseconds(2);
                digitalWrite(clockPin, LOW);
            }
        }
        else if (inputType == DataTransferType::Parallel)
        {
            // Write the data onto the assigned pins
            for (int i = 0; i < dataSize; ++i)
            {
                digitalWrite(inputPins[i], dataToWrite[i / charSize] & (1 << (i % charSize)));
            }

            // Pulse the latch pin to store into the register
            digitalWrite(latchPin, HIGH);
            delayMicroseconds(20);
            digitalWrite(latchPin, LOW);
        }
    }
    else
    {
        // Placeholder for error checking
    }
}

void ShiftRegister::resetInputPins()
{
    // Delete array of input pins and reset pointer to 0
    delete inputPins;
    inputPins  = NULL;
}

void ShiftRegister::resetOutputPins()
{
    // Delete array of output pins and reset pointer to 0
    delete outputPins;
    outputPins = NULL;
}

} // namespace InputOutput