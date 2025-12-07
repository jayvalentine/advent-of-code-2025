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
    /// @return New position of the dial, and zero count.
    std::pair<int, int> apply(int starting_position) const
    {
        // Apply the initial rotation.
        int new_position = starting_position;

        int full_rotations = amount / 100;
        int partial_rotation = amount % 100;

        if (direction == Direction::Left)
        {
            new_position -= partial_rotation;
        }
        else if (direction == Direction::Right)
        {
            new_position += partial_rotation;
        }

        // We pass zero for at least the number of full rotations,
        // since each full rotation visits every number.
        int zero_count = full_rotations;

        bool passed_zero_with_partial_rotation = false;

        // Additionally, the partial rotation may have taken us to (or past) zero.
        if (new_position < 0)
        {
            new_position += 100;
            if (starting_position != 0)
            {
                passed_zero_with_partial_rotation = true;
            }
        }
        else if (new_position > 99)
        {
            new_position -= 100;
            passed_zero_with_partial_rotation = true;
        }

        if (passed_zero_with_partial_rotation || new_position == 0)
        {
            zero_count++;
        }

        return std::pair<int, int>(new_position, zero_count);
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
