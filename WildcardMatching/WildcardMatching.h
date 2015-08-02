#ifndef WILDCARDMATCHING_H
#define WILDCARDMATCHING_H

class WildcardMatching
{
public:
    WildcardMatching()
    {
        
    }
    
    ~WildcardMatching()
    {
        
    }

    bool isMatch(const char *s, const char *p) 
    {
        if ((s == nullptr) || (p == nullptr))
        {
            return false;
        }
        
        if ((*p == *s) || (*p == '?'))
        {
            if (*s == '\0')
            {
                return (*p != '?');
            }
            else
            {
                return isMatch(s + 1, p + 1);
            }
        }
        else
        {
            if (*p == '*')
            {
                do
                {
                    p++;
                }
                while (*p == '*');
                
                const char *nextStar = p;
                while ((*nextStar != '\0') && (*nextStar != '*'))
                {
                    nextStar++;
                }
                
                const char *ss = s;
                const char *pp = p;
                while (*ss != '\0')
                {
                    s = ss;
                    p = pp;
                    while (p <= nextStar - 1)
                    {
                        if ((*p != *s) && (*p != '?'))
                        {
                            break;
                        }
                        p++;
                        s++;
                    }
                    
                    if (p == nextStar)
                    {
                        return isMatch(s, p);  
                    }
                    
                    ss++;
                }

                return (*pp == '\0');
            }
            else
            {
                return false;
            }
        }
    }    
};

#endif // WILDCARDMATCHING_H
