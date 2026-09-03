#ifndef SHAPE_POLYMORPHIC_VARIANT_HPP
#define SHAPE_POLYMORPHIC_VARIANT_HPP

#include "shapes.hpp"

#include <memory>
#include <variant>

namespace PolymorphicWrappers
{
    /////////////////////////////////////////////////////////////////////////////
    // Restricted polymorphism with std::variant

    class ShapeVariant
    {
        using ShapeVariantT = std::variant<Circle, Triangle, Square>;
        ShapeVariantT shape_;

    public:
        template <typename T>
        ShapeVariant(const T& shp)
            : shape_{shp}
        { }

        void draw() const
        {
            std::visit([](const auto& s) { s.draw(); }, shape_);
        }

        void move(int dx, int dy)
        {
            std::visit([dx, dy](auto& s) { s.move(dx, dy); }, shape_);
        }
    };
} // namespace PolymorphicWrappers

#endif