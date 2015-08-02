#include <string>
#include <iostream>

using namespace std;

class Solution
{
public:
    void MoveSpacesToEnd(string &str)
    {
        int i = 0; // reading index
        int j = 0; // writing index
        // "-1" indicates that we haven't seen any non-space 
        // characters before we see this space.
        int cntOfSpaces = -1; 
        
        for (; i < str.length(); i++)
        {
            if (str[i] == '*')
            {
                if (cntOfSpaces == 0)
                {
                    // Keep the first space.
                    str[j] = '*';
                    j++;
                    cntOfSpaces++;
                }
            }
            else
            {
                str[j] = str[i];
                j++;
                cntOfSpaces = 0;
            }
        }
        
        // Set the remaining characters to spaces.
        for (; j < str.length(); j++)
        {
            str[j] = '*';
        }
    }
};

int main()
{    
	string str("**Hi*Wei**Ren***Tingting***He***");
    
    cout << "The original string is " << str << endl;
    
    Solution sol;
    sol.MoveSpacesToEnd(str);
    
    cout << "After moving extra spaces to the end, the new string is " << str << endl;
    
	return 0;
}
