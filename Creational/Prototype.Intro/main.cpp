#include <cassert>
#include <iostream>
#include <memory>
#include <typeinfo>

class Engine
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::unique_ptr<Engine> clone() const = 0;
    virtual ~Engine() = default;
};

template <typename T, typename TEngineBase = Engine>
class CloneableEngine : public TEngineBase
{
public:
    using TEngineBase::TEngineBase; // inheriting constructors from the base engine class

    std::unique_ptr<Engine> clone() const override
    {
        return std::make_unique<T>(static_cast<const T &>(*this));
    }
};

class Diesel : public CloneableEngine<Diesel> // CRTP - Curiously Recurring Template Pattern
{
    int id_{0};

public:
    void start() override
    {
        std::cout << "Diesel starts\n";
    }

    void stop() override
    {
        std::cout << "Diesel stops\n";
    }

    // std::unique_ptr<Engine> clone() const override
    // {
    //     return std::make_unique<Diesel>(*this); // Diesel copy constructor
    // }
};

class TDI : public CloneableEngine<TDI, Diesel> // CRTP - Curiously Recurring Template Pattern
{
public:
    void start() override
    {
        std::cout << "TDI starts\n";
    }

    void stop() override
    {
        std::cout << "TDI stops\n";
    }
};

class Hybrid : public CloneableEngine<Hybrid> // CRTP - Curiously Recurring Template Pattern
{
public:
    void start() override
    {
        std::cout << "Hybrid starts\n";
    }

    void stop() override
    {
        std::cout << "Hybrid stops\n";
    }

    // std::unique_ptr<Engine> clone() const override
    // {
    //     return std::make_unique<Hybrid>(*this); // Hybrid copy constructor
    // }
};

class Car
{
    std::unique_ptr<Engine> engine_;

public:
    explicit Car(std::unique_ptr<Engine> engine)
        : engine_{std::move(engine)}
    {
    }

    Car(const Car &source)
        : engine_{source.engine_->clone()}
    {
    }

    void drive(int km)
    {
        engine_->start();
        std::cout << "Driving " << km << " kms\n";
        engine_->stop();
    }
};

namespace Cpp26
{
    class Engine
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual ~Engine() = default;
    };

    class Diesel : public Engine
    {
    public:
        Diesel() = default;

        Diesel(const Diesel &source)
        {
            std::cout << "Diesel(cc)\n";
        }

        Diesel(Diesel &&) = default;

        void start() override
        {
            std::cout << "Diesel starts\n";
        }

        void stop() override
        {
            std::cout << "Diesel stops\n";
        }
    };

    class TDI : public Diesel
    {
    public:
        TDI() = default;

        TDI(const TDI &source)
        {
            std::cout << "TDI(cc)\n";
        }

        TDI(TDI &&) = default;

        void start() override
        {
            std::cout << "TDI starts\n";
        }

        void stop() override
        {
            std::cout << "TDI stops\n";
        }
    };

    class Hybrid : public Engine
    {
    public:
        Hybrid() = default;

        Hybrid(const Hybrid &source)
        {
            std::cout << "Hybrid(cc)\n";
        }

        Hybrid(Hybrid &&) = default;

        void start() override
        {
            std::cout << "Hybrid starts\n";
        }

        void stop() override
        {
            std::cout << "Hybrid stops\n";
        }
    };

    class Car
    {
        std::polymorphic<Engine> engine_;

    public:
        template <typename TEngine>
        explicit Car(TEngine engine)
            : engine_{std::move(engine)}
        {
        }

        void drive(int km)
        {
            engine_->start();
            std::cout << "Driving " << km << " kms\n";
            engine_->stop();
        }
    };

    void polymorphic_demo()
    {
        std::cout << "engine\n";
        std::unique_ptr<Engine> engine = std::make_unique<Diesel>();
        engine->start();
        engine->stop();

        std::cout << "poly_engine\n";

        std::polymorphic<Engine> poly_engine(Diesel{});
        poly_engine->start();
        poly_engine->stop();

        poly_engine = std::polymorphic<Engine>{TDI{}};
        poly_engine->start();
        poly_engine->stop();

        std::cout << "copy_of_poly_engine\n";

        std::polymorphic<Engine> copy_of_poly_engine = poly_engine;
        copy_of_poly_engine->start();
        copy_of_poly_engine->stop();
    }
}



int main()
{
    Car c1{std::make_unique<TDI>()};
    c1.drive(100);

    std::cout << "\n";

    Car c2 = c1;
    c2.drive(200);

    Cpp26::polymorphic_demo();

    Cpp26::Car modern_car{Cpp26::Diesel{}};
    modern_car.drive(300);

    Cpp26::Car copy_of_modern_car = modern_car;
    copy_of_modern_car.drive(400);
}