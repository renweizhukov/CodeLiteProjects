#ifndef THREESUM_H
#define THREESUM_H

#include <vector>
#include <algorithm>

using namespace std;

class ThreeSum {
public:
    vector<vector<int>> threeSum(vector<int> &num) 
    {
        vector<vector<int>> ret;
        sort(num.begin(), num.end());
        
        int n = num.size();
        for (int i = 0; (i < n - 2) && (num[i] <= 0); i++)
        {
            if ((i > 0) && (num[i] == num[i - 1]))
            {
                continue;
            }
            
            int j = i + 1;
            int k = n - 1;
            while ((num[k] >= 0) && (j < k))
            {
                int sum = num[j] + num[k];
                if (sum == -1*num[i])
                {
                    vector<int> tmp({num[i], num[j], num[k]});
                    ret.push_back(tmp);
                    do
                    {
                        k--;    
                    }
                    while ((num[k] == num[k + 1]) && (j < k));
                    
                    do
                    {
                        j++;
                    }
                    while ((num[j] == num[j - 1]) && (j < k));
                }
                else if (sum > -1*num[i])
                {
                    do
                    {
                        k--;    
                    }
                    while ((num[k] == num[k + 1]) && (j < k));
                }
                else
                {
                    do
                    {
                        j++;
                    }
                    while ((num[j] == num[j - 1]) && (j < k));
                }
            }
        }
        
        return ret;
    }
};

#endif // THREESUM_H