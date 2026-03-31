#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <format>
#include <ranges>

template<typename T>
concept Formatter = requires(T s, const std::vector<int> &data) {
    { s.format(data) } -> std::same_as<std::string>;
};

struct CsvFormatter {
    std::string format(const std::vector<int> &data) const {
        if (data.empty()) return "";

        std::string result;
        for (const auto &el : data | std::views::take(data.size() - 1)) {
            result += std::format("{},", el);
        }
        return result + std::format("{}", data.back());
    }
};

struct JsonFormatter {
    std::string format(const std::vector<int> &data) const {
        if (data.empty()) return "[]";

        auto joined = data
            | std::views::transform([](int n) { return std::to_string(n); })
            | std::views::join_with(std::string(", "))
            | std::ranges::to<std::string>();

        return std::format("[{}]", joined);
    }
};

template<Formatter F>
class DataReporter {
    F formatter_;
    std::vector<int> data_;
  public:
    explicit DataReporter(std::vector<int> data): data_(std::move(data)) {}
    void print() {
        std::cout << formatter_.format(data_) << std::endl;
    }
};

int main() {
    DataReporter<CsvFormatter>({1, 2, 3}).print();
    DataReporter<JsonFormatter>({1, 2, 3}).print();
}

