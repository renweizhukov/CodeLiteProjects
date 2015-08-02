#ifndef PERMUTE_H
#define PERMUTE_H

#include <vector>

using namespace std;

class Permute
{
public:
    Permute()
    {
    
    }
    
    ~Permute()
    {
        
    }

    vector<vector<int>> permute(vector<int> &num) 
    {
        vector<vector<int>> res({num});
        vector<int> tmpV;
        int n = num.size();
        int tmp = 0;
        
        for (int i = 0; i < n - 1; i++)
        {
            int m = res.size();
            for (int k = 0; k < m; k++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    tmpV = res[k];
                    tmp = tmpV[i];
                    tmpV[i] = tmpV[j];
                    tmpV[j] = tmp;
                    res.push_back(tmpV);
                }
            }
        }
        
        return res;
    }
};

#endif // PERMUTE_H
