﻿#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>

using namespace std;
using namespace chrono;

// Генерация файла с натуральными числами от 1 до N
void generateFile(const string& filename, int N)
{
    ofstream file(filename);
    for (int i = 1; i <= N; ++i)
    {
        file << i << "\n";
        if (i % 100 == 0) {
            file.flush();
        }
    }
    file.close();
}

// Последовательная обработка элементов файла (умножение на число) и запись в другой файл
void sequentialProcessing(const string& filename, const string& outputFilename, int multiplier)
{
    ifstream file(filename);
    ofstream outputFile(outputFilename);
    int num;

    while (file >> num)
    {
        int result = num * multiplier;
        outputFile << result << "\n";
    }

    file.close();
    outputFile.close();
}

// Многопоточная обработка элементов файла(Возведение в степень)
void parallelProcessing(const string& filename, const string& outputFilename,int exponent, int numThreads)
{
    ifstream file(filename);
    ofstream outputFile(outputFilename);
    vector<thread> threads;
    vector<int> nums;
    mutex myMutex;

    // Чтение элементов из файла
    int num;
    while (file >> num)
    {
        nums.push_back(num);
    }

    file.close();

    // Функция, которую выполняет каждый поток
    auto threadFunction = [&](int start, int end)
    {
        for (int i = start; i < end; ++i)
        {
            {
                lock_guard<mutex> lock(myMutex);
                int result = pow(nums[i], exponent);
                outputFile << result << "\n";
            }
        }
    };


    // Разделение элементов массива между потоками
    int chunkSize = nums.size() / numThreads;
    int remaining = nums.size() % numThreads;
    int start = 0;
    int end = 0;

    for (int i = 0; i < numThreads; ++i)
    {
        start = end;
        end = start + chunkSize;

        if (remaining > 0)
        {
            end++;
            remaining--;
        }

        threads.emplace_back(threadFunction, start, end);
    }

    // Ожидание завершения работы всех потоков
    for (auto& thread : threads)
    {
        thread.join();
    }

    file.close();
    outputFile.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Задание значения N
    int N;
    cout << "Введите значение N: ";
    cin >> N;

    // Генерация файла с натуральными числами от 1 до N
    string filename = "numbers.txt";
    generateFile(filename, N);

    // Задание значения для умножения
    int multiplier;
    cout << "Введите множитель: ";
    cin >> multiplier;

    int exponent;
    cout << "Введите степень: ";
    cin >> exponent;

    // Последовательная обработка элементов файла и запись в другой файл
    string sequentialOutputFilename = "result_sequential.txt";
    sequentialProcessing(filename, sequentialOutputFilename, multiplier);

    // Задание количества потоков для параллельной обработки
    int numThreads;
    cout << "Введите количество потоков для параллельной обработки: ";
    cin >> numThreads;

    // Замер времени многопоточной обработки
    auto start = high_resolution_clock::now();

    // Многопоточная обработка элементов файла и запись в другой файл
    string parallelInputFilename = sequentialOutputFilename;
    string parallelOutputFilename = "parallel_result.txt";
    parallelProcessing(parallelInputFilename, parallelOutputFilename, exponent, numThreads);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Время многопоточной обработки: " << duration.count() << " мс" << endl;

    return 0;
}