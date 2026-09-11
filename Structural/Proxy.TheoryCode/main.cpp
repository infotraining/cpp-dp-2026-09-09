#include "proxy.hpp"
#include <functional>
#include <thread>

using ImageFactory = std::function<std::unique_ptr<Image>(std::string)>;

class ClientApplication
{
    std::vector<std::unique_ptr<Image>> images_;

public:
    ClientApplication(std::initializer_list<std::string> filenames, ImageFactory image_factory)
    {
        std::cout << "Loading images..." << std::endl;
        for (const auto& filename : filenames)
            images_.push_back(image_factory(filename));
        std::cout << "Images loaded images..." << std::endl;
    }

    void render(size_t index)
    {
        images_.at(index)->draw();
    }
};

int main()
{
    using namespace std::literals;
    auto image_filenames = {"drawing1.drw"s, "drawing2.drw"s, "drawing3.drw"s};

    auto bitmap_image_factory = [] (std::string filename) { return std::make_unique<Bitmap>(filename); };
    auto lazy_image_factory = [] (std::string filename) { return std::make_unique<LazyBitmap>(filename); };

    ClientApplication c{image_filenames, lazy_image_factory};

    std::cout << "Loading complete..." << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "Rendering images..." << std::endl;

    c.render(0);
    c.render(1);
    c.render(2);
}
