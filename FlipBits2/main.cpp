#include <iostream>
using namespace std;

int main()
{
    // Read the length of the bit array.
	int N = 0;
    cin >> N;
    cout << "The number of bits is " << N << "." << endl;
    
    // Ignore '\n' after N.
    cin.clear();
    cin.ignore(10000, '\n');
    
    // Read the elements of the bit array one by one and 
    // calculate the maximum subarray sum of diff0To1 at 
    // the same time.
    int bitVal = -1;
    int cnt1Bits = 0;
    int maxSum = 0;
    int tempSum = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> bitVal;
        // Increase cnt1Bits by 1 if the current bit is '1'.
        if (bitVal == 1)
        {
            cnt1Bits++;
        }
    
        // Set bitVal to count of '1' bits minus count of '0' bits. It should be 
        // either 1 or -1.
        bitVal = 1 - 2*bitVal;
        if (i == 0)
        {
            // Set the initial values for maxSum and tempSum.
            maxSum = bitVal;
            tempSum = (bitVal > 0) ? bitVal : 0;
        }
        else
        {
            tempSum += bitVal;
            if (tempSum > maxSum)
            {
                maxSum = tempSum;
            }
            
            // If tempSum is negative, reset it to 0. Since a negative 
            // number won't contribute to the maximum sum with subsequent 
            // numbers.
            if (tempSum < 0)
            {
                tempSum = 0;
            }
        }
        
        // Ignore the following space for the first 
        // (N - 1) bits.
        if (i < N - 1)
        {
            cin.clear();
            cin.ignore(1, ' ');
        }
    }
    
    // If all the bits are '1', maxSum will be -1. In this case, flipping will 
    // only decrease the count of '1'-bits. If at least one bit is 0, maxSum
    // must be greater than 0 since we can at least flip one '0'-bit to increase
    // the count of '1'-bits by 1.
    if (maxSum > 0)
    {
        cnt1Bits += maxSum;
    }
    
    cout << "The maximum count of '1'-bits by flipping a subarray is " << cnt1Bits 
        << "." << endl;
    
	return 0;
}