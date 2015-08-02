#include <iostream>
#include <string>
#include "WildcardMatching.h"

using namespace std;

int main()
{
	string s("abefcdgiescdfimde");
    string p("ab*cd?i*de");
    
    cout << "The string s is " << s << endl;
    cout << "The pattern string p is " << p << endl;
    
    WildcardMatching sol;
    bool ret = sol.isMatch(s.data(), p.data());
    cout << std::boolalpha;
    cout << "isMatch(s, p) returns " << ret << endl;
    
	return 0;
}
