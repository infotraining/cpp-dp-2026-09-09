#pragma once
#include <functional>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "shape.hpp"
#include "shape_readers_writers/shape_reader_writer.hpp"
#include "singleton.hpp"

template <typename T>
std::type_index make_type_index()
{
    return std::type_index(typeid(T));
}

template <typename T>
std::type_index make_type_index(const T &obj)
{
    return std::type_index(typeid(obj));
}

namespace Drawing
{
    using ShapeCreator = std::function<std::unique_ptr<Shape>()>;
    using ShapeRWCreator = std::function<std::unique_ptr<IO::ShapeReaderWriter>()>;

    template <typename TProduct, typename TId = std::string, typename TCreator = std::function<std::unique_ptr<TProduct>()>>
    class GenericFactory
    {
        std::unordered_map<TId, TCreator> creators_;

    public:
        bool register_creator(const TId &id, TCreator creator)
        {
            return creators_.emplace(id, creator).second;
        }

        std::unique_ptr<TProduct> create(const TId &id)
        {
            if (creators_.find(id) != creators_.end())
                return creators_.at(id)();
            throw std::invalid_argument("Unknown id");
        }
    };

    using ShapeFactory = GenericFactory<Shape>;
    using ShapeRWFactory = GenericFactory<IO::ShapeReaderWriter, std::type_index>;

    using ShapeFactorySingleton = SingletonHolder<ShapeFactory>;
    using ShapeRWFactorySingleton = SingletonHolder<ShapeRWFactory>;
}