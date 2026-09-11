#include "src/turnstile.hpp"

#include <iostream>

using namespace std;

int main()
{
    TurnstileAPI api;

    Cpp17::Turnstile t{api};

    t.coin();
    t.pass();
    t.pass();
    t.coin();
    t.pass();
    t.coin();
    t.coin();
    t.coin();
    t.coin();
    t.coin();
    t.coin();

    t.audit();
}
