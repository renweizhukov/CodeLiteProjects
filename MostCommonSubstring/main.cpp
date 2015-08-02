#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int GetCntMostFrequentSubstring(
    const int N,       // length of str
    const int K,       // minimum length of substring
    const int L,       // maximum length of substring
    const int M,       // maximum count of distinct characters in the substring
    const string &str) // the input string
{
    // substrCntMaps[i] = the hash map from substrings with length K + i to 
    // the count of their occurrences.
    vector<unordered_map<string, int>> substrCntMaps(L - K + 1);
    // charCntMaps[i] = the hash map from distinct characters in substrings 
    // with length K + i to the count of their occurrences.
    vector<unordered_map<char, int>> charCntMaps(L - K + 1);
    
    // Calculate charCntMaps for str.substr(0, K).
    // Time complexity O(K).
    for (int i = 0; i < K; i++)
    {
        auto it = charCntMaps[0].find(str[i]);
        if (it == charCntMaps[0].end())
        {
            // This is a new character which didn't exist in charCntMaps[0].
            charCntMaps[0].insert(make_pair(str[i], 1));
        }
        else
        {
            // Increase the occurrence count of this character which existed 
            // in charCntMaps[0].
            (it->second)++;
        }
    }
    
    // If str.substr(0, K) contains no more than M distinct characters, add it 
    // to substrCntMaps[0].
    // Time complexity O(1).
    string substr = str.substr(0, K);
    if (charCntMaps[0].size() <= M)
    {
        substrCntMaps[0].insert(make_pair(substr, 1));
    }
    
    // Calculate charCntMaps for str.substr(0, subStringLen) where 
    // subStringLen = K + 1,..., L.
    // Time complexity O(L - K).
    for (int subStringLen = K + 1; subStringLen <= L; subStringLen++)
    {
        int mapIndex = subStringLen - K;
        // str.substr(0, subStringLen) = str.substr(0, subStringLen - 1) 
        //                               + str[subStringLen - 1].
        charCntMaps[mapIndex] = charCntMaps[mapIndex - 1];
        auto it = charCntMaps[mapIndex].find(str[subStringLen - 1]);
        if (it == charCntMaps[mapIndex].end())
        {
            charCntMaps[mapIndex].insert(make_pair(str[subStringLen - 1], 1));
        }
        else
        {
            (it->second)++;
        }
        
        // If str.substr(0, subStringLen) contains no more than M distinct characters, 
        // add it to substrCntMaps[mapIndex].
        substr.push_back(str[subStringLen - 1]);
        if (charCntMaps[mapIndex].size() <= M)
        {
            substrCntMaps[mapIndex].insert(make_pair(substr, 1));
        }
    }
    
    // Calculate charCntMaps for str.substr(i, subStringLen) where 
    // subStringLen = K,..., L and i = 1,..., N - subStringLen.
    // Time complexity O((L - K)*N).
    for (int subStringLen = K; subStringLen <= L; subStringLen++)
    {
        int mapIndex = subStringLen - K;
        for (int i = 1; i <= N - subStringLen; i++)
        {
            // Delete the character str[i - 1].
            auto itDelete = charCntMaps[mapIndex].find(str[i - 1]);
            if (itDelete->second > 1)
            {
                (itDelete->second)--;
            }
            else
            {
                charCntMaps[mapIndex].erase(itDelete);
            }
            
            // Add the character str[i + subStringLen - 1].
            auto itNew = charCntMaps[mapIndex].find(str[i + subStringLen - 1]);
            if (itNew == charCntMaps[mapIndex].end())
            {
                charCntMaps[mapIndex].insert(make_pair(str[i + subStringLen - 1], 1));
            }
            else
            {
                (itNew->second)++;
            }
            
            // If str.substr(i, subStringLen) contains no more than M distinct characters, 
            // add it to substrCntMaps[mapIndex].
            if (charCntMaps[mapIndex].size() <= M)
            {
                substr = str.substr(i, subStringLen);
                auto it = substrCntMaps[mapIndex].find(substr);
                if (it == substrCntMaps[mapIndex].end())
                {
                    substrCntMaps[mapIndex].insert(make_pair(substr, 1));
                }
                else
                {
                    (it->second)++;
                }
            }
        }
    }
    
    // Get the number of occurrences of the most frequent substring.
    int maxCnt = 0;
    for (int i = 0; i < substrCntMaps.size(); i++)
    {
        for (auto &substrCnt : substrCntMaps[i])
        {
            if (substrCnt.second > maxCnt)
            {
                maxCnt = substrCnt.second;
            }
        }
    }
    
    return maxCnt;
}

int main()
{
	int N = -1;
    cin >> N;
    cout << "The length of the string is " << N << "." << endl;
    
    int K = -1;
    cin >> K;
    cout << "The minimum length of the substring is " << K << "." << endl;
    
    int L = -1;
    cin >> L;
    cout << "The maximum length of the substring is " << L << "." << endl;
    
    int M = -1;
    cin >> M;
    cout << "The maximum count of distinct characters in the substring is " << M << "." << endl;
    
    cin.clear();
    cin.ignore(10000, '\n');
    
    string str;
    getline(cin, str);
    cout << "The input string is \"" << str << "\"." << endl;
    
    int res = GetCntMostFrequentSubstring(N, K, L, M, str);
    
    cout << "The number of occurrences of the most frequent substring is " << res << "." << endl;
    
	return 0;
}
