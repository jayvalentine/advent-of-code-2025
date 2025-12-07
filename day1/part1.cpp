#include <string>
#include <vector>
#include <fstream>
#include <iostream>

/// @brief Direction of rotation
enum class Direction
{
    Left,
    Right
};

/// @brief A single rotation of the dial.
class Rotation
{
public:
    /// @brief Construct a new Rotation.
    /// @param d Direction.
    /// @param a Amount of rotation in "clicks".
    Rotation(Direction d, int a) : direction(d), amount(a) {}

    /// @brief Apply this rotation to a dial position.
    /// @param starting_position Starting position of the dial.
    /// @return New position of the dial.
    int apply(int starting_position) const
    {
        // Apply the initial rotation.
        int new_position = starting_position;
        if (direction == Direction::Left)
        {
            new_position -= amount;
        }
        else if (direction == Direction::Right)
        {
            new_position += amount;
        }

        // Loop round if we've gone over the boundary.
        while (new_position < 0)
        {
            new_position += 100;
        }
        while (new_position > 99)
        {
            new_position -= 100;
        }

        return new_position;
    }

private:
    Direction direction;
    int amount;
};

Rotation ParseRotation(const std::string& s)
{
    auto direction = s[0];
    auto amount = s.substr(1);

    Direction d;
    if (direction == 'L')
    {
        d = Direction::Left;
    }
    else if (direction == 'R')
    {
        d = Direction::Right;
    }

    int a = std::stoi(amount);

    return Rotation(d, a);
}

std::vector<Rotation> ParseRotationList(const std::string& path)
{
    std::vector<Rotation> rotations;

    std::ifstream f(path);
    std::string line;
    while (std::getline(f, line)) {
        rotations.push_back(ParseRotation(line));
    }

    return rotations;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: part1 <data-file-path>" << std::endl;
        return 1;
    }

    std::string data_file_path = argv[1];
    auto rotations = ParseRotationList(data_file_path);

    int dial = 50;
    int zero_count = 0;
    for (const auto& r : rotations)
    {
        dial = r.apply(dial);
        if (dial == 0)
        {
            zero_count++;
        }
    }

    std::cout << "Password: " << zero_count << std::endl;
    return 0;
}
