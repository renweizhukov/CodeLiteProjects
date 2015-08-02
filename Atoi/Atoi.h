class Solution {
    bool IsDigit(const char& ch)
    {
        return ('0' <= ch) && (ch <= '9');    
    }
    
public:
    int atoi(const char *str) {
        int ret = 0;
        if (str == nullptr) 
        {
            return ret;
        }
        
        int start = -1;
        int sign = 1;
        for (int index = 0; str[index] != '\0'; index++)
        {
            const char ch = str[index];
            if (ch == '+')
            {
                start = index + 1;
                break;
            }
            else if (ch == '-')
            {
                start = index + 1;
                sign = -1;
                break;
            }
            else if (IsDigit(ch))
            {
                start = index;
                break;
            }
        }
        
        if (start != -1)
        {
            for (int index = start; IsDigit(str[index]) && (str[index] != '\0'); index++)
            {
                if ((ret > LONG_MAX/10) || (ret < LONG_MIN/10))
                {
                    ret = 0;
                    break;
                }
                ret = 10*ret;
                
                int digit = static_cast<int>(str[index] - '0');
                if ((digit != 0) && 
                    ((ret > LONG_MAX - digit) || (ret < LONG_MIN + digit)))
                {
                    ret = 0;
                    break;
                }
                ret += (sign*digit);
            }
        }
        
        return ret;
    }
};