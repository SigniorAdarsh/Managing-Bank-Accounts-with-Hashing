#include "Chaining.h"
using namespace std;
int rri = 0;
int power(long long x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res % p;
}
Chaining::Chaining()
{
    size_t sizz = 10000;
    bankStorage2d.resize(sizz, {});
}
void Chaining::createAccount(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    Account newacc;
    newacc.id = id;
    newacc.balance = count;
    bankStorage2d[myval].push_back(newacc);
    rri++;
}
void chotumerge(vector<int> &dummy, int begin, int midd, int ending)
{
    vector<int> temp;
    int i = begin;
    int j = midd + 1;
    while (i <= midd && j <= ending)
    {

        if (dummy[i] <= dummy[j])
        {
            temp.push_back(dummy[i]);
            i++;
        }
        else
        {
            temp.push_back(dummy[j]);
            j++;
        }
    }
    while (i <= midd)
    {
        temp.push_back(dummy[i]);
        i++;
    }
    while (j <= ending)
    {
        temp.push_back(dummy[j]);
        j++;
    }
    for (int i = begin; i <= ending; i++)
        dummy[i] = temp[i - begin];
}
void mergesme(vector<int> &dummy, int begin, int ending)
{
    if (begin < ending)
    {
        int midd = begin + (ending - begin) / 2;
        mergesme(dummy, begin, midd);
        mergesme(dummy, midd + 1, ending);
        chotumerge(dummy, begin, midd, ending);
    }
}
std::vector<int> Chaining::getTopK(int k)
{
    // IMPLEMENT YOUR CODE HERE
    vector<int> dummy;
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            dummy.push_back(bankStorage2d[i][j].balance);
        }
    }
    mergesme(dummy, 0, dummy.size() - 1);
    if (k <= rri)
    {
        vector<int> mummy(k);
        int sup = k;
        int k2 = k;
        while (k2 > 0)
        {
            mummy[sup - k2] = dummy[(dummy.size()) - (sup - k2) - 1];
            k2--;
        }
        return mummy;
    }
    else
    {
        vector<int> mummy(dummy.size());
        int sup = rri;
        int k = rri;
        while (k > 0)
        {
            mummy[sup - k] = dummy[dummy.size() - (sup - k) - 1];
            k--;
        }
        return mummy;
    } // Placeholder return value
}

int Chaining::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    if (bankStorage2d[myval].size() == 0)
        return -1;
    else
    {
        for (int i = 0; i < bankStorage2d[myval].size(); i++)
        {
            if (bankStorage2d[myval][i].id == id)
                return bankStorage2d[myval][i].balance;
        }
        return -1;
    } // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count)
{
    int myval = hash(id);
    bool lov = false;
    if (bankStorage2d[myval].size() == 0)
    {
        createAccount(id, count);
    }
    else
    {
        for (int i = 0; i < bankStorage2d[myval].size(); i++)
        {
            if (bankStorage2d[myval][i].id == id)
            {
                bankStorage2d[myval][i].balance += count;
                lov = true;
                break;
            }
        }
        if (lov == false)
        {
            createAccount(id, count);
        }
    }
    // IMPLEMENT YOUR CODE HERE
}

bool Chaining::doesExist(std::string id)
{
    int myval = hash(id);
    if (bankStorage2d[myval].size() == 0)
        return false;
    else
    {
        for (int i = 0; i < bankStorage2d[myval].size(); i++)
        {
            if (bankStorage2d[myval][i].id == id)
                return true;
        }
        return false;
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id)
{
    int myval = hash(id);
    if (bankStorage2d[myval].size() == 0)
        return false;
    else
    {
        for (int i = 0; i < bankStorage2d[myval].size(); i++)
        {
            if (bankStorage2d[myval][i].id == id)
            {
                bankStorage2d[myval].erase(bankStorage2d[myval].begin() + i);
                rri--;
                return true;
            }
        }
        return false;
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int Chaining::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return rri; // Placeholder return value
}

int Chaining::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int loserhash = 0;
    int modder = 10000;
    for (int i = 0; i < id.length(); i++)
    {
        int x = static_cast<int>(id[i]);
        loserhash = (loserhash + power(x, i + 1, modder)) % modder;
    }
    return loserhash % modder; // Placeholder return value
}