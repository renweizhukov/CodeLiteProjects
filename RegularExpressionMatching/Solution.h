#ifndef SOLUTION_H
#define SOLUTION_H

#include <string.h>
#include <vector>

using namespace std;

class Solution
{
//	bool matchFirst(const char *s, const char *p)
//	{
//        return (*p == *s || (*p == '.' && *s != '\0'));
//    }
	
public:
	Solution() {};
	~Solution() {};

//    bool isMatch(const char *s, const char *p) 
//	{
//        if (*p == '\0') return *s == '\0';  // Empty
//    
//        if (*(p + 1) != '*') 
//		{   
//			// Without *
//            if(!matchFirst(s,p)) 
//			{
//				return false;
//			}
//            return isMatch(s + 1, p + 1);
//        } 
//		else 
//		{ 
//		    // With *
//			// Skip this *
//            if(isMatch(s, p + 2)) 
//			{
//				return true;
//			}
//
//			// Include this *
//			if (matchFirst(s, p))
//		    {
//		        return isMatch(s + 1, p);
//		    }
//			
//			return false;
//        }
//    }
    bool isMatch(const char *s, const char *p)
    {
        if ((s == nullptr) || (p == nullptr))
        {
            return false;
        }
        
        size_t ls = strlen(s);
        size_t lp = strlen(p);
        
        vector<bool> m(lp + 1, false);
        m[0] = true;
        for (size_t j = 1; j < lp; j += 2)
        {
            if (p[j] == '*')
            {
                m[j + 1] = true;
            }
            else
            {
                break;
            }
        }
        
        vector<bool> tmp;
        for (size_t i = 0; i < ls; i++)
        {
            tmp.clear();
            tmp.push_back(false);
            for (size_t j = 0; j < lp; j++)
            {
                if (p[j] != '*')
                {
                    tmp.push_back(m[j] && ((p[j] == '.') || (p[j] == s[i])));
                }
                else
                {
                    if ((p[j - 1] == '.') || (p[j - 1] == s[i]))
                    {
                        tmp.push_back(m[j - 1] || m[j + 1] || tmp[j - 1]);
                    }
                    else
                    {
                        tmp.push_back(tmp[j - 1]);
                    }
                }
            }
            m = tmp;
        }
        
        return m[lp];
    }
};

#endif // SOLUTION_H