#include <string>
#include <iostream>
#include "Solution.h"

using namespace std;

int main()
{
	string s("bbbba");
	string p(".*a*a");
	cout << "The input string is " << s << "." << endl;
	cout << "The input pattern is " << p << "." << endl;
	
	Solution sol;
	bool matchFlag = sol.isMatch(s.data(), p.data());

	cout << "The output match flag is " << matchFlag << endl;

	return 0;
}