#include <iostream>
#include <vector>
#include "Permute.h"

using namespace std;

int main()
{
	vector<int> num({7, 1, 4, 5, 2});
    
    Permute sol;
    vector<vector<int>> res = sol.permute(num);
    
    cin.get();
    
	return 0;
}