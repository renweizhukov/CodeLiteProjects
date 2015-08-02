#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TrieNode 
{
    char m_ch;  // character stored in this TrieNode
    TrieNode* m_children[27]; // array of children TrieNodes
    
public:
    // Initialize your data structure here.
    TrieNode() 
    {
        m_ch = 0;
        for (int i = 0; i < 27; i++)
        {
            m_children[i] = nullptr;
        }
    }
    
    TrieNode(char ch) : 
        m_ch(ch)
    {
        for (int i = 0; i < 27; i++)
        {
            m_children[i] = nullptr;
        }
    }
    
    // Get the stored character.
    char GetChar()
    {
        return m_ch;
    }
    
    // Set the stored character.
    void SetChar(char ch)
    {
        m_ch = ch;
    }
    
    // Add a child TrieNode to its children list.
    void AddChild(TrieNode* child)
    {
        if (child->GetChar() != 0)
        {
            m_children[child->GetChar() - 'a'] = child;
        }
        else
        {
            m_children[26] = child;
        }
    }
    
    // Find the child TrieNode based on next character.
    TrieNode* FindChild(char ch)
    {
        if (ch != 0)
        {
            return m_children[ch - 'a'];
        }
        else
        {
            return m_children[26];
        }
    }
};

class Trie 
{
public:
    Trie() 
    {
        m_root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string s) 
    {
        TrieNode *prev = nullptr;
        TrieNode *curr = m_root;
        // We check the characters of s one by one. Note that 
        // we also add the NULL terminator to the Trie which 
        // indicates the end of a word.
        for (int i = 0; i <= s.length(); i++)
        {
            prev = curr;
            curr = prev->FindChild(s[i]);
            
            // Can't find a TrieNode with the character s[i], 
            // so create a new one and add it to the children 
            // list of prev.
            if (curr == nullptr)
            {
                curr = new TrieNode(s[i]);
                prev->AddChild(curr);
            }
        }
    }

    // Returns the root TrieNode.
    TrieNode* GetRoot() 
    {
        return m_root;
    }

private:
    TrieNode* m_root;
};

class Solution 
{
    void findWordsStartFromOneCell(
        vector<vector<char>>& board,
        int m,
        int n,
        int i,
        int j,
        TrieNode* currNode,
        string& word,
        vector<string>& foundWords)
    {
        TrieNode *childNode = currNode->FindChild(board[i][j]);
        if (childNode == nullptr)
        {
            return;
        }
        
        word.push_back(board[i][j]);
        board[i][j] = 'X';
        TrieNode *wordEndNode = childNode->FindChild(0);
        if ((wordEndNode != nullptr) && (wordEndNode->GetChar() != 'X'))
        {
            foundWords.push_back(word);
            wordEndNode->SetChar('X');
        }
        
        if ((i > 0) && (board[i - 1][j] != 'X'))
        {
            findWordsStartFromOneCell(
                board,
                m,
                n,
                i - 1,
                j,
                childNode,
                word,
                foundWords);
        }
        
        if ((i < m - 1) && (board[i + 1][j] != 'X'))
        {
            findWordsStartFromOneCell(
                board,
                m,
                n,
                i + 1,
                j,
                childNode,
                word,
                foundWords);
        }
        
        if ((j > 0) && (board[i][j - 1] != 'X'))
        {
            findWordsStartFromOneCell(
                board,
                m,
                n,
                i,
                j - 1,
                childNode,
                word,
                foundWords);            
        }
        
        if ((j < n - 1) && (board[i][j + 1] != 'X'))
        {
            findWordsStartFromOneCell(
                board,
                m,
                n,
                i,
                j + 1,
                childNode,
                word,
                foundWords);    
        }
        
        board[i][j] = word.back();
        word.pop_back();
    }
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
    {
        // Build the trie based on the input words.
        Trie wordTrie;
        for (auto &w : words)
        {
            wordTrie.insert(w);
        }
        
        vector<string> foundWords;
        int m = board.size();
        if (m == 0)
        {
            return foundWords;
        }
        
        int n = board[0].size();
        if (n == 0)
        {
            return foundWords;
        }
        
        TrieNode* root = wordTrie.GetRoot();
        string word;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                findWordsStartFromOneCell(
                    board,
                    m,
                    n,
                    i,
                    j,
                    root,
                    word,
                    foundWords);
            }
        }
        
        return foundWords;
    }
};

int main()
{
	vector<vector<char>> board({{'a', 'b'},{'a', 'a'}});
    vector<string> words({"aba","baa","bab","aaab","aaa","aaaa","aaba"}); 
    
    Solution sol;
    vector<string> res = sol.findWords(board, words);
    
    for (auto &str: res)
    {
        cout << str << endl;
    }
    
	return 0;
}