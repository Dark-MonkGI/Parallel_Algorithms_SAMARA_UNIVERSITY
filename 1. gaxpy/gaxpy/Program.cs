using System;
using System.IO;


namespace gaxpy
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //Формула gaxpy z = A*x + y 
            //Заем размерность матрицы
            Random rnd = new Random();
            int n = 5;
            int m = 5;
            string text = "";

            Console.WriteLine($"Mатрица размерностью: n={n} и m={m} \n");
            //Созаем матрицу с заданной размерностью 
            double[,] matrix = new double[n, m];


            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    matrix[i, j] = rnd.NextDouble();
                    Console.Write("{0} ", matrix[i, j]);
                    text = text + matrix[i, j] + "\n";
                }
                Console.WriteLine();
                //text = text + "\n";
            }
            write("matrix", text.Replace(",", "."));
            Console.WriteLine("---------");


            // Вектор
            text = "";
            Console.WriteLine($"Вектор x: \n");
            double[] vector = new double[m];
            for (int i = 0; i < m; i++)
            {
                vector[i] = rnd.NextDouble();
                Console.WriteLine(vector[i]);
                text = text + vector[i] + "\n";
            }
            write("vector", text.Replace(",", "."));
            Console.WriteLine("---------");


            // второй вектор
            text = "";
            Console.WriteLine($"Вектор y: \n");
            double[] vectorNext = new double[n];
            for (int i = 0; i < n; i++)
            {
                vectorNext[i] = rnd.NextDouble();
                Console.WriteLine(vectorNext[i]);
                text = text = text + vectorNext[i] + "\n";
            }
            write("vectorNext", text.Replace(",", "."));
            Console.WriteLine("---------");



            //Выходная матрица (уже вектор)
            double[] outputMatrixV = new double[n];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    outputMatrixV[i] += matrix[i, j] * vector[j]; 
                }
            }

            //итоговый вектор
            text = "";
            double[] output = new double[n];

            for (int i = 0; i < n; i++)
            {
                output[i] = outputMatrixV[i] + vectorNext[i];
            }




            Console.WriteLine($"Выходной итоговый вектор после gaxpy: \n");
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine($"{output[i]}");
                text = text + output[i] + "\n";
            }
            write("output", text.Replace(",", "."));

            Console.ReadKey();
        }

        private static void write(string nameFile, string text)
        {
            string path = $@"C:\Users\Dark_Monk\Desktop\gaxpy\{nameFile}.txt";
            // полная перезапись файла 
            using (StreamWriter writer = new StreamWriter(path, false))
            {
                writer.WriteLine(text);
            }
        }
    }
}
