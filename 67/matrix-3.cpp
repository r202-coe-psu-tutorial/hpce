#include <random>
#include <array>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <typeinfo>

void matrix_multification(auto A, auto B, auto C, const int ROW, const int COL)
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

void generate_matrix(auto matrix , const size_t ROW, const size_t COL)
{
    std::random_device rd;                        // obtain a random number from hardware
    std::mt19937 gen(rd());                       // seed the generator
    std::uniform_int_distribution<> distr(0, 10); // define the range
    for (int i=0; i<ROW; ++i)
    {

        for (int j=0; j<COL; ++j)
        {

            matrix[i][j] = distr(gen);
        }
    }
}

void print_matrix(auto matrix, const size_t ROW, const size_t COL, int space = 3)
{
    for (int i=0; i<ROW; ++i)
    {
        for (int j=0; j<COL; ++j)
        {
            std::cout << std::setw(space) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void operation(auto A, auto B, auto C, const size_t ROW, const size_t COL)
{
    generate_matrix(A, ROW, COL);
    generate_matrix(B, ROW, COL);

    // std::cout << std::endl
    //           << "Print A:" << std::endl;
    // print_matrix(A);

    // std::cout << std::endl
    //           << "Print B:" << std::endl;
    // print_matrix(B);

    auto t_start = std::chrono::high_resolution_clock::now();

    matrix_multification(A, B, C, ROW, COL);
    auto t_end = std::chrono::high_resolution_clock::now();

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    std::cout << "Processing time of " << ROW << " time:" << elapsed_time_ms << " ms" << std::endl;

    // std::cout << std::endl
    //           << "Print C:" << std::endl;
    // print_matrix(C, 4);
}

template <size_t ARRAY_SIZE>
void create_and_operate()
{
    // std::array<std::array<int, ARRAY_SIZE>, ARRAY_SIZE> A = {}, B = {}, C = {};
    int **A, **B, **C;
    A = new int* [ARRAY_SIZE];
    B = new int* [ARRAY_SIZE];
    C = new int* [ARRAY_SIZE];
    for( int i=0; i<ARRAY_SIZE; ++i){
        A[i] = new int[ARRAY_SIZE];
        B[i] = new int[ARRAY_SIZE];
        C[i] = new int[ARRAY_SIZE];
    }

    operation(A, B, C, ARRAY_SIZE, ARRAY_SIZE);

    for( int i=0; i<ARRAY_SIZE; ++i){
        delete A[i];
        delete B[i];
        delete C[i];
    }
    delete A;
    delete B;
    delete C;


}

int main()
{
    std::cout << "size: "<< 3<<std::endl;
    create_and_operate<3>();
    std::cout << "size: "<< 8<<std::endl;
    create_and_operate<8>();
    std::cout << "size: "<< 16<<std::endl;
    create_and_operate<16>();
    std::cout << "size: "<< 32<<std::endl;
    create_and_operate<32>();
    std::cout << "size: "<< 64<<std::endl;
    create_and_operate<64>();
    std::cout << "size: "<< 128<<std::endl;
    create_and_operate<128>();
    std::cout << "size: "<< 256<<std::endl;
    create_and_operate<256>();
    std::cout << "size: "<< 512<<std::endl;
    create_and_operate<512>();
    std::cout << "size: "<< 1024<<std::endl;
    create_and_operate<1024>();
    std::cout << "size: "<< 2048<<std::endl;
    create_and_operate<2048>();

    return 0;
}
