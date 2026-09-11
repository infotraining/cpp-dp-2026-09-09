#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

enum StatisticsType {
    avg,
    min_max,
    sum
};

class Statistics
{
public:
    virtual ~Statistics() = default;
    virtual void calculate(Data& data_, Results& results_) = 0;
};

class Avg : public Statistics
{
public:
    void calculate(Data& data_, Results& results_) override
    {
        double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
        double avg = sum / data_.size();

        StatResult result("Avg", avg);
        results_.push_back(result);
    };
};

class Min : public Statistics
{
public:
    void calculate(Data& data_, Results& results_) override
    {
        double min = *(std::min_element(data_.begin(), data_.end()));

        results_.push_back(StatResult("Min", min));
    };
};

class Max : public Statistics
{
public:
    void calculate(Data& data_, Results& results_) override
    {
        double max = *(std::max_element(data_.begin(), data_.end()));

        results_.push_back(StatResult("Max", max));
    };
};

class Sum : public Statistics
{
public:
    void calculate(Data& data_, Results& results_) override
    {
        double sum = std::accumulate(data_.begin(), data_.end(), 0.0);

        results_.push_back(StatResult("Sum", sum));
    };
};

class Median : public Statistics
{
public:
    void calculate(Data& data_, Results& results_) override
    {
        if (data_.empty())
            return;

        std::sort(data_.begin(), data_.end());
        double median;
        size_t size = data_.size();
        if (size % 2 == 0)
        {
            median = (data_[size / 2 - 1] + data_[size / 2]) / 2.0;
        }
        else
        {
            median = data_[size / 2];
        }

        results_.push_back(StatResult("Median", median));
    };
};

class StatGroup : public Statistics
{
    std::vector<std::shared_ptr<Statistics>> statistics_;
public:
    void add_statistics(std::shared_ptr<Statistics> stat)
    {
        statistics_.push_back(stat);
    }

    void calculate(Data& data_, Results& results_) override
    {
        for (auto& stat : statistics_)
        {
            stat->calculate(data_, results_);
        }
    }
};

class DataAnalyzer
{
    std::shared_ptr<Statistics> calculate_strategy;
    Data data_;
    Results results_;

public:
    DataAnalyzer(std::shared_ptr<Statistics> calculate_strategy)
        : calculate_strategy{calculate_strategy}
    {
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(std::shared_ptr<Statistics> new_strategy)
    {
        calculate_strategy = new_strategy;
    }

    void calculate()
    {
        calculate_strategy->calculate(data_, results_);
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
    // TODO: Refactor the code above using Strategy Pattern
    // Hint#1: Define an interface for calculating Statistics
    // Hint#2: Use delegation technique to replace ifs in calculate() method
    auto avg = std::make_shared<Avg>();
    auto min = std::make_shared<Min>();
    auto max = std::make_shared<Max>();
    
    auto min_max = std::make_shared<StatGroup>();
    min_max->add_statistics(min);
    min_max->add_statistics(max);

    auto sum = std::make_shared<Sum>();

    auto basic_stats = std::make_shared<StatGroup>();
    basic_stats->add_statistics(avg);
    basic_stats->add_statistics(min_max);
    basic_stats->add_statistics(sum);

    auto median = std::make_shared<Median>(); 

    auto advanced_stats = std::make_shared<StatGroup>();
    advanced_stats->add_statistics(basic_stats);
    advanced_stats->add_statistics(median);

    DataAnalyzer da{basic_stats};
    da.load_data("stats_data.dat");
    da.calculate();

    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_stats_data.dat");
    da.set_statistics(advanced_stats);
    da.calculate();

    show_results(da.results());
}
