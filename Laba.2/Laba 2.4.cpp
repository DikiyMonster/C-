//Параллельный алгоритм №2: декомпозиция набора простых чисел
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

void parallelPrimeSearch(vector<int>& primes, int start, int end) 
{
    vector<bool> isPrime(end - start + 1, true);

    for (int i = 2; i * i <= end; ++i) 
	{
        if (isPrime[i - start]) 
		{
            for (int j = max(i * i, (start + i - 1) / i * i); j <= end; j += i) 
			{
                isPrime[j - start] = false;
            }
        }
    }

    lock_guard<mutex> lock(mtx);
    for (int i = start; i <= end; ++i) 
	{
        if (isPrime[i - start]) 
		{
            primes.push_back(i);
        }
    }
}

int main() 
{
	
	setlocale(LC_ALL, "Russian");
	
    int start = 50;
    int end = 150;
    int numThreads = 2; // При необходимости отрегулируйте количество потоков.

    vector<int> primes;
    vector<thread> threads;

    int segmentSize = (end - start + 1) / numThreads;
    for (int i = 0; i < numThreads; ++i) 
	{
        int segmentStart = start + i * segmentSize;
        int segmentEnd = (i == numThreads - 1) ? end : segmentStart + segmentSize - 1;
        threads.emplace_back(parallelPrimeSearch, ref(primes), segmentStart, segmentEnd);
    }

    for (auto& thread : threads) 
	{
        thread.join();
    }

    cout << "Простые числа между " << start << " и " << end << " являются:\n";
    for (int prime : primes) 
	{
        cout << prime << " ";
    }

    return 0;
}
