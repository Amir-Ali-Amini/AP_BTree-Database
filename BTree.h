// P name
// Fig :
// use ?:
// date
// amiraliamini 610399102 UT-CS-99

//=================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
using namespace std;

//=================================================================================
// #include"node.h"
//---------------------------------------------------------------------------------

class BTree;

class BTNode
{
    friend class BTree;

public:
    BTNode()
    {
        isNode = true;
        childs = 0;
        leftPtr = extraPtr = rightPtr = midPtr = 0;
        leftData = rightData = extraData = 0;
    }

    void fix() // sort members of BTNode
    {

        if (leftData == 0)
        {
            leftData = extraData;
            extraData = 0;
        }
        else if (leftData->data > extraData->data)
        {
            if (rightData == 0)
            {
                rightData = leftData;
                leftData = extraData;
                extraData = 0;
            }
            else
            {
                Node *newPtr = extraData;
                extraData = leftData;
                leftData = newPtr;
            }
        }
        else if (rightData)
        {
            if (extraData->data > rightData->data)
            {
                Node *newPtr = extraData;
                extraData = rightData;
                rightData = newPtr;
            }
        }
        else
        {
            rightData = extraData;
            extraData = 0;
        }
    }

    //====================================================
    BTNode *leftPtr, *midPtr, *extraPtr, *rightPtr, *fatherPtr;
    Node *leftData, *extraData, *rightData;
    bool isNode = true;
    int childs; // how many childern
    Node *getNewNode(long long d)
    {
        Node *newPtr = new Node;
        newPtr->data = d;
        newPtr->self = this;
        return newPtr;
    }
};

#define ll long long
long long STI(string a)
{
    if (a[0] == '"')
        a = a.substr(1);
    long long ans = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == '"')
            break;
        ans *= 40;
        if (a[i] >= '0' && a[i] <= '9')
            ans += int(a[i]) - 48;
        if (a[i] >= 'a' && a[i] <= 'z')
            ans += int(a[i]) - 87;
    }
    return ans;
}
string ITS(ll a)
{
    char ls[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    string ans = "";
    while (a)
    {
        ans += ls[a % 40];
        a /= 40;
    }
    string anss = "";
    for (int i = 0; i < ans.size(); i++)
    {
        anss += ans[ans.size() - i - 1];
    }
    return anss;
}
long long DTI(string a)
{
    while (a[0] == ' ')
        a = a.substr(1);
    if (a[7] != '/')
        a = a.substr(0, 5) + '0' + a.substr(5);
    if (a.size() < 10)
        a = a.substr(0, 8) + '0' + a.substr(8);
    long long ans = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == '/')
            continue;
        ans *= 10;
        ans += int(a[i]) - 48;
    }
    return ans;
}
string ITD(ll date)
{

    string ans = "0000/00/00";
    for (int i = 9; i >= 0; i--)
    {
        if (i == 4 || i == 7)
            i--;
        ans[i] = char(date % 10 + 48);
        date /= 10;
    }
    int h = 0;
    for (int i = 3; i < ans.size() && h < 2; i++)
    {
        if (ans[i - 1] == '/' && ans[i] == '0')
            ans = ans.substr(0, i) + ans.substr(i + 1);
        if (ans[i - 1] == '/')
            h++;
    }
    return ans;
}

long long ITI(string a)
{
    long long ans = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == ' ')
            continue;
        ans *= 10;
        ans += int(a[i]) - 48;
    }
    return ans;
}

string ITI(ll a)
{
    string ans = "";
    while (a)
    {
        ans = char((a % 10) + 48) + ans;
        a /= 10;
    }
    return ans;
}
