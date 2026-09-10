#ifndef SHAPE_GROUP_HPP
#define SHAPE_GROUP_HPP

#include "shape.hpp"

#include <memory>
#include <vector>

namespace Drawing
{
    // TODO: implement a composite for shapes
    // TODO: implement Iterator pattern for ShapeGroup composite that allows iterating over aggregated shapes
    class ShapeGroup : public Shape
    {
        using ShapePtr = std::unique_ptr<Shape>;
        std::vector<ShapePtr> shapes_;

    public:
        static constexpr const char* id = "ShapeGroup";

        using iterator = std::vector<ShapePtr>::iterator;
        using const_iterator = std::vector<ShapePtr>::const_iterator;

        ShapeGroup() = default;

        ShapeGroup(const ShapeGroup& source)
        {
            shapes_.reserve(source.shapes_.size());

            for(auto& s : source.shapes_)
                shapes_.push_back(s->clone());
        }

        void move(int dx, int dy)
        {
            for(auto& s : shapes_)
                s->move(dx, dy);
        }

        void draw() const 
        {
            for(auto& s : shapes_)
                s->draw();
        }

        std::unique_ptr<Shape> clone() const
        {
            return std::make_unique<ShapeGroup>(*this);
        }

        void add(std::unique_ptr<Shape> shp)
        {
            shapes_.push_back(std::move(shp));
        }

        size_t size() const
        {
            return shapes_.size();
        }

        iterator begin() { return shapes_.begin(); }
        iterator end() { return shapes_.end(); }

        const_iterator begin() const { return shapes_.begin(); }
        const_iterator end() const { return shapes_.end(); }
    };
} // namespace Drawing

#endif // SHAPE_GROUP_HPP
