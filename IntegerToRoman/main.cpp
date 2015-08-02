#include <iostream>
#include <string>
#include "RomanToInteger.h"

using namespace std;

int main()
{
	cout << "Please enter an integer between 1 and 3999: ";
    int num;
    cin >> num;
    cout << endl;
    
    RomanToInteger sol;
    string roman = sol.intToRoman(num);
    
    cout << "The roman integer is: " << roman << "." << endl;
    
	return 0;
}
