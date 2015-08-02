#include <iostream>
#include <climits>

using namespace std;

double pow(double x, int n) 
{
    if (n < 0)
    {
        if (n > LONG_MIN)
        {
            return 1.0/pow(x, -n);
        }
        else
        {
            return 1.0/pow(x, LONG_MAX)/x;
        }
    }
    else if (n == 0)
    {
        return 1.0;
    }
    else
    {
        if (n == 1)
        {
            return x;
        }
        
        double y = pow(x, n/2);
        if (n & 1)
        {
            return y*y*x;
        }
        else
        {
            return y*y;
        }
    }
}

int main()
{
    double x = 0.0;
	cout << "Please input a double x = ";
    cin >> x;
    cout << endl;
    
    int n = 0;
    cout << "Please input an integer n = ";
    cin >> n;
    cout << endl;
    
    double res = pow(x, n);
    cout << "Pow(x, n) = " << res << endl;
    
	return 0;
}
