#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<string> GetAllPermutationsUnique(string &str)
    {
        vector<string> res;
        int n = str.length();
        if (n == 0)
        {
            return res;
        }
        
        // First add one string with str[0] to res.
        res.push_back(move(string({str[0]})));
        
        // Then add the subsequent characters to existing 
        // strings in res. To avoid duplicates, we insert 
        // the character backwards from the end until we 
        // see the same character.
        for (int i = 1; i < n; i++)
        {
            int resSize = res.size();
            for (int j = 0; j < resSize; j++)
            {
                // Append str[i] to the end of res[j].
                res[j].push_back(str[i]);
                
                // Insert str[i] into res[j] backwards from the end until 
                // we see the same character.
                string tmp = res[j];
                for (int k = i - 1; (k >= 0) && (tmp[k] != str[i]); k--)
                {
                    tmp[k + 1] = tmp[k];
                    tmp[k] = str[i];
                    res.push_back(tmp);
                }
            }
        }
        
        return res;
    }
};

int main()
{
	string str;
    cout << "Please type a string: ";
    cin >> str;
    cout << endl;
    
    Solution sol;
    vector<string> permutations = sol.GetAllPermutationsUnique(str);
    cout << "Print out all the unique permutations as below:" << endl;
    for (auto &s : permutations)
    {
        cout << s << endl;
    }
    
	return 0;
}
