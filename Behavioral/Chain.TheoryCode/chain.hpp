#ifndef CHAIN_HPP_
#define CHAIN_HPP_

#include <iostream>
#include <memory>
#include <string>

// "Handler"
class Handler
{
protected:
    std::shared_ptr<Handler> successor_;

public:
    Handler()
        : successor_{nullptr}
    { }

    void set_successor(std::shared_ptr<Handler> successor)
    {
        successor_ = successor;
    }

    void process_request(int request)
    {
        bool cancel = false;
        if (can_handle(request))
            handle_request(request, cancel);
        else if (!cancel && (successor_ != nullptr))
            successor_->process_request(request);
    }

    virtual ~Handler() = default;

protected:
    virtual bool can_handle(int request) const = 0;
    virtual void handle_request(int request, bool& cancel) = 0;
};

// "ConcreteHandler1"
class ConcreteHandler1 : public Handler
{
public:
    bool can_handle(int request) const override
    {
        return (request >= 0) && (request < 10);
    }

    void handle_request(int request, bool& cancel)
    {
        std::cout << "ConcreteHandler1 handled request " << request << std::endl;
        cancel = true;
    }
};

// "ConcreteHandler2"
class ConcreteHandler2 : public Handler
{
public:
    bool can_handle(int request) const override
    {
        return (request >= 10) && (request < 20);
    }

    void handle_request(int request, bool& cancel)
    {
        std::cout << "ConcreteHandler2 handled request " << request << std::endl;
        cancel = true;
    }
};

// "ConcreteHandler3"
class ConcreteHandler3 : public Handler
{
public:
    bool can_handle(int request) const override
    {
        return (request >= 20) && (request < 30);
    }

    void handle_request(int request, bool& cancel) override
    {   
        std::cout << "ConcreteHandler3 handled request " << request << std::endl;
        cancel = true;
    }
};

#endif /*CHAIN_HPP_*/
