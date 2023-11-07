#include <fmt/chrono.h>
#include <fmt/format.h>

#include "vectorint.hpp"

auto main(int argc, char **argv) -> int
{
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, World!\n");

    /* INSERT YOUR CODE HERE */
    VectorInt data(20);
    for(int i=0; i < data.max_size(); i++) {
        data.push_back(i*2);
    }
    data.push_back(42);
    data.push_back(48);
    for(int i=0; i < data.size(); i++) {
        fmt::print("data[{}] = {}\n", i, data.at(i));
    }
    fmt::print("data.size() = {}\n", data.size());
    //data.resize(42);
    //fmt::print("data.size() = {}\n", data.size());
    fmt::print("Pushing back 77\n");
     auto start = std::chrono::system_clock::now();
    data.push_back(77);
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    fmt::print("data[{}] = {}\n", data.size()-1, data.at(data.size()-1));
    fmt::print("The push back took {}\n", elapsed);
    return 0; /* exit gracefully*/
}
