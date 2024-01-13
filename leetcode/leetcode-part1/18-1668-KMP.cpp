#include <iostream>
using namespace std;
#include <string>

class Solution {
public:
    int* getNext(string word)
    {
        int wordLen=word.size();
        int *next = new int[wordLen];
        next[0]=-1;
        int i=0,k=-1;
        while(i<wordLen-1)
        {
            if(k==-1 || word[i]==word[k])
            {
                i++;
                k++;
                next[i]=k;
            }
            else
            {
                k=next[k];
            }
        }
        return next;
    }
    int KMP(string sequence, string word)
    {
        int i=0,j=0;
        int slen=sequence.size(),wlen=word.size();
        int* next = getNext(word);
        while(i<slen && j<wlen)
        {
            if(j==-1 || sequence[i]==word[j])
            {
                ++i;
                ++j;
            }
            else
            {
                j=next[j];
            }
        }
        if(j==wlen)
            return i-j;
        return -1;
    }
    int maxRepeating(string sequence, string word) 
    {
        int count=0;
        string words=word;
        while(KMP(sequence,words)!=-1)
        {
            count++;
            words+=word;
        }
        return count;
    }
};