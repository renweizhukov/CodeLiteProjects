#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution 
{
    typedef vector<pair<char, int>> VecChIndex;
    
public:
    int lengthOfLongestSubstringTwoDistinct(string s) 
    {
        int len = s.length();
        if (len <= 2)
        {
            return len;
        }
        else
        {
            int startIndex = 0;
            int maxLen = 2;
            VecChIndex vChIndex;
            for (int i = 0; i < len; i++)
            {
                int vChIndexIndex = -1;
                for (int j = 0; j < vChIndex.size(); j++)
                {
                    if (vChIndex[j].first == s[i])
                    {
                        vChIndexIndex = j;
                        break;
                    }
                }
                
                if (vChIndexIndex != -1)
                {
                    vChIndex[vChIndexIndex].second = i;
                }
                else
                {
                    if (vChIndex.size() == 2)
                    {
                        auto itToDelete = vChIndex.begin();
                        auto itToKeep = vChIndex.begin();
                        itToKeep++;
                        if (itToDelete->second > itToKeep->second)
                        {
                            auto itTmp = itToDelete;
                            itToDelete = itToKeep;
                            itToKeep = itTmp;
                        }
                        
                        if (i - startIndex > maxLen)
                        {
                            maxLen = i - startIndex;
                        }
                        
                        startIndex = itToDelete->second + 1;
                        vChIndex.erase(itToDelete);
                    }
                    
                    vChIndex.push_back(make_pair(s[i], i));
                }
            }
            
            if (len - startIndex > maxLen)
            {
                maxLen = len - startIndex;
            }
            
            return maxLen;
        }
    }
};

int main()
{
	string str("bacc");
    Solution sol;
    
    cout << "The maximum substring length of \"" << str << "\" is " << sol.lengthOfLongestSubstringTwoDistinct(str) << "." << endl;
	return 0;
}
