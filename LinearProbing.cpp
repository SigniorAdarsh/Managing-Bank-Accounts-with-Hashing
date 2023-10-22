#include "LinearProbing.h"
using namespace std;
int rizz;
int power2(long long x, unsigned int y, int p)
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
int LinearProbing::newhash(string id, vector<Account> &bankStorage1d)
{
    int loserhash = 0;
    int modder = 140057;
    loserhash=hash(id);
    while (bankStorage1d[loserhash].id != "VOID")
    {
        loserhash = (loserhash + 1) % modder;
    }
    return loserhash;
}
LinearProbing::LinearProbing()
{
    size_t sizz = 140057;
    bankStorage1d.resize(sizz);
    for (int i = 0; i < sizz; i++)
    {
        bankStorage1d[i].id = "VOID";
        bankStorage1d[i].balance = -1;
    }
    rizz = 0;
}
void LinearProbing::createAccount(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = newhash(id, bankStorage1d);
    Account newacc;
    newacc.id = id;
    newacc.balance = count;
    bankStorage1d[myval] = newacc;
    rizz++;
}
void chotumerge3(vector<int> &dummy, int begin, int midd, int ending)
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
void mergesme3(vector<int> &dummy, int begin, int ending)
{
    if (begin < ending)
    {
        int midd = begin + (ending - begin) / 2;
        mergesme3(dummy, begin, midd);
        mergesme3(dummy, midd + 1, ending);
        chotumerge3(dummy, begin, midd, ending);
    }
}
std::vector<int> LinearProbing::getTopK(int k)
{
    // IMPLEMENT YOUR CODE HERE
    vector<int> dummy;
    for (int i = 0; i < 140057; i++)
    {
        if (bankStorage1d[i].id != "VOID")
        {
            dummy.push_back(bankStorage1d[i].balance);
        }
    }
    mergesme3(dummy, 0, dummy.size() - 1);
    if (rizz >= k)
    {
        vector<int> mummy(k);
        int sup = k;
        while (k > 0)
        {
            mummy[sup - k] = dummy[dummy.size() - (sup - k) - 1];
            k--;
        }
        return mummy;
    }
    else
    {
        vector<int> mummy(dummy.size());
        int sup = rizz;
        int k = rizz;
        while (k > 0)
        {
            mummy[sup - k] = dummy[dummy.size() - (sup - k) - 1];
            k--;
        }
        return mummy;
    } // Placeholder return value
}

int LinearProbing::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    int rm = myval;
    int modder = 140057;
    while (bankStorage1d[myval].id != "VOID" || bankStorage1d[myval].balance != -1)
    {
        if (bankStorage1d[myval].id == id)
            return bankStorage1d[myval].balance;
        else
            myval = (myval + 1) % modder;
        if (myval == rm)
            break;
    }
    return -1;
    // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count)
{
    int myval = hash(id);
    int rm = myval;
    int modder = 140057;
    while (bankStorage1d[myval].id != "VOID" || bankStorage1d[myval].balance != -1)
    {
        if (bankStorage1d[myval].id == id)
        {
            bankStorage1d[myval].balance += count;
            return;
        }
        else
            myval = (myval + 1) % modder;
        if (myval == rm)
            break;
    }
    Account newacc;
    newacc.id = id;
    newacc.balance = count;
    bankStorage1d[myval] = newacc;
    rizz++;

    // IMPLEMENT YOUR CODE HERE
}

bool LinearProbing::doesExist(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    int rm = myval;
    int modder = 140057;
    while (bankStorage1d[myval].id != "VOID" || bankStorage1d[myval].balance != -1)
    {
        if (bankStorage1d[myval].id == id)
            return true;
        else
            myval = (myval + 1) % modder;
        if (myval == rm)
            break;
    }
    return false;
    // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    int rm = myval;
    int modder = 140057;
    while (bankStorage1d[myval].id != "VOID" || bankStorage1d[myval].balance != -1)
    {
        if (bankStorage1d[myval].id == id)
        {
            bankStorage1d[myval].id = "VOID";
            bankStorage1d[myval].balance = -2;
            rizz--;
            return true;
        }
        else
            myval = (myval + 1) % modder;
        if (myval == rm)
            break;
    }
    return false; // Placeholder return value
}
int LinearProbing::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return rizz;
    // Placeholder return value
}

int LinearProbing::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int loserhash = 0;
    int modder = 140057;
    for (int i = 0; i < id.length(); i++)
    {
        int x = static_cast<int>(id[i]);
        loserhash = (loserhash + power2(x, i + 1, modder)) % modder;
    }
    return loserhash % modder;
    // Placeholder return value
}