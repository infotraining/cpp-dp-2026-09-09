#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <algorithm>
#include <cctype>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// "Strategy"
class Formatter
{
public:
    virtual std::string format(const std::string& data) = 0;
    virtual ~Formatter() = default;
};

// "ConcreteStrategyA"
class UpperCaseFormatter : public Formatter
{
public:
    std::string format(const std::string& data) override
    {
        std::string transformed_data{data};

        std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::toupper(c); });

        return transformed_data;
    }
};

// "ConcreteStrategyB"
class LowerCaseFormatter : public Formatter
{
public:
    std::string format(const std::string& data) override
    {
        std::string transformed_data{data};

        std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::tolower(c); });

        return transformed_data;
    }
};

// "ConcreteStrategyC"
class CapitalizeFormatter : public Formatter
{
public:
    std::string format(const std::string& data) override
    {
        std::string transformed_data{data};

        if (data.size() >= 1)
        {
            transformed_data[0] = static_cast<char>(std::toupper(data.front()));

            std::transform(data.begin() + 1, data.end(), transformed_data.begin() + 1, [](char c) { return std::tolower(c); });
        }

        return transformed_data;
    }
};

class SparseFormatter : public Formatter
{
public:
    std::string format(const std::string& data) override
    {
        std::string transformed_data{data};

        for (size_t i = 0; i < data.size(); ++i)
        {
            transformed_data[i] = (i % 2 == 0) ? static_cast<char>(std::toupper(data[i])) : static_cast<char>(std::tolower(data[i]));
        }

        return transformed_data;
    }
};

// "Context"
class TextParagraph
{
    std::shared_ptr<Formatter> formatter_strategy_;
    std::string text_ = "text";

public:
    TextParagraph(std::shared_ptr<Formatter> strategy)
        : formatter_strategy_{strategy}
    {
    }

    void reset_formatter(std::shared_ptr<Formatter> new_strategy)
    {
        formatter_strategy_ = new_strategy;
    }

    void pretty_print()
    {
        std::cout << "Data: " << formatter_strategy_->format(text_) << std::endl;
    }

    std::string text() const
    {
        return text_;
    }

    void set_text(const std::string& text)
    {
        text_ = text;
    }
};

namespace ModernCpp
{
    using Formatter = std::function<std::string(const std::string&)>;

    // "ConcreteStrategyA"
    class UpperCaseFormatter
    {
    public:
        std::string operator()(const std::string& data)
        {
            std::string transformed_data{data};

            std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::toupper(c); });

            return transformed_data;
        }
    };

    // "ConcreteStrategyB"
    class LowerCaseFormatter
    {
    public:
        std::string operator()(const std::string& data)
        {
            std::string transformed_data{data};

            std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::tolower(c); });

            return transformed_data;
        }
    };

    // "ConcreteStrategyC"
    class CapitalizeFormatter
    {
    public:
        std::string operator()(const std::string& data)
        {
            std::string transformed_data{data};

            if (data.size() >= 1)
            {
                transformed_data[0] = static_cast<char>(std::toupper(data.front()));

                std::transform(data.begin() + 1, data.end(), transformed_data.begin() + 1, [](char c) { return std::tolower(c); });
            }

            return transformed_data;
        }
    };

    class SparseFormatter
    {
    public:
        std::string operator()(const std::string& data)
        {
            std::string transformed_data{data};

            for (size_t i = 0; i < data.size(); ++i)
            {
                transformed_data[i] = (i % 2 == 0) ? static_cast<char>(std::toupper(data[i])) : static_cast<char>(std::tolower(data[i]));
            }

            return transformed_data;
        }
    };

    class TextParagraph
    {
        Formatter formatter_strategy_;
        std::string text_ = "text";

    public:
        TextParagraph(Formatter strategy)
            : formatter_strategy_{strategy}
        {
        }

        void reset_formatter(Formatter new_strategy)
        {
            formatter_strategy_ = new_strategy;
        }

        void pretty_print()
        {
            std::cout << "Data: " << formatter_strategy_(text_) << std::endl;
        }

        std::string text() const
        {
            return text_;
        }

        void set_text(const std::string& text)
        {
            text_ = text;
        }
    };
} // namespace ModernCpp

#endif /*STRATEGY_HPP_*/
