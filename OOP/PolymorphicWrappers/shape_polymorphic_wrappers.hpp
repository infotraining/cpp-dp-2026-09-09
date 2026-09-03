#ifndef SHAPE_POLYMORPHIC_WRAPPERS_HPP
#define SHAPE_POLYMORPHIC_WRAPPERS_HPP

#include <memory>

namespace PolymorphicWrappers
{
    ////////////////////////////////////////////////////////////
    // Polymorphic wrapper for shapes
    ////////////////////////////////////////////////////////////

    class Shape
    {
        // shape interface - implementation detail
        class IShape
        {
        public:
            virtual ~IShape() = default;
            virtual void move(int x, int y) = 0;
            virtual void draw() const = 0;
            virtual std::unique_ptr<IShape> clone() = 0;
        };

        template <typename T>
        class ShapeWrapper : public IShape
        {
            T shape_;

        public:
            ShapeWrapper(const T& shp)
                : shape_(shp)
            {
            }

            ShapeWrapper(T&& shp)
                : shape_(std::move(shp))
            {
            }

            void draw() const override
            {
                shape_.draw();
            }

            void move(int x, int y) override
            {
                shape_.move(x, y);
            }

            std::unique_ptr<IShape> clone() override
            {
                return std::make_unique<ShapeWrapper<T>>(shape_);
            }
        };

    public:
        template <typename T, typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, Shape>>>
        Shape(T&& shp)
            : shape_(std::make_unique<ShapeWrapper<std::decay_t<T>>>(std::forward<T>(shp)))
        {
        }

        Shape(const Shape& src)
            : shape_{src.shape_->clone()}
        {
        }

        Shape& operator=(const Shape& src)
        {
            Shape temp(src);
            swap(temp);

            return *this;
        }

        template <class T>
        Shape& operator=(T&& src)
        {
            Shape(std::forward<T>(src)).swap(*this);
            return *this;
        }

        Shape(Shape&&) noexcept = default;
        Shape& operator=(Shape&&) noexcept = default;

        void swap(Shape& other)
        {
            shape_.swap(other.shape_);
        }

        void draw() const
        {
            shape_->draw();
        }

        void move(int x, int y)
        {
            shape_->move(x, y);
        }

    private:
        std::unique_ptr<IShape> shape_;
    };
} // namespace PolymorphicWrappers

#endif