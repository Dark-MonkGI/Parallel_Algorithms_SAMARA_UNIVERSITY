#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "ru");

    //Формула gaxpy z = A*x + y 
    //Заем размерность матрицы
    const int n = 250;
    const int m = 250;
    string text = "";

    cout << "Matrix shape: n=" << n << " and m=" << m << "\n";
    cout << "---------\n";
    //Созаем матрицу с заданной размерностью 
    float matrix[n][m]{};
    
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            matrix[i][j] = floor(r*1000000)/ 1000000;
            cout << matrix[i][j] << " ";
            text = text + to_string(matrix[i][j])  + "\n";
        }       
        cout << "\n";
    }
    cout << "\n";

    ofstream streamTextOne;
    streamTextOne.open("C:\\Users\\Dark_Monk\\Desktop\\gaxpy\\matrix.txt");
    std::replace(text.begin(), text.end(), ',', '.'); // replace all ',' to '.'
    streamTextOne << text;
    cout << "---------\n";
    cout << "\n";


    // Вектор
    text = "";
    cout << "Вектор x: \n";
    cout << "---------\n";
    float vector[m];

    for (int i = 0; i < m; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        vector[i] = floor(r * 1000000) / 1000000;
        cout << vector[i] << "\n";
        text = text + to_string(vector[i]) + "\n";
    }
    ofstream streamTextTwo;
    streamTextTwo.open("C:\\Users\\Dark_Monk\\Desktop\\gaxpy\\vector.txt");
    std::replace(text.begin(), text.end(), ',', '.'); // replace all ',' to '.'
    streamTextTwo << text;
    cout << "---------\n";
    cout << "\n";


    // второй вектор
    text = "";
    cout << "Вектор y: \n";
    cout << "---------\n";
    float vectorNext[n];

    for (int i = 0; i < n; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        vectorNext[i] = floor(r * 1000000) / 1000000;
        cout << vectorNext[i] << "\n";
        text +=  to_string(vectorNext[i]) + "\n";
    }
    ofstream streamTextThree;
    streamTextThree.open("C:\\Users\\Dark_Monk\\Desktop\\gaxpy\\vectorNext.txt");
    std::replace(text.begin(), text.end(), ',', '.'); // replace all ',' to '.'
    streamTextThree << text;
    cout << "---------\n";
    cout << "\n";


    //Умножение матрицы на вектор
    float outputMatrixV[n]{};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            outputMatrixV[i] += matrix[i][j] * vector[j];
        }
    }
    //Прибавляем вектор, получаем итоговый вектор, пишем в фаил
    text = "";
    cout << "Выходной итоговый вектор после gaxpy: \n";
    cout << "---------\n";
    float output[n];

    for (int i = 0; i < n; i++)
    {
        output[i] = outputMatrixV[i] + vectorNext[i];
        cout << output[i] << "\n";
        text += to_string(output[i]) + "\n";
    }
    ofstream streamTextFour;
    streamTextFour.open("C:\\Users\\Dark_Monk\\Desktop\\gaxpy\\output.txt");
    std::replace(text.begin(), text.end(), ',', '.'); // replace all ',' to '.'
    streamTextFour << text;
    cout << "---------\n";

}

