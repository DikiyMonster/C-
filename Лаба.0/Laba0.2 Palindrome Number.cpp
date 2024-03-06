//9. Palindrome Number
#include <iostream>

using namespace std;

bool isPalindrome(int x) {
    // Если число отрицательное или оканчивается нулем, то оно не является палиндромом
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int reversed = 0;
    int original = x;

    // Переворачиваем число
    while (x > 0) {
        int digit = x % 10;
        x /= 10;

        // Проверяем на переполнение
        if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && digit > 7)) {
            return false;
        }

        reversed = reversed * 10 + digit;
    }

    // Палиндром, если перевернутое число равно исходному
    return reversed == original;
}

int main() {
	
	setlocale(LC_ALL, "Russian");
	
    int x = 121;

    if (isPalindrome(x)) {
        cout << x << " - Это палиндром." << endl;
    } else {
        cout << x << " - Не палиндром." << endl;
    }

    return 0;
}
