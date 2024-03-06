//14. Longest Common Prefix

#include <iostream>
#include <vector>

using namespace std;

string longestCommonPrefix(vector<string>& strs) 
{
    if (strs.empty()) 
	{
        return ""; // Если массив пуст, общего префикса нет, возвращаем пустую строку
    }

    string commonPrefix = strs[0]; // Инициализируем общий префикс первой строкой

    for (int i = 1; i < strs.size(); ++i) 
	{
        int j = 0;
        
        while (j < commonPrefix.size() && j < strs[i].size() && commonPrefix[j] == strs[i][j])
		{
            j++;
        }

        commonPrefix = commonPrefix.substr(0, j); // Обрезаем префикс до общей части
    }

    return commonPrefix;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	
    vector<string> strs = {"flower", "flow", "flight"};

    string result = longestCommonPrefix(strs);

    cout << "Самый длинный общий префикс: " << result <<endl;

    return 0;
}
