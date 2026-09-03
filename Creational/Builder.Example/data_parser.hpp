#ifndef DATA_PARSER_HPP
#define DATA_PARSER_HPP

#include "report_builder.hpp"

#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <print>
#include <sstream>
#include <string>
#include <iostream>
#include <ranges>

class DataParser
{
public:
    explicit DataParser(ReportBuilder& report_builder)
        : report_builder_(report_builder)
    {
    }

    virtual void parse(const std::string& file_name)
    {
        report_builder_.add_header(std::string("Raport from file: ") + file_name);

        report_builder_.begin_data();

        std::ifstream fin(file_name.c_str());

        while (!fin.eof())
        {
            std::string row;
            std::getline(fin, row);

            std::istringstream iss(row);
            DataRow data(std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>());

            report_builder_.add_row(data);
        }

        report_builder_.end_data();

        report_builder_.add_footer("Copyright RaportBuilder 2013");
    }

    virtual ~DataParser() = default;

public:
    ReportBuilder& report_builder_;
};

class JsonDataParser : public DataParser
{
public:
    explicit JsonDataParser(ReportBuilder& report_builder)
        : DataParser(report_builder)
    {
    }

    void parse(const std::string& file_name) override
    {       
        std::ifstream fin(file_name);
        if (!fin.is_open())
        {
            std::print("Could not open file: {}\n", file_name);
            throw std::runtime_error("Could not open file: " + file_name);
        }
        
        nlohmann::json json_data = nlohmann::json::parse(fin);

        report_builder_.add_header(std::string("Raport from file: ") + file_name);
        
        report_builder_.begin_data();
        for (const auto& row_item : json_data)
        {
            DataRow row_values{
                row_item["firstName"].get<std::string>(),
                row_item["lastName"].get<std::string>(),
                row_item["gender"].get<std::string>(),
                std::to_string(row_item["age"].get<int>()),
            };

            report_builder_.add_row(row_values);
        }

        report_builder_.end_data();
        report_builder_.add_footer("Parsed using nlohmann::json library");
    }
};

#endif