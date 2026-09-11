#include "strategy.hpp"

int main()
{
    TextParagraph paragraph{std::make_shared<UpperCaseFormatter>()};
    paragraph.pretty_print();

    auto lcf = std::make_shared<LowerCaseFormatter>();
    paragraph.reset_formatter(lcf);
    paragraph.pretty_print();

    paragraph.reset_formatter(std::make_shared<CapitalizeFormatter>());
    paragraph.pretty_print();

    paragraph.reset_formatter(std::make_shared<SparseFormatter>());
    paragraph.set_text("Design Patterns");
    paragraph.pretty_print();
}
