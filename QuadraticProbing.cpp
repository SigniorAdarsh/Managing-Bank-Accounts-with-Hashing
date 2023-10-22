#include "QuadraticProbing.h"
using namespace std;
int rizzel;
int power3(long long x, unsigned int y, int p)
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
int QuadraticProbing::newhash2(string id, vector<Account> &bankStorage1d)
{
    int loserhash = hash(id);
    int lh = loserhash;
    int modder = 200003;
    int i = 0;
    while (true)
    {
        int x = (lh + power3(i, 2, modder)) % modder;
        if (bankStorage1d[x].balance <0)
        {
            lh = x;
            break;
        }
        else
        {
            i++;
        }
    }
    return lh;
}
QuadraticProbing::QuadraticProbing()
{
    size_t sizz = 200003;
    bankStorage1d.resize(sizz);
    for (int i = 0; i < sizz; i++)
    {
        bankStorage1d[i].id = "VOID";
        bankStorage1d[i].balance = -1;
    }
    rizzel = 0;
}
void QuadraticProbing::createAccount(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = newhash2(id, bankStorage1d);
    Account newacc;
    newacc.id = id;
    newacc.balance = count;
    bankStorage1d[myval] = newacc;
    rizzel++;
}
void chotumerge1(vector<int> &dummy, int begin, int midd, int ending)
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
void mergesme1(vector<int> &dummy, int begin, int ending)
{
    if (begin < ending)
    {
        int midd = begin + (ending - begin) / 2;
        mergesme1(dummy, begin, midd);
        mergesme1(dummy, midd + 1, ending);
        chotumerge1(dummy, begin, midd, ending);
    }
}
std::vector<int> QuadraticProbing::getTopK(int k)
{
    // IMPLEMENT YOUR CODE HERE
    vector<int> dummy;
    for (int i = 0; i < 200003; i++)
    {
        if (bankStorage1d[i].balance>=0)
        {
            dummy.push_back(bankStorage1d[i].balance);
        }
    }
    mergesme1(dummy, 0, dummy.size() - 1);
    if (rizzel >= k)
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
        int sup = rizzel;
        int k = rizzel;
        while (k > 0)
        {
            mummy[sup - k] = dummy[dummy.size() - (sup - k) - 1];
            k--;
        }
        return mummy;
    } // Placeholder return value
}

int QuadraticProbing::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    int lh = myval;
    int i = 0;
    int modder = 200003;
    while (true)
    {
        int x = (lh + power3(i, 2, modder)) % modder;
        if ( bankStorage1d[x].balance == -1)
        {
            return -1;
        }
        else if (bankStorage1d[x].balance == -2)
        {
            i++;
        }
        else
        {
            if (bankStorage1d[x].id == id)
                return bankStorage1d[x].balance;
            else
                i++;
        }
    }
    // Placeholder return value
}

void QuadraticProbing::addTransaction(std::string id, int count)
{
    int myval = hash(id);
    int lh = myval;
    int i = 0;
    int modder = 200003;
    int x=lh%modder;
    while (true)
    {
        if ( bankStorage1d[x].balance == -1)
        {
            createAccount(id, count);
            return;
        }
        else if (bankStorage1d[x].balance == -2)
        {
            i++;
        }
        else
        {
            if (bankStorage1d[x].id == id)
            {
                bankStorage1d[x].balance += count;
                return;
            }
            else
                i++;
        }
        x = (lh + power3(i, 2, modder)) % modder;
    }
    // IMPLEMENT YOUR CODE HERE
}

bool QuadraticProbing::doesExist(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    int lh = myval;
    int i = 0;
    int modder = 200003;
    while (true)
    {
        int x = (lh + power3(i, 2, modder)) % modder;
        if ( bankStorage1d[x].balance == -1)
        {
            return false;
        }
        else if (bankStorage1d[x].balance == -2)
        {
            i++;
        }
        else
        {
            if (bankStorage1d[x].id == id)
                return true;
            else
                i++;
        }
    }
    // Placeholder return value
}

bool QuadraticProbing::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int myval = hash(id);
    int lh = myval;
    int i = 0;
    int modder = 200003;
    while (true)
    {
        int x = (lh + power3(i, 2, modder)) % modder;
        if (bankStorage1d[x].balance == -1)
        {
            return false;
        }
        else if (bankStorage1d[x].balance == -2)
        {
            i++;
        }
        else
        {
            if (bankStorage1d[x].id == id)
            {
                bankStorage1d[x].id = "VOID";
                bankStorage1d[x].balance = -2;
                rizzel--;
                return true;
            }
            else
                i++;
        }
    } // Placeholder return value
}
int QuadraticProbing::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return rizzel;
    // Placeholder return value
}

int QuadraticProbing::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int loserhash = 0;
    int modder = 200003;
    for (int i = 0; i < id.length(); i++)
    {
        int x = static_cast<int>(id[i]);
        loserhash = (loserhash + power3(x, i + 1, modder)) % modder;
    }
    return loserhash % modder;
    // Placeholder return value
}