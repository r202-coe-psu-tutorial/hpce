

#include <iostream>
#include <cstdint>

// bool is_prime(uint64_t number)
// {
//     if (number <= 1)
//     {
//         return false;
//     }
//     for (int64_t i = 2; i * i <= number; ++i)
//     {
//         if (number % i == 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }

bool is_prime(uint64_t number)
{
    if (number <= 1)
    {
        return false;
    }

    if (number == 2)
    {
        return true;
    }

    // if (number % 2 == 0)
    // {
    //     return false;
    // }

    for (uint64_t i = 3; i < number; i++)
    {
        // std::cout << "Checking divisibility by: " << i << std::endl;
        if (number % i == 0)
        {
            // std::cout << "Divisible by: " << i << std::endl;
            return false;
        }
    }
    return true;
}

int main()
{
    uint64_t num;
    std::cout << "Enter a number: ";
    std::cin >> num;

    std::cout << num << " : is a prime number -> " << is_prime(num) << std::endl;

    return 0;
}