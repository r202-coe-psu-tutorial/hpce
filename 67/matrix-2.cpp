#include <random>
#include <array>
#include <iostream>
#include <iomanip>
#include <chrono>

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

void operation(auto &A, auto &B, auto &C)
{
    generate_matrix(A);
    generate_matrix(B);

    // std::cout << std::endl
    //           << "Print A:" << std::endl;
    // print_matrix(A);

    // std::cout << std::endl
    //           << "Print B:" << std::endl;
    // print_matrix(B);

    auto t_start = std::chrono::high_resolution_clock::now();

    matrix_multification(A, B, C, A.size(), A.size());
    auto t_end = std::chrono::high_resolution_clock::now();

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    std::cout << "Processing time of " << A.size() << " time:" << elapsed_time_ms << " us" << std::endl;

    // std::cout << std::endl
    //           << "Print C:" << std::endl;
    // print_matrix(C, 4);
}

template <size_t ARRAY_SIZE>
void create_and_operate()
{
    std::array<std::array<int, ARRAY_SIZE>, ARRAY_SIZE> A = {}, B = {}, C = {};
    operation(A, B, C);
}

int main()
{
    create_and_operate<3>();
    create_and_operate<8>();
    create_and_operate<16>();
    create_and_operate<32>();
    create_and_operate<64>();
    create_and_operate<128>();
    create_and_operate<256>();
    create_and_operate<512>();
    create_and_operate<1024>();
    create_and_operate<2048>();

    return 0;
}
