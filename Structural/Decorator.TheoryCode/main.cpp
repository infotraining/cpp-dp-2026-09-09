#include "decorator.hpp"
#include <memory>

using namespace std;

void client(Component& c)
{
    c.operation();
}

int main()
{
    // Create ConcreteComponent and two Decorators
    auto c = make_shared<ConcreteComponent>();
    auto d1 = make_shared<ConcreteDecoratorA>(c);
    auto d2 = make_shared<ConcreteDecoratorB>(d1);

    client(*d2);

    cout << "\n\n";

    d2->set_component(c); // Change the wrapped component of d2 to c
    client(*d2); // Call the client function again to see the effect of the change

    cout << "\n";

    auto c2 = make_shared<ConcreteDecoratorA>(
                make_shared<ConcreteDecoratorB>(
                    make_shared<ConcreteComponent>()));
}
