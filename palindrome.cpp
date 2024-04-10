#include <iostream>
#include <string>

using namespace std;
 
string isPalindrome(string str)
{
    string s = str;
    if (s.length() == 1) {
        return "Enter string with length of 2 or more.";
    }
    for (int i = 0; i < s.length() / 2; i++) {
        if (s[i] != s[s.length() - i - 1]) {
            return "NotPalindrome";
        }
    }
    return "IsPalindrome";
}

int main()
{
    string s;
    cin >> s;

    cout << isPalindrome(s) << endl;
    return 0;
}
