//Модифицированный последовательный алгоритм поиска
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> sieveOfEratosthenes(int n) 
{
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= n; ++p) 
	{
        if (isPrime[p]) {
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

vector<int> segmentedSieve(int start, int end) 
{
    int limit = sqrt(end) + 1;
    vector<int> basePrimes = sieveOfEratosthenes(limit);

    vector<bool> isPrime(end - start + 1, true);

    for (int prime : basePrimes) 
	{
        for (int i = max(prime * prime, (start + prime - 1) / prime * prime); i <= end; i += prime) 
		{
            isPrime[i - start] = false;
        }
    }

    vector<int> primes;
    for (int i = start; i <= end; ++i) 
	{
        if (isPrime[i - start]) 
		{
            primes.push_back(i);
        }
    }

    return primes;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	
    int start = 50;
    int end = 150;

    vector<int> primes = segmentedSieve(start, end);

    cout << "Простые числа между " << start << " и " << end << " являются:\n";
    for (int prime : primes) {
        cout << prime << " ";
    }

    return 0;
}
