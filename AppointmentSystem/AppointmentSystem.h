#ifndef APPOINTMENTSYSTEM_H
#define APPOINTMENTSYSTEM_H

#include <list>

using namespace std;

class AppointmentSystem
{
    list<pair<int, int>> m_freeList;
    
public:
    AppointmentSystem()
    {
        m_freeList.push_back(pair<int, int>(0, 2400));
    }
    
    ~AppointmentSystem()
    {
        
    }
    
    bool Reserve(int start, int end)
    {
        auto it = m_freeList.begin();
        while (it != m_freeList.end())
        {
            if (start < it->first)
            {
                return false;
            }
            
            if ((start >= it->first) && (end <= it->second))
            {
                if (start > it->first)
                {
                    m_freeList.insert(it, pair<int, int>(it->first, start));
                }
                
                int tmpEnd = it->second;
                it = m_freeList.erase(it);
                
                if (end < tmpEnd)
                {
                    m_freeList.insert(it, pair<int, int>(end, tmpEnd));
                }
                
                return true;
            }
            else
            {
                it++;
            }
        }
        
        return false;
    }
    
    bool IsAvailable(int start, int end)
    {
        for (auto& f : m_freeList)
        {
            if (start < f.first)
            {
                return false;
            }
            
            if ((start >= f.first) && (end <= f.second))
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool Release(int start, int end)
    {
        auto it = m_freeList.begin();
        while (it != m_freeList.end())
        {
            if (start <= it->first)
            {
                break;
            }
            else
            {
                it++;
            }
        }
        
        it = m_freeList.insert(it, pair<int, int>(start, end));
        if (it != m_freeList.begin())
        {
            auto itPrev = it;
            itPrev--;
            
            if (itPrev->second >= it->first)
            {
                it->first = itPrev->first;
                m_freeList.erase(itPrev);
            }
        }
        
        if (it != m_freeList.end())
        {
            auto itNext = it;
            itNext++;
            
            while ((itNext != m_freeList.end()) && (itNext->first <= it->second))
            {
                it->second = max(it->second, itNext->second);
                itNext = m_freeList.erase(itNext);
            }
        }
        
        return true;
    }
};

#endif // APPOINTMENTSYSTEM_H