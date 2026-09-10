#include "adapter.hpp"
#include <iostream>

using namespace std;

void using_object_adapter()
{
    LowLevel::LedLight led;
    SwitchObjectAdapter switchAdapter(led);
    Button button(switchAdapter);

    button.press();
    button.release();
}

void using_class_adapter()
{
    SwitchCmykAdapter switchAdapter;
    Button button(switchAdapter);

    button.press();
    button.release();
}

int main()
{
    using_object_adapter();

    cout << endl;


    using_class_adapter();

    return 0;
}
