#ifndef SUGGESTEDMOVIETITLES_H
#define SUGGESTEDMOVIETITLES_H

#include <vector>
#include <string>
#include <queue>

using namespace std;

class SuggestedMovieTitles
{
    struct MovieNode
    {
        char ch;
        list<MovieNode*> children;
    };
    
    struct MovieNodeWithString
    {
        MovieNode* pNode;
        string str;
        MovieNodeWithString(MovieNode *p, string s) :
            pNode(p),
            str(s)
        {
            
        }
    };
    
    vector<string> m_allMovieTitles;
    MovieNode *m_pMovieTitlesRoot;
    
public:
    SuggestedMovieTitles()
    {
        
    }
    
    ~SuggestedMovieTitles()
    {
        
    };

    vector<string> GetSuggestedMovieTitles(string& str, vector<string>& preSuggestedMovieTitles)
    {
        if (preSuggestedMovieTitles.empty())
        {
            preSuggestedMovieTitles = m_allMovieTitles;
        }

        vector<string> suggestedMovieTitles;
        int n = str.length();
        if (n == 0)
        {
            return suggestedMovieTitles;
        }
        
        for (auto& movieTitle : preSuggestedMovieTitles)
        {
            if (movieTitle.length() >= n)
            {
                if (movieTitle[n - 1] == str[n - 1])
                {
                    suggestedMovieTitles.push_back(movieTitle);
                }
            }
        }
        
        return suggestedMovieTitles;
    }
    
    vector<string> GetSuggestedMovieTitles(string& str)
    {
        vector<string> suggestedMovieTitles;
        
        // Find the root of the subtree which contains all the suggested movie titles.
        MovieNode *pSubTree = m_pMovieTitlesRoot;
        for (int i = 0; i < str.length(); i++)
        {
            auto it = pSubTree->children.begin();
            for (it != pSubTree->children.end())
            {
                if (str[i] == (*it)->ch)
                {
                    pSubTree = *it;
                    break;
                }
                it++;
            }
            
            if (it == pSubTree->children.end())
            {
                pSubTree = m_pMovieTitlesRoot;
                break;
            }
        }
        
        // Add all the movie titles below pSubTree.
        if (pSubTree != m_pMovieTitlesRoot)
        {
            queue<MovieNodeWithString> searchQueue;
            searchQueue.push(MovieNodeWithString(pSubTree, str));
            
            while (!searchQueue.empty())
            {
                MovieNodeWithString tmpNodeWithString = searchQueue.front();
                searchQueue.pop();
                
                if (tmpNodeWithString.pNode->children.empty())
                {
                    suggestedMovieTitles.push_back(tmpNodeWithString.str);
                }
                else
                {
                    for (auto& child : tmpNodeWithString.pNode->children)
                    {
                        searchQueue.push(MovieNodeWithString(child, tmpNodeWithString.str + child->ch));
                    }
                }
            }
        }
        
        return suggestedMovieTitles;
    }
};

#endif // SUGGESTEDMOVIETITLES_H
