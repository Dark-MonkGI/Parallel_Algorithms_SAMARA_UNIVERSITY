#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <chrono>
using namespace std;

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "ru");

    auto startTime = chrono::high_resolution_clock::now();
    //Формула gaxpy z = A*x + y 
    //Заем размерность матрицы
    const int n = 10000;
    const int m = n;

    cout << "Matrix shape: n=" << n << " and m=" << m << "\n";
    cout << "---------\n";
    //Созаем матрицу с заданной размерностью 
    auto* matrix = new float[n * m];


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            matrix[i * m + j] = floor(r * 10000000) / 10000000;
            //cout << matrix[i * m + j] << " ";
        }
        cout << "\n";
    }
    cout << "---------\n";
    cout << "\n";


    // Вектор
    cout << "Вектор x: \n";
    cout << "---------\n";
    float vector[m];

    for (int i = 0; i < m; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        vector[i] = floor(r * 10000000) / 10000000;
        //cout << vector[i] << "\n";
    }
    cout << "---------\n";
    cout << "\n";


    // второй вектор
    cout << "Вектор y: \n";
    cout << "---------\n";
    float vectorNext[n];

    for (int i = 0; i < n; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        vectorNext[i] = floor(r * 10000000) / 10000000;
        //cout << vectorNext[i] << "\n";
    }
    cout << "---------\n";
    cout << "\n";




    //Умножение матрицы на вектор
    float outputMatrixV[n]{};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            outputMatrixV[i] += matrix[i * m + j] * vector[j];
        }
    }
    //Прибавляем вектор, получаем итоговый вектор, пишем в фаил
    cout << "Выходной итоговый вектор после gaxpy: \n";
    cout << "---------\n";
    float output[n];

    for (int i = 0; i < n; i++)
    {
        output[i] = outputMatrixV[i] + vectorNext[i];
        cout << output[i] << "\n";
    }
    cout << "---------\n";

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = endTime - startTime;
    cout << "Duration " << duration.count() << "s" << endl;



    string mytime = "Duration " + to_string(duration.count()) + "s " + "Matrix:" + to_string(n) + "x" + to_string(m) + "\n";
    ofstream streamText;
    streamText.open("C:\\Users\\Dark_Monk\\Desktop\\gaxpy\\Time.txt", ofstream::app);
    //std::replace(mytime.begin(), mytime.end(), ',', '.'); // replace all ',' to '.'
    streamText << mytime;

    delete[] matrix;
}
