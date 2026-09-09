#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <variant>
#include <vector>
#include <cstdint>
#include <optional>
#include <cassert>

class Shape
{
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
    int radius_;

public:
    Circle(int radius) : radius_(radius) {}

    void draw() const override
    {
        std::cout << "Drawing a circle with radius " << radius_ << "\n";
    }
};

class Rectangle : public Shape
{
    int width_;
    int height_;

public:
    Rectangle(int width, int height) : width_(width), height_(height) {}

    void draw() const override
    {
        std::cout << "Drawing a rectangle with width " << width_ << " and height " << height_ << "\n";
    }
};

namespace Lib
{
    class Triangle
    {
        int base_;
        int height_;

    public:
        Triangle(int base, int height) : base_(base), height_(height) {}

        void draw() const
        {
            std::cout << "Drawing a triangle with base " << base_ << " and height " << height_ << "\n";
        }
    };
}

class MyTriangle : public Shape
{
    Lib::Triangle triangle_;

public:
    MyTriangle(int base, int height) : triangle_(base, height) {}

    void draw() const override
    {
        triangle_.draw();
    }
};

void client_renderer(const Shape &shape)
{
    shape.draw(); // late binding (runtime polymorphism)
}

class GraphicsDoc
{
    std::vector<std::unique_ptr<Shape>> shapes_;

public:
    void add_shape(std::unique_ptr<Shape> shape)
    {
        shapes_.push_back(std::move(shape));
    }

    void render() const
    {
        std::cout << "Rendering GraphicsDoc with " << shapes_.size() << " shapes:\n";
        for (const auto &shape : shapes_)
        {
            shape->draw(); // polymorphic call (runtime polymorphism - late binding)
        }
    }
};

class BasicDataAnalyzer
{
public:
    virtual std::optional<size_t> find_item(const std::vector<int> &data, int item) 
    {
        if (std::find(data.begin(), data.end(), item) != data.end())
        {
            return std::distance(data.begin(), std::find(data.begin(), data.end(), item));
        }
        return std::nullopt;
    }
};

class AdvancedDataAnalyzer : public BasicDataAnalyzer
{
public:
    std::optional<size_t> find_item(const std::vector<int> &data, int item) 
    {
        assert(std::is_sorted(data.begin(), data.end()));

        if (const auto [left, right] = std::equal_range(data.begin(), data.end(), item); left != right)
        {
            return std::distance(data.begin(), left);
        }

        return std::nullopt;
    }
};

class DataManager
{
    std::vector<int> data_;

public:
    void set_data(const std::vector<int> &data)
    {
        data_ = data;
    }

    void find_and_print_item(BasicDataAnalyzer &analyzer, int item) 
    {
        // If the analyzer is an AdvancedDataAnalyzer, sort the data to satisfy the precondition
        if (dynamic_cast<AdvancedDataAnalyzer *>(&analyzer))
        {
            std::sort(data_.begin(), data_.end());
        }

        auto result = analyzer.find_item(data_, item);
        if (result)
        {
            std::cout << "Item " << item << " found at index " << *result << "\n";
        }
        else
        {
            std::cout << "Item " << item << " not found\n";
        }
    }
};

void preconditions_postconditions_example()
{
    std::vector<int> data{1, 4, 5, 5, 1, 3, 4, 5};

    BasicDataAnalyzer analyzer;
    AdvancedDataAnalyzer advanced_analyzer;

    DataManager manager;
    manager.set_data(data);

    manager.find_and_print_item(analyzer, 3);
    manager.find_and_print_item(advanced_analyzer, 3);
}

void shapes_example()
{
    GraphicsDoc doc;
    doc.add_shape(std::make_unique<Circle>(5));
    doc.add_shape(std::make_unique<Rectangle>(4, 6));
    doc.add_shape(std::make_unique<MyTriangle>(3, 5));

    doc.render();
}

int main()
{
    // shapes_example();
    preconditions_postconditions_example();
}
