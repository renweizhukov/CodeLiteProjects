#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
	string str;
    cout << "Please type an integer: ";
    cin >> str;
    cout << endl;
    int i = atoi(str.data());
    cout << "atoi(str) = " << i << endl;
	return 0;
}