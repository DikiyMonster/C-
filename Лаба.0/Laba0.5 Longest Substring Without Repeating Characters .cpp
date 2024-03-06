//3. Longest Substring Without Repeating Characters
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int lengthOfLongestSubstring(string s) 
{
    unordered_map<char, int> charIndexMap;
    int maxLength = 0;
    int startIndex = 0;

    for (int i = 0; i < s.length(); ++i)//перебераем символы строки s начина€ с индекса 0 
	{
        if (charIndexMap.find(s[i]) != charIndexMap.end() && charIndexMap[s[i]] >= startIndex) 
		{
            startIndex = charIndexMap[s[i]] + 1;
        }

        charIndexMap[s[i]] = i;
        maxLength = max(maxLength, i - startIndex + 1);
    }

    return maxLength;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	
    string s = "abcabcbb";
    
    int result = lengthOfLongestSubstring(s);
    
    cout << "ƒлина самой длинной подстроки без повтор€ющихс€ символов: " << result << endl;
    return 0;
}
