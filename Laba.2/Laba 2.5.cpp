//Параллельный алгоритм №3: применение пула потоков
#include <iostream>
#include <vector>
#include <cmath>
#include <future>
#include <thread>

using namespace std;

vector<int> sieveOfEratosthenes(int n) 
{
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= n; ++p) 
	{
        if (isPrime[p]) 
		{
            for (int i = p * p; i <= n; i += p) 
			{
                isPrime[i] = false;
            }
        }
    }

    for (int p = 2; p <= n; ++p) 
	{
        if (isPrime[p]) 
		{
            primes.push_back(p);
        }
    }

    return primes;
}

vector<int> parallelSieve(int start, int end) 
{
    int limit = sqrt(end) + 1;
    vector<int> basePrimes = sieveOfEratosthenes(limit);

    vector<future<vector<int>>> futures;

    int numThreads = thread::hardware_concurrency();
    int segmentSize = (end - start + 1) / numThreads;

    for (int i = 0; i < numThreads; ++i) 
	{
        int segmentStart = start + i * segmentSize;
        int segmentEnd = (i == numThreads - 1) ? end : segmentStart + segmentSize - 1;

        futures.push_back(async(launch::async, [segmentStart, segmentEnd, &basePrimes]() 
		{
            vector<int> primes;

            for (int num = segmentStart; num <= segmentEnd; ++num) 
			{
                bool isPrime = true;

                for (int prime : basePrimes) 
				{
                    if (prime * prime > num)
                        break;

                    if (num % prime == 0) 
					{
                        isPrime = false;
                        break;
                    }
                }

                if (isPrime)
                    primes.push_back(num);
            }

            return primes;
        }));
    }

    vector<int> result;

    for (auto& future : futures) 
	{
        vector<int> primesInSegment = future.get();
        result.insert(result.end(), primesInSegment.begin(), primesInSegment.end());
    }

    return result;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	
    int start = 50;
    int end = 150;

    vector<int> primes = parallelSieve(start, end);

    cout << "Простые числа между " << start << " и " << end << " являются:\n";
    for (int prime : primes) 
	{
        cout << prime << " ";
    }

    return 0;
}
