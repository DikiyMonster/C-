//Последовательный алгоритм "Решето Эратосфена"
#include <iostream>
#include <vector>

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

int main() 
{
	setlocale(LC_ALL, "Russian");
    int n = 100;
    vector<int> primes = sieveOfEratosthenes(n);

    cout << "Простые числа до " << n << " являются: ";
    for (int prime : primes) 
	{
        cout << prime << " ";
    }

    return 0;
}

