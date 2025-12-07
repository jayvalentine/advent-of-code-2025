#include "rotation.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: part2 <data-file-path>" << std::endl;
        return 1;
    }

    std::string data_file_path = argv[1];
    auto rotations = ParseRotationList(data_file_path);

    int dial = 50;
    int zero_count = 0;
    for (const auto& r : rotations)
    {
        auto [new_dial, passed_zero_count] = r.apply(dial);
        std::cout << "New position: " << new_dial << ", passed zero " << passed_zero_count << " times" << std::endl;
        dial = new_dial;
        zero_count += passed_zero_count;
    }

    std::cout << "Password: " << zero_count << std::endl;
    return 0;
}
