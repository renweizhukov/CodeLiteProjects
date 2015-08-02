#include <iostream>
#include "ThreeSum.h"

int main()
{
	vector<int> input({1, -1, -1, 0});
    ThreeSum sol;
    vector<vector<int>> result = sol.threeSum(input);
    
    for (auto& sum3 : result)
    {
        cout << "[ ";
        for (auto& v : sum3)
        {
            cout << v << " ";
        }
        
        cout << "]" << endl;
    }
    
	return 0;
}
