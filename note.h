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

//----------------------------------------------------------------------------------

// node for header
// Fig :
// use ?:
// date
// amiraliamini 610399102 UT-CS-99

//=================================================================================

class BTNode;
class BTree;

class Node
{
public:
    long long data;
    Node *nextField;
    BTNode *self;
};