#include <random>
#include <array>
#include <iostream>
#include <iomanip>

void matrix_multification(auto &A, auto &B, auto &C, const int ROW, const int COL)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < ROW; k++)
                C[i][j] += A[i][k] * B[k][j]; // row × column
        }
    }
}

// for (int i = 0; i < N; i++) {
// for (int j = 0; j < N; j++) {
// int sum = 0;
// for (int k = 0; k < N; k++)
// sum += A[i][k] * B[j][k]; // row × row
// C[i][j] = sum;
// }
// }

void generate_matrix(auto &matrix)
{
    std::random_device rd;                        // obtain a random number from hardware
    std::mt19937 gen(rd());                       // seed the generator
    std::uniform_int_distribution<> distr(0, 10); // define the range
    for (auto &row : matrix)
    {

        for (auto &col : row)
        {
            col = distr(gen);
        }
    }
}

void print_matrix(auto &matrix, int space = 3)
{
    for (auto &row : matrix)
    {
        for (auto &col : row)
        {
            std::cout << std::setw(space) << col << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    const unsigned long long ROW = 3;
    const unsigned long long COL = 3;
    std::array<std::array<int, COL>, ROW> A = {}, B = {}, C = {};
    generate_matrix(A);
    generate_matrix(B);

    std::cout << std::endl
              << "Print A:" << std::endl;
    print_matrix(A);

    std::cout << std::endl
              << "Print B:" << std::endl;
    print_matrix(B);

    matrix_multification(A, B, C, ROW, COL);
    std::cout << std::endl
              << "Print C:" << std::endl;
    print_matrix(C, 4);

    return 0;
}
