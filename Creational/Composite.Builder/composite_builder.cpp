#include <iostream>
#include <optional>
#include <string>

#include "person.hpp"
#include "person_builder.hpp"

int main()
{
    // clang-format off
    Person j = Person::create("Zenon", "Anonim")
        .lives()
            .at("Ulica")
            .in("Miasto")
            .with_postal_code("00-000")
        .works()
            .in_company("Zeiss")
            .with_tax_id("PL76200");


    Person p = 
        Person::create("Jan", "Kowalski")
            .lives()
                .at("Westerplatte 2/8")
                .in("Cracow")
                .with_postal_code("31-000")
            .works()
                .in_company("Infotraining")
                .with_tax_id("PL00011100");


    std::cout << p.description() << "\n";

    Person other = Person::create("Adam", "Nowak")
        .lives()
            .at("Elm street")
            .in("New York")
            .with_postal_code("1241243")
        .works()
            .in_company("UN")
            .with_tax_id("6124167253716");
    // clang-format on
}