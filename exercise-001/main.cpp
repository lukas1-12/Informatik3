#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include <vector>
#include <random>

void print_vector(const std::vector<int>& vector) 
{
    for (int value : vector) { 
    fmt::print("{} ", value);
    fmt::print("\n");
}
}


auto main(int argc, char **argv) -> int
{
    int count = 20;
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-c,--count", count, "A count integer");
        app.parse(argc, argv);
        fmt::print("Count: {}\n", count);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    std::vector<int> randomValues;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 100);
    for (int i = 0; i < count; ++i) {
    randomValues.push_back(dis(gen));
    }
    fmt::print("Unsorted Numbers:\n");
    print_vector(randomValues);

    auto start = std::chrono::system_clock::now();
    std::sort(randomValues.begin(), randomValues.end());
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    fmt::print("Sorted Numbers:\n");
    print_vector(randomValues);
    fmt::print("time for the sort: {}", elapsed);

    return 0; /* exit gracefully*/

}
