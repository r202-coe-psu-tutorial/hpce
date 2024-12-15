#include <random>
#include <array>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <typeinfo>
#include <thread>
#include <future>

template <typename T>
void matrix_multification(T A, T B, T C, const size_t ROW, const size_t COL, size_t start=0, size_t end=0)
{
    // std::cout << std::format("{} Matrix size {}x{} => start: {} end: {}",std::this_thread::get_id(), ROW, COL, start, end) << std::endl;
    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < ROW; k++){
                // std::cout << std::format("-> {} {} {}", i, j, k) <<std::endl;
                C[i][j] += A[i][k] * B[k][j]; // row × column
            }
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

    auto t_start = std::chrono::high_resolution_clock::now();
    matrix_multification(A, B, C, ROW, COL, 0, ROW);
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << std::format("Processing time of {}x{} time: {} ms", ROW, COL, elapsed_time_ms) << std::endl;

}

void operation_thread(auto A, auto B, auto C, const size_t ROW, const size_t COL, size_t num_thread=0)
{

    size_t cpu_units = num_thread;
    if(cpu_units<=0)
        cpu_units = std::thread::hardware_concurrency();

    // std::cout << std::endl << std::endl << cpu_units << " concurrent threads are supported.\n"<<std::endl;
    
    auto t_start = std::chrono::high_resolution_clock::now();
   
    std::vector<std::thread> threads;
    if(ROW <= cpu_units){
        for(size_t i=0; i<ROW; i++){
            // std::cout<<i << ":" <<i+1<<std::endl;
            threads.push_back(
                std::move(
                    std::thread(
                        matrix_multification<decltype(A)>, A, B, C, ROW, COL, i, i+1
                    )
                )
            );
        }
    }
    else{
        unsigned int compute_row = ROW/cpu_units;
        for(size_t i=0; i<cpu_units; i++){
            unsigned int start = i*compute_row;
            unsigned int end = (i+1)*compute_row;
            if(i+1==ROW)
                end = ROW;

            threads.push_back(
                std::move(
                    std::thread(
                        matrix_multification<decltype(A)>, A, B, C, ROW, COL, start, end
                    )
                )
            );
        }

    }

    for(auto& t: threads){
        t.join();
    }



    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << std::format("Processing time of palallel {}x{} time: {} ms", ROW, COL, elapsed_time_ms) << std::endl;

}



void operation_async(auto A, auto B, auto C, const size_t ROW, const size_t COL, size_t num_thread=0)
{

    size_t cpu_units = num_thread;
    if(cpu_units<=0)
        cpu_units = std::thread::hardware_concurrency();

    // std::cout << std::endl << std::endl << cpu_units << " concurrent threads are supported.\n"<<std::endl;
    
    auto t_start = std::chrono::high_resolution_clock::now();
   
    std::vector<std::future<void>> futures;
    if(ROW <= cpu_units){
        for(size_t i=0; i<ROW; i++){
            // std::cout<<i << ":" <<i+1<<std::endl;
            futures.push_back(
                    std::async(
                        // std::launch::async,
                        // std::launch::deferred,
                        std::launch::async | std::launch::deferred,
                        matrix_multification<decltype(A)>, A, B, C, ROW, COL, i, i+1
                )
            );
        }
    }
    else{
        unsigned int compute_row = ROW/cpu_units;
        for(size_t i=0; i<cpu_units; i++){
            unsigned int start = i*compute_row;
            unsigned int end = (i+1)*compute_row;
            if(i+1==ROW)
                end = ROW;

            futures.push_back(
                    std::async(
                        // std::launch::async,
                        // std::launch::deferred,
                        std::launch::async | std::launch::deferred,
                        matrix_multification<decltype(A)>, A, B, C, ROW, COL, start, end
                    )
            );
        }

    }

    for(auto& f: futures){
        f.wait();
    }



    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << std::format("Processing time of async {}x{} time: {} ms", ROW, COL, elapsed_time_ms) << std::endl;

}





template <typename T>
void create_and_operate(const size_t ROW, const size_t COL)
{
    // std::array<std::array<int, ARRAY_SIZE>, ARRAY_SIZE> A = {}, B = {}, C = {};
    T **A, **B, **C;
    A = new T* [ROW];
    B = new T* [ROW];
    C = new T* [ROW];
    for( size_t i=0; i<ROW; ++i){
        A[i] = new T[COL];
        B[i] = new T[COL];
        C[i] = new T[COL];
    }

    generate_matrix(A, ROW, COL);
    generate_matrix(B, ROW, COL);

    // std::cout << std::endl
    //           << "Print A:" << std::endl;
    // print_matrix(A);

    // std::cout << std::endl
    //           << "Print B:" << std::endl;
    // print_matrix(B);


    operation(A, B, C, ROW, COL);

   
    for( size_t i=0; i<ROW; ++i){
        delete A[i];
        delete B[i];
        delete C[i];
    }
    delete A;
    delete B;
    delete C;

}

template <typename T>
void create_and_operate_thread(const size_t ROW, const size_t COL)
{
    // std::array<std::array<int, ARRAY_SIZE>, ARRAY_SIZE> A = {}, B = {}, C = {};
    T **A, **B, **C;
    A = new T* [ROW];
    B = new T* [ROW];
    C = new T* [ROW];
    for( size_t i=0; i<ROW; ++i){
        A[i] = new T[COL];
        B[i] = new T[COL];
        C[i] = new T[COL];
    }

    generate_matrix(A, ROW, COL);
    generate_matrix(B, ROW, COL);
    // std::cout << std::endl
    //           << "Print A:" << std::endl;
    // print_matrix(A, ROW, COL);
    //  std::cout << std::endl
    //           << "Print B:" << std::endl;
    // print_matrix(B, ROW, COL);
 
 
    operation_thread(A, B, C, ROW, COL);

    // std::cout << std::endl
    //           << "Print C:" << std::endl;
    // print_matrix(C, ROW, COL);
    

    for(size_t i=0; i<ROW; ++i){
        delete A[i];
        delete B[i];
        delete C[i];
    }
    delete A;
    delete B;
    delete C;

}



template <typename T>
void create_and_operate_async(const size_t ROW, const size_t COL)
{
    // std::array<std::array<int, ARRAY_SIZE>, ARRAY_SIZE> A = {}, B = {}, C = {};
    T **A, **B, **C;
    A = new T* [ROW];
    B = new T* [ROW];
    C = new T* [ROW];
    for( size_t i=0; i<ROW; ++i){
        A[i] = new T[COL];
        B[i] = new T[COL];
        C[i] = new T[COL];
    }

    generate_matrix(A, ROW, COL);
    generate_matrix(B, ROW, COL);
    // std::cout << std::endl
    //           << "Print A:" << std::endl;
    // print_matrix(A, ROW, COL);
    //  std::cout << std::endl
    //           << "Print B:" << std::endl;
    // print_matrix(B, ROW, COL);
 
 
    operation_async(A, B, C, ROW, COL);

    // std::cout << std::endl
    //           << "Print C:" << std::endl;
    // print_matrix(C, ROW, COL);
    

    for(size_t i=0; i<ROW; ++i){
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
    constexpr size_t sizes[]={3, 4, 8, 16, 32,64,128 };
    // constexpr size_t sizes[]={3, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
    // constexpr size_t sizes[]={3, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    for(const auto& s: sizes){
        create_and_operate<int>(s, s);
    }

    for(const auto& s: sizes){
        create_and_operate_thread<int>(s, s);
    }

    for(const auto& s: sizes){
        create_and_operate_async<int>(s, s);
    }



    return 0;
}
