#ifndef COFFEEHELL_HPP_
#define COFFEEHELL_HPP_

#include <iostream>
#include <string>

class Coffee
{
public:
    virtual ~Coffee() = default;

    virtual float get_total_price() const = 0;
    virtual std::string get_description() const = 0;
    virtual void prepare() = 0;
};

class CoffeeBase : public Coffee
{
    float price_;
    std::string description_;

public:
    CoffeeBase(float price, const std::string &description) : price_{price}, description_{description}
    {
    }

    float get_total_price() const override
    {
        return price_;
    }

    std::string get_description() const override
    {
        return description_;
    }
};

class Espresso : public CoffeeBase
{
public:
    Espresso(float price = 4.0, const std::string &description = "Espresso")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect espresso: 7 g, 15 bar and 24 sec.\n";
    }
};

class Americano : public CoffeeBase
{
public:
    Americano(float price = 6.0, const std::string &description = "Americano")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect americano.\n";
    }
};

class Decafeinated : public CoffeeBase
{
public:
    Decafeinated(float price = 5.0, const std::string &description = "Decafeinated Coffee")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect decafeinated coffee.\n";
    }
};

// TODO: Add condiments that can be added to coffee: WhippedCream: 2.5$, Whisky: 6.0$, ExtraEspresso: 4.0$
// Hint#1: Add CoffeeDecorator and concrete decorators for condiments

class CoffeeDecorator : public Coffee
{
    std::shared_ptr<Coffee> coffee_;
    float price_;
    std::string description_;

public:
    CoffeeDecorator(std::shared_ptr<Coffee> coffee, float price, std::string description)
        : coffee_{coffee}, price_{price}, description_{description}
    {
    }

    float get_total_price() const override
    {
        return price_ + coffee_->get_total_price();
    }

    std::string get_description() const override
    {
        return description_ + " + " + coffee_->get_description();
    }

    void prepare() override
    {
        coffee_->prepare();
    }
};

class WhippedCream : public CoffeeDecorator
{
public:
    WhippedCream(std::shared_ptr<Coffee> coffee, float price = 2.5, const std::string &description = "Whipped Cream")
        : CoffeeDecorator{coffee, price, description}
    {
    }

    void prepare() override
    {
        CoffeeDecorator::prepare();
        std::cout << "Adding whipped cream.\n";
    }
};

class Whisky : public CoffeeDecorator
{
public:
    Whisky(std::shared_ptr<Coffee> coffee, float price = 6.0, const std::string &description = "Whisky")
        : CoffeeDecorator{coffee, price, description}
    {
    }

    void prepare() override
    {
        CoffeeDecorator::prepare();
        std::cout << "Adding whisky.\n";
    }
};

class ExtraEspresso : public CoffeeDecorator
{
public:
    ExtraEspresso(std::shared_ptr<Coffee> coffee, float price = 4.0, const std::string &description = "Extra Espresso")
        : CoffeeDecorator{coffee, price, description}
    {
    }

    void prepare() override
    {
        CoffeeDecorator::prepare();
        std::cout << "Adding extra espresso.\n";
    }
};

#endif /*COFFEEHELL_HPP_*/
