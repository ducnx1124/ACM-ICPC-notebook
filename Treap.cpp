#include <bits/stdc++.h>
using namespace std;

struct Treap
{
    #define S(t) (t ? t->Sum : 0)
    #define W(t) (t ? t->Weight : 0)
 
    struct Node
    {
        long Weight, Sum, Value, AssignValue, IncStart, IncRate;
        int Priority;
        Node *l, *r;
 
        Node (long x)
        {
            Value = x;
 
            Priority = (rand() << 15) | rand();
            l = r = NULL;
            IncRate = IncStart = 0;
            AssignValue = -1;
            Weight = 1;
            Sum = 0;
        }
    } *root;
 
    void PushQuery (Node *t)
    {
        Node *l = t->l, *r = t->r;
 
        if (t->AssignValue > -1)
        {
            if (l)
            {
                l->IncRate = l->IncStart = 0;
                l->Value = l->AssignValue = t->AssignValue;
                l->Sum = l->Value * l->Weight;
            }
 
            if (r)
            {
                r->IncRate = r->IncStart = 0;
                r->Value = r->AssignValue = t->AssignValue;
                r->Sum = r->Value * r->Weight;
            }
 
            t->AssignValue = -1;
        }
 
        if (t->IncStart || t->IncRate)
        {
            if (l)
            {
                l->Sum += t->IncStart * l->Weight;
                l->Sum += t->IncRate * ((l->Weight * (l->Weight + 1)) >> 1);
                l->Value += t->IncStart + t->IncRate * (W(l->l) + 1);
 
                l->IncStart += t->IncStart;
                l->IncRate += t->IncRate;
            }
 
            if (r)
            {
                long k = t->IncStart + t->IncRate * (W(l) + 1);
                r->Sum += k * r->Weight;
                r->Sum += t->IncRate * ((r->Weight * (r->Weight + 1)) >> 1);
                r->Value += k + t->IncRate * (W(r->l) + 1);
 
                r->IncStart += k;
                r->IncRate += t->IncRate;
            }
 
            t->IncRate = t->IncStart = 0;
        }
    }
 
    void PropertyUpdate (Node *t)
    {
        if (t)
        {
            t->Weight = W(t->l) + W(t->r) + 1;
            t->Sum = S(t->l) + S(t->r) + t->Value;
        }
    }
 
    void Split (Node *t, Node *&l, Node *&r, int p)
    {
        if (!t) l = r = NULL;
        else
        {
            PushQuery(t);
 
            if (p <= W(t->l))
            {
                r = t;
                Split(t->l, l, r->l, p);
            } else
            {
                l = t;
                Split(t->r, l->r, r, p - W(t->l) - 1);
            }
        }
 
        PropertyUpdate(t);
    }
 
    void Merge (Node *&t, Node *l, Node *r)
    {
        if (l) PushQuery(l);
        if (r) PushQuery(r);
 
        if (!l) t = r;
        else
        if (!r) t = l;
        else
        if (l->Priority > r->Priority)
        {
            t = l;
            Merge(t->r, l->r, r);
        } else
        {
            t = r;
            Merge(t->l, l, r->l);
        }
 
        PropertyUpdate(t);
    }
 
    void Assign (int l,int r,long value)
    {
        Node *t1, *t = root, *t2;
        Split(t, t, t2, r);
        Split(t, t1, t, l - 1);
 
        t->IncRate = t->IncStart = 0;
        t->AssignValue = t->Value = value;
        t->Sum = value * t->Weight;
 
        Merge(t, t1, t);
        Merge(t, t, t2);
        root = t;
    }
 
    void IncRange (int l,int r,long IncRate)
    {
        Node *t1, *t = root, *t2;
        Split(t, t, t2, r);
        Split(t, t1, t, l - 1);
 
        t->IncRate += IncRate;
        t->Sum += IncRate * ((t->Weight * (t->Weight + 1)) >> 1);
        t->Value += IncRate * (W(t->l) + 1);
 
        Merge(t, t1, t);
        Merge(t, t, t2);
        root = t;
    }
 
    void insert (int p,int v)
    {
        Node *t1, *t2;
        Split(root, t1, t2, p - 1);
        Merge(t1, t1, new Node(v));
        Merge(root, t1, t2);
    }
 
    long GetSum (int l,int r)
    {
        Node *t1, *t = root, *t2;
        Split(t, t, t2, r);
        Split(t, t1, t, l - 1);
 
        long s = t->Sum;
        Merge(t, t1, t);
        Merge(t, t, t2);
        root = t;
 
        return s;
    }
 
    #undef S
    #undef W
};