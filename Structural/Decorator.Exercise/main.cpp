#include "starbugs_coffee.hpp"

#include <memory>

void client(std::shared_ptr<Coffee> coffee)
{
    std::cout << "Description: " << coffee->get_description() << "; Price: " << coffee->get_total_price() << std::endl;
    coffee->prepare();
}

class CoffeeBuilder
{
    std::unique_ptr<Coffee> coffee_;

public:
    CoffeeBuilder() = default;

    template <typename Base, typename... Args>
    CoffeeBuilder& create_base(Args&&... args)
    {
        static_assert(std::is_base_of<Coffee, Base>::value, "Base must derive from Coffee");
        coffee_ = std::make_unique<Base>(std::forward<Args>(args)...);
        return *this;
    }

    template <typename... Decorator>
    CoffeeBuilder& add()
    {
        static_assert((std::is_base_of<CoffeeDecorator, Decorator>::value && ...), "All Decorators must derive from CoffeeDecorator");
        (..., (coffee_ = std::make_unique<Decorator>(std::move(coffee_))));
        return *this;
    }

    std::unique_ptr<Coffee> get_coffee()
    {
        return std::move(coffee_);
    }
};

int main()
{
    std::unique_ptr<Coffee> cf = std::make_unique<Espresso>();
    client(std::move(cf));

    //-------------------------------------------
    std::cout << "\n\nCreating a decorated coffee...\n";

    // TODO: create a coffee decorated with ExtraEspresso, Whisky & WhippedCream. Pass decorated coffee to the client.
    auto coffee = std::make_shared<Espresso>();
    auto decorated_coffee_1 = std::make_shared<ExtraEspresso>(coffee);
    auto decorated_coffee_2 = std::make_shared<Whisky>(std::make_shared<Whisky>(decorated_coffee_1));
    auto decorated_coffee_3 = std::make_shared<Whisky>(decorated_coffee_2);
    auto decorated_coffee_4 = std::make_shared<WhippedCream>(decorated_coffee_3);
    client(decorated_coffee_4);
    client(decorated_coffee_3);

    //-------------------------------------------
    std::cout << "\n\nBuilding coffee using CoffeeBuilder...\n";

    CoffeeBuilder coffee_bld;
    coffee_bld
        .create_base<Espresso>()
        .add<Whisky>()
        .add<ExtraEspresso, Whisky, WhippedCream>();

    client(coffee_bld.get_coffee());
}
