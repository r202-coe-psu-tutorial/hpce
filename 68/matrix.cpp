#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <stdfloat>
#include <thread>
using namespace std;

// Function to multiply two matrices
// Matrix A: m x n, Matrix B: n x p, Result: m x p
void matrixMultiplication(vector<vector<float64_t>> &A, vector<vector<float64_t>> &B, vector<vector<float64_t>> &C, int start_row, int end_row)
{
    int m = A.size();    // number of rows in A
    int n = A[0].size(); // number of columns in A (must equal rows in B)
    int p = B[0].size(); // number of columns in B

    // Perform multiplication
    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to print a matrix
void printMatrix(const vector<vector<float64_t>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (float64_t val : row)
        {
            cout << val << " ";
        }
        cout << "\n";
    }
}

// Function to create a matrix with random values
// rows: number of rows, cols: number of columns
void createRandomMatrix(vector<vector<float64_t>> &matrix)
{
    // vector<vector<float64_t>> matrix(rows, vector<float64_t>(cols));

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = rand() % 10; // Random values from 0 to 99
        }
    }
}

int main()
{
    srand(time(0)); // Seed for random number generation

    int size;
    int num_threads = 2;

    // Get dimensions for first matrix
    cout << "Enter dimensions for Matrix A&B:\n";
    cout << "Number of rows and columns: ";
    cin >> size;

    cout << "Enter number of threads: ";
    cin >> num_threads;
    // Check if matrices can be multiplied
    // Create random matrices
    vector<vector<float64_t>> A(size, vector<float64_t>(size));
    vector<vector<float64_t>> B(size, vector<float64_t>(size));
    cout << "Creating random matrices A ...\n";
    createRandomMatrix(A);

    cout << "Creating random matrices B ...\n";
    createRandomMatrix(B);

    // cout << "\n--- Matrix A (" << size << "x" << size << ") ---\n";
    // printMatrix(A);

    // cout << "\n--- Matrix B (" << size << "x" << size << ") ---\n";
    // printMatrix(B);

    // Perform matrix multiplication
    vector<vector<float64_t>> result(size, vector<float64_t>(size, 0));
    // matrixMultiplication(A, B, result, 0, size);

    cout << "\n--- Performing multiplication using " << num_threads << " threads ---\n";
    vector<std::thread> threads;
    int rows_per_thread = size / num_threads;
    for (int t = 0; t < num_threads; t++)
    {
        int start_row = t * rows_per_thread;
        int end_row = (t == num_threads - 1) ? size : start_row + rows_per_thread;

        std::cout << "Thread " << t << " processing rows " << start_row << " to " << end_row - 1 << std::endl;
        threads.push_back(
            std::thread(
                matrixMultiplication, ref(A), ref(B), ref(result), start_row, end_row)

        );
    }

    for (auto &th : threads)
    {
        th.join();
    }

    cout << "\n--- Result A * B (" << size << "x" << size << ") ---\n";
    printMatrix(result);

    return 0;
}
