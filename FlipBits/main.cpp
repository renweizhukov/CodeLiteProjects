#include <iostream>
#include <string>
#include <vector>
using namespace std;

// This function finds the contiguous subarray within an array 
// (containing at least one number) which has the largest sum.
// Here we assume that N >= 1 where N is the size of the input array.
int GetMaxSubArraySum(vector<int> &A, int N)
{
    int maxSum = A[0];
    int tempSum = (A[0] >= 0) ? A[0] : 0;
    
    for (int i = 1; i < N; i++)
    {
        tempSum += A[i];
        if (tempSum > maxSum)
        {
            maxSum = tempSum;
        }
        
        // If tempSum is negative, reset it to 0. Since a negative 
        // number won't contribute to the maximum sum with subsequent 
        // numbers.
        if (tempSum < 0)
        {
            tempSum = 0;
        }
    }
    
    return maxSum;
}

int main()
{
    // Read the length of the bit array.
	int N = 0;
    cin >> N;
    cout << "The number of bits is " << N << "." << endl;
    
    // Ignore '\n' after N.
    cin.clear();
    cin.ignore(10000, '\n');
    
    // Read the elements of the bit array one by one.
    vector<int> bitArray(N);
    for (int i = 0; i < N; i++)
    {
        cin >> bitArray[i];
        // Ignore the following space for the first 
        // (N - 1) bits.
        if (i < N - 1)
        {
            cin.clear();
            cin.ignore(1, ' ');
        }
    }
    cout << "The input bit array is: ";
    for (int i = 0; i < N; i++)
    {
        cout << bitArray[i] << ' ';
    }
    cout << "." << endl;
    
    // Diff0To1[i] = count of '0'-bits - count of '1'-bits at index i.
    // It should be either 1 or -1.
    vector<int> diff0To1(N);
    int cnt1Bits = 0; // count of '1'-bits without any flipping.
    for (int i = 0; i < N; i++)
    {
        if (bitArray[i] == 0)
        {
            diff0To1[i] = 1;
        }
        else
        {
            diff0To1[i] = -1;
            cnt1Bits++;
        }
    }
    
    // If we flip the bits between L and R (inclusive), we will increase 
    // the count of '1'-bits by diff0To1[L] + diff0To1[L + 1] + ... + diff0To1[R].
    // Thus, to get the maximum count of bits increased by flipping, it is 
    // equivalent to find the contiguous subarray within diff0To1 which 
    // has the largest sum.
    int maxCntBitsAddedByFlip = GetMaxSubArraySum(diff0To1, N);
    // If all the bits are '1', maxCntBitsAddedByFlip will be -1. In this case, 
    // flipping will only decrease the count of '1'-bits. If at least one bit 
    // is 0, maxCntBitsAddedByFlip must be greater than 0 since we can at least 
    // flip one '0'-bit to increase the count of '1'-bits by 1.
    if (maxCntBitsAddedByFlip > 0)
    {
        cnt1Bits += maxCntBitsAddedByFlip;
    }
    
    cout << "The maximum count of '1'-bits by flipping a subarray is " << cnt1Bits 
        << "." << endl;
    
	return 0;
}
