using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gaxpy
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //Формула gaxpy z = A*x + y 
            //Заем размерность матрицы
            Random rnd = new Random();
            int n = rnd.Next(3, 7);
            int m = rnd.Next(3, 7);

            Console.WriteLine($"Mатрица размерностью: n={n} и m={m} \n");
            //Созаем матрицу с заданной размерностью 
            int[,] matrix = new int[n, m];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    matrix[i, j] = rnd.Next(0, 10);
                    Console.Write("{0} ", matrix[i, j]);

                }
                Console.WriteLine();
            }
            Console.WriteLine("---------");


            // Вектор
            Console.WriteLine($"Вектор x: \n");
            int[] vector = new int[m];
            for (int i = 0; i < m; i++)
            {
                vector[i] = rnd.Next(0, 10);
                Console.WriteLine(vector[i]);
            }

            Console.WriteLine("---------");


            // второй вектор
            Console.WriteLine($"Вектор y: \n");

            int[] vectorNext = new int[n];
            for (int i = 0; i < n; i++)
            {
                vectorNext[i] = rnd.Next(0, 10);
                Console.WriteLine(vectorNext[i]);
            }
            Console.WriteLine("---------");  

            //Выходная матрица (уже вектор)
            int[] outputMatrixV = new int[n];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    outputMatrixV[i] += matrix[i, j] * vector[j]; 
                }
            }


            //итоговый вектор
            int[] output = new int[n];

            for (int i = 0; i < n; i++)
            {
                output[i] = outputMatrixV[i] + vectorNext[i];
            }




            Console.WriteLine($"Выходной итоговый вектор после gaxpy: \n");
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine($"{output[i]}");
            }


            Console.ReadKey();
        }
    }
}
