#include <bits/stdc++.h>
using namespace std;
#define long int64_t
 
struct BufferedReader
{
    char Buf[1 << 16 | 1];
    int cur;
 
    void FillBuffer ()
    {
        Buf[fread(Buf, 1, 1 << 16, stdin)] = 0;
        cur = 0;
    }
 
    BufferedReader ()
    {
        //freopen("test.inp","r",stdin);
        FillBuffer();
    }
 
    void nextchar ()
    {
        ++cur;
        if (!Buf[cur]) FillBuffer();
    }
 
    BufferedReader& operator >> (int &t)
    {
        t = 0;
        while (!isdigit(Buf[cur])) nextchar();
        while (isdigit(Buf[cur])) t = t * 10 + Buf[cur] - '0', nextchar();
 
        return *this;
    }
};