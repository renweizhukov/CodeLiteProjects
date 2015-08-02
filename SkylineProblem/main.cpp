#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

bool CompareEdges(const pair<int, int> edge1, const pair<int, int> edge2)
{
    if (edge1.first != edge2.first)
    {
        // If two edges are at different x positions, the edge with smaller 
        // x will be "smaller".
        return (edge1.first < edge2.first);
    }
    else
    {
        // (edge1.first == edge2.first):
        // If two edges are at the same x position, then 
        // (1) the higher edge will be "smaller" when both are left edges;
        // (2) the lower edge will be "smaller" when both are right edges.
        // Note that the height of a left edge is positive while the height 
        // of a right edge is negative.
        return (edge1.second > edge2.second);
    }
}

class Solution 
{
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) 
    {
        // Separate the left edges from the right edges.
        // Time complexity O(n).
        vector<pair<int, int>> leftEdges;
        vector<pair<int, int>> rightEdges;
        for (auto& bldg : buildings)
        {
            leftEdges.push_back(make_pair(bldg[0], bldg[2]));
            // The height of a right edge is set to negative.
            rightEdges.push_back(make_pair(bldg[1], -bldg[2]));
        }
        
        // The left edges are already sorted based on the x position 
        // Li. If two left edges are at the same x position, we want 
        // to move the higher left edge before the lower left edge.
        // Time complexity O(n*log(n)).
        auto itLeftEdge = leftEdges.begin();
        while(itLeftEdge != leftEdges.end())
        {
            auto itTmp = itLeftEdge++;
            while ((itLeftEdge != leftEdges.end()) && 
                    (itLeftEdge->first == itTmp->first))
            {
                itLeftEdge++;
            }
            
            sort(itTmp, itLeftEdge, CompareEdges);
        }
        
        // Sort the right edges based on the x position Ri and the 
        // height Hi. If two right edges are at the same x position, 
        // we want to put the lower right edge before the higher 
        // right edge.
        // Time complexity O(n*log(n)).
        sort(rightEdges.begin(), rightEdges.end(), CompareEdges);
        
        // Process the leftmost edge which can be either left or right 
        // to generate the key points. If one left edge is at the same 
        // x position as one right edge, the left edge is processed 
        // before the rigth edge. Note that the first edge to be 
        // processed must be left and the last edge to be processed 
        // must be right.
        // Time complexity O(n*log(n)).
        vector<pair<int, int>> keyPoints;
        // The index of next left edge to be processed.
        int leftEdgeIndex = 0;
        // The index of next right edge to be processed.
        int rightEdgeIndex = 0;
        // The height of current horizontal line segment before 
        // processing next edge. Its initial value is 0.
        int currHeight = 0;
        pair<int, int> currEdge;
        // A multiset (i.e., a BST with possible duplicate values) 
        // contain the heights of all the left edges which haven't been 
        // paired with their right edges.
        multiset<int> unpairedLeftEdgeHeights;
        while (rightEdgeIndex < rightEdges.size())
        {
            
            // Select the leftmost edge.
            if ((leftEdgeIndex < leftEdges.size()) && 
                (leftEdges[leftEdgeIndex].first <= rightEdges[rightEdgeIndex].first))
            {
                currEdge = leftEdges[leftEdgeIndex];
                leftEdgeIndex++;
            }
            else
            {
                currEdge = rightEdges[rightEdgeIndex];
                rightEdgeIndex++;
            }
            
            if (currEdge.second > 0)
            {
                // This is a left edge.
                if (currEdge.second > currHeight)
                {
                    keyPoints.push_back(currEdge);
                    currHeight = currEdge.second;
                }
                
                unpairedLeftEdgeHeights.insert(currEdge.second);
            }
            else
            {
                // This is a right edge.
                
                // Delete the left edge which matches this right edge.
                auto itDeleteLeftEdgeHeight = 
                    unpairedLeftEdgeHeights.find(-(currEdge.second));
                unpairedLeftEdgeHeights.erase(itDeleteLeftEdgeHeight);
                
                auto itCurrentHeight = 
                    unpairedLeftEdgeHeights.find(currHeight);
                if (itCurrentHeight == unpairedLeftEdgeHeights.end())
                {
                    // All the left edges which "establish" the current 
                    // height have been deleted, so reduce the height.
                    if (unpairedLeftEdgeHeights.empty())
                    {
                        currHeight = 0;
                    }
                    else
                    {
                        currHeight = *(unpairedLeftEdgeHeights.rbegin());
                    }
                    
                    keyPoints.push_back(make_pair(currEdge.first, currHeight));
                }
            }
        }
        
        return keyPoints;
    }
};

int main()
{
	vector<vector<int>> buildings =  // {{0, 1, 3}};
        {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    Solution sol;
    
    vector<pair<int, int>> keyPoints = sol.getSkyline(buildings);
    cout << "The key points are as below" << endl;
    for (auto& kP : keyPoints)
    {
        cout << "x Position: " << kP.first << "\t" << "Height: " << kP.second << endl;
    }
    
	return 0;
}
