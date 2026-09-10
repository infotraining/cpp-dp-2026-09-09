#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"

#include <memory>

namespace Drawing
{
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void move(int x, int y) = 0;
        virtual void draw() const = 0;
        virtual std::unique_ptr<Shape> clone() const = 0;
    };

    template <typename T, typename TShapeBase = Shape>
    class CloneableShape : public TShapeBase
    {
        std::unique_ptr<Shape> clone() const override
        {
            return std::make_unique<T>(static_cast<const T&>(*this));
        }
    };

    template <typename T>
    class ShapeBase : public CloneableShape<T>
    {
        Point coord_; 
    public:
        Point coord() const
        {
            return coord_;
        }

        void set_coord(const Point& pt)
        {
            coord_ = pt;
        }

        ShapeBase(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }
    };
} // namespace Drawing

#endif // SHAPE_HPP
