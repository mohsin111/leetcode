#include <deque>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

// If duplicates in T are treated as one
//O(ns + nt) time and O(ns + nt) space
string minWindow0(string S, string T) {
    unordered_map<char, int> counts;
    unordered_set<char> tchars;
    deque<int> q;

    for (int i = 0; i < T.size(); ++i)
    {
        tchars.insert(T[i]);
    }
    if (tchars.empty())
        return "";
    
    int i = 0;

    int minStart = 0;
    int minSize = -1;

    while(1) {

        for (;i < S.size(); ++i) 
        {
            if (counts.find(S[i]) != counts.end()) {
                q.push_back(i); 
                counts[S[i]]++;
            }
             else if (tchars.find(S[i]) != tchars.end()) {
                q.push_back(i);
                counts[S[i]] = 1;
            }

            if (counts.size() == tchars.size())
                break;
        }
        
        if (i == S.size())
            break;

        ++i;
        while(1) {

            int curStart = q.front();
            int curEnd = q.back();
            q.pop_front();
            counts[S[curStart]]--;
            if (counts[S[curStart]] == 0) {
                int curSize = curEnd - curStart + 1;
                if ((minSize == -1) || (curSize < minSize)) {
                    minSize = curSize;
                    minStart = curStart;
                }
                counts.erase(S[curStart]);
                break;
            }
        }
        
    }
    
    return (minSize == -1) ? "" : S.substr(minStart, minSize);
}


string minWindow(string S, string T) {
    unordered_map<char, int> counts;
    unordered_map<char, int> tchars;
    deque<int> q;

    for (int i = 0; i < T.size(); ++i)
    {
        if (tchars.find(T[i]) != tchars.end())
            tchars[T[i]]++;
        else
            tchars[T[i]] = 1;
    }

    if (tchars.empty())
        return "";
    
    int i = 0;

    int minStart = 0;
    int minSize = -1;
    
    int countSize = 0;

    while(1) {

        for (;i < S.size(); ++i) 
        {
            if (counts.find(S[i]) != counts.end()) {
                if (counts[S[i]] < tchars[S[i]])
                    countSize++;

                q.push_back(i); 
                counts[S[i]]++;
            } else if (tchars.find(S[i]) != tchars.end()) {
                countSize++;
                q.push_back(i);
                counts[S[i]] = 1;
            }
            
            if (countSize == T.size())
                break;
        }
        
        if (i++ == S.size())
            break;

        while(1) {

            int curStart = q.front();
            int curEnd = q.back();
            q.pop_front();
            counts[S[curStart]]--;
            if (counts[S[curStart]] < tchars[S[curStart]])
                countSize--;

            if (countSize < T.size()) {
                int curSize = curEnd - curStart + 1;
                if ((minSize == -1) || (curSize < minSize)) {
                    minSize = curSize;
                    minStart = curStart;
                }
                break;
            }
        }
        
    }
    
    return (minSize == -1) ? "" : S.substr(minStart, minSize);
}


int main(int argc, char** argv)
{
    string S = "ADOBECODEBANC";
    string T = "ABC";
    cout << minWindow(S, T) << endl;
    return 0;
}