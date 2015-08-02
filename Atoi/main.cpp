#include <climits>
#include <string>
#include <iostream>
#include "Atoi.h"

using namespace std;

int main()
{
	string s;
	cout << "Please input a number in the string format: ";
	cin >> s;
	cout << "." << endl;
	
	Solution sol;
	int number = sol.atoi(s.data());
	cout << "The converted number is " << number << "." << endl;
	
	return 0;
}