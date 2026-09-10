#ifndef ADAPTER_HPP_
#define ADAPTER_HPP_

#include <iostream>

// "Target"
class ISwitch
{
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~ISwitch() = default;
};

// Client
class Button
{
    ISwitch& switch_;
public:
    Button(ISwitch& sw) : switch_(sw) {}
    
    void press()
    {
        switch_.on();
    }
   
    void release()
    {
        switch_.off();
    }
};



namespace LowLevel
{
// "Adaptee"
    class LedLight
    {
    public:
        void set_rgb(uint8_t red, uint8_t green, uint8_t blue)
        {
            std::cout << "Setting LED color to RGB(" << static_cast<int>(red) << ", "
                      << static_cast<int>(green) << ", " << static_cast<int>(blue) << ")" << std::endl;
        }
    };
}

namespace AlternativeLowLevel
{
    class CmykLight
    {
    public:
        void set_cmyk(uint8_t cyan, uint8_t magenta, uint8_t yellow, uint8_t black)
        {
            std::cout << "Setting CMYK light color to CMYK(" << static_cast<int>(cyan) << ", "
                      << static_cast<int>(magenta) << ", " << static_cast<int>(yellow) << ", "
                      << static_cast<int>(black) << ")" << std::endl;
        }
    };
}

// "Adapter"
class SwitchClassAdapter : public ISwitch, private LowLevel::LedLight
{
public:
    void on() override
    {
        set_rgb(255, 255, 255); // Turn on the LED with white color
    }

    void off() override
    {
        set_rgb(0, 0, 0); // Turn off the LED
    }
};

class SwitchCmykAdapter : public ISwitch, private AlternativeLowLevel::CmykLight
{
public:
    void on() override
    {
        set_cmyk(0, 0, 0, 0); // Turn on the CMYK light with white color
    }

    void off() override
    {
        set_cmyk(0, 0, 0, 255); // Turn off the CMYK light
    }
};

// "Adapter"
class SwitchObjectAdapter : public ISwitch
{
private:
    LowLevel::LedLight& adaptee_;

public:
    SwitchObjectAdapter(LowLevel::LedLight& adaptee)
        : adaptee_(adaptee)
    {
    }

    void on() override
    {
        adaptee_.set_rgb(255, 255, 255); // Turn on the LED with white color
    }

    void off() override
    {
        adaptee_.set_rgb(0, 0, 0); // Turn off the LED
    }
};

#endif /*ADAPTER_HPP_*/
