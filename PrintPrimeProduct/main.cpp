#include <iostream>

using namespace std;

class Solution
{
public:
    void PrintPrimeProduct(int num)
    {
        if (num < 0)
        {
            // Output "-" for negative numbers.
            cout << "-";
            num = -num;
        }
        
        if (num <= 3)
        {
            cout << num;
            return;
        }
        
        int prevPrime = -1;
        while (num > 1)
        {
            // If we are searching for the first prime factor, we start from 2.
            // Otherwise, we start from the previous prime factor.
            int currPrime = (prevPrime != -1) ? prevPrime : 2;
            for ( ; currPrime <= num; currPrime++)
            {
                // We don't need to verify whether currPrime is indeed a prime 
                // number. Since we are searching from the smallest number, the 
                // first divisor of num has to be a prime number. If it is not, 
                // we should have found a smaller divisor before we reach currPrime.
                if (num%currPrime == 0)
                {
                    if (prevPrime == -1)
                    {
                        // This is the first prime factor.
                        cout << currPrime;
                    }
                    else
                    {
                        // This is a prime factor but not the first one.
                        cout << "*" << currPrime;
                    }
                    
                    prevPrime = currPrime;
                    num /= currPrime;
                    break;
                }
            }
        }
        
        cout << endl;
    }
};

int main()
{
    int num;
	cout << "Please input an integer: ";
    cin >> num;
    cout << endl;
    
    cout << "This integer can be written as the product of prime factors: ";
    Solution sol;
    sol.PrintPrimeProduct(num);
    
	return 0;
}
