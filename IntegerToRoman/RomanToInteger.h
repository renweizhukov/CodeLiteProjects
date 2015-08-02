using namespace std;

class RomanToInteger 
{
    template<int unit> 
    int GetNextNum(int num, string unit10, string unit5, string unit1, string& output)
    {
        int ret = 0;
        
        if (num >= 9*unit)
        {
            output.append(unit1 + unit10);
            ret = num - 9*unit;
        }
        else if (num >= 5*unit)
        {
            output.append(unit5);
            ret = num - 5*unit;
        }
        else if (num >= 4*unit)
        {
            output.append(unit1 + unit5);
            ret = num - 4*unit;
        }
        else
        {
            output.append(num/unit, unit1[0]);
            ret = num % unit; 
        }
        
        return ret;
    }
    
public:
    string intToRoman(int num) 
    {
        string roman;
        
        while (num > 0)
        {
            if (num >= 1000)
            {
                roman.append(num/1000, 'M');
                num %= 1000;
            }
            else if (num >= 100)
            {
                num = GetNextNum<100>(num, "M", "D", "C", roman);
            }
            else if (num >= 10)
            {
                num = GetNextNum<10>(num, "C", "L", "X", roman);
            }
            else
            {
                num = GetNextNum<1>(num, "X", "V", "I", roman);
            }
        }
        
        return roman;
    }
};