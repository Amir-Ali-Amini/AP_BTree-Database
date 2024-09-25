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
// #include"BTree.h"
//---------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
class BTree
{
public:
    BTree()
    {
        nodeCounter = 0;
        isEmpty = true;
        rootPtr = 0;
    }
    //---------------------------------------------------------insert
    Node *insert(long long d)
    {
        if (!rootPtr)
        {
            rootPtr = getNewNode(d);
            isEmpty = false;
            rootPtr->leftData->self = rootPtr;
            return rootPtr->leftData;
        }
        else
        {
            BTNode *nodeToAdd = find(d);
            // cout<<nodeToAdd->leftData->data<< " : " <<d<<"----\n";
            nodeToAdd->extraData = nodeToAdd->getNewNode(d);
            nodeToAdd->extraData->self = nodeToAdd;
            Node *nodeToReturn = nodeToAdd->extraData;
            Node *adedNode = nodeToAdd->extraData;
            nodeToAdd->fix();
            fixInsert(nodeToAdd);
            return nodeToReturn;
        }
    }
    void fixInsert(BTNode *&nodeToFix) // give extra member to up row
    {
        BTNode *fatherPtr = nodeToFix->fatherPtr;

        long long childNumber; // wich chid of father
        if (fatherPtr)
        {
            if (fatherPtr->leftPtr == nodeToFix)
                childNumber = 1;
            if (fatherPtr->midPtr == nodeToFix)
                childNumber = 2;
            if (fatherPtr->rightPtr == nodeToFix)
                childNumber = 3;
            fatherPtr->isNode = false;
        }
        if (nodeToFix->extraData)
        {
            BTNode *upNode = getNewNode(nodeToFix->extraData);
            upNode->leftData->self = upNode;
            upNode->isNode = false;
            if (nodeToFix->rightData)
            {
                upNode->midPtr = getNewNode(nodeToFix->rightData, upNode);
                upNode->midPtr->midPtr = nodeToFix->rightPtr;
                if (upNode->midPtr->midPtr)
                    upNode->midPtr->midPtr->fatherPtr = upNode->midPtr; // show father to child
                upNode->midPtr->leftPtr = nodeToFix->extraPtr;
                if (upNode->midPtr->leftPtr)
                    upNode->midPtr->leftPtr->fatherPtr = upNode->midPtr;
            }
            nodeToFix->extraData = nodeToFix->rightData = 0;
            nodeToFix->rightPtr = nodeToFix->extraPtr = 0;
            upNode->leftPtr = nodeToFix;
            upNode->isNode = false;
            nodeToFix->fatherPtr = upNode;
            if (upNode->midPtr->midPtr != 0 || upNode->midPtr->leftPtr != 0)
                upNode->midPtr->isNode = false;
            if (upNode->leftPtr->midPtr != 0 || upNode->leftPtr->leftPtr != 0)
                upNode->leftPtr->isNode = false;

            // cout<<"upnode: " << upNode->leftData->data<<
            // "ul : "<<upNode->leftPtr->leftData->data<<
            // "ur : "<<upNode->midPtr->leftData->data<<endl;
            merge(fatherPtr, upNode, childNumber);
        }
    }
    void merge(BTNode *&first, BTNode *&second, long long c = -1) // merge 2 nodes
    {
        second->isNode = false;
        if (first)
        {
            second->leftPtr->fatherPtr = second->midPtr->fatherPtr = first;
            first->isNode = false;
            first->extraData = second->leftData;
            first->extraData->self = first;
            first->fix();
            // cout<< second->leftData->data<<" : "<<first->rightData->data<<endl;
            if (c == 1)
            {

                first->extraPtr = first->midPtr;
                first->midPtr = first->leftPtr;
                first->leftPtr = second->leftPtr;
                first->midPtr = second->midPtr;
                if (first->extraData == 0)
                {
                    first->rightPtr = first->extraPtr;
                    first->extraPtr = 0;
                    // cout<<"yes\n";
                    // cout<<first->rightData->  self->leftData->  data<<endl;
                }
            }
            if (c == 2)
            {

                first->extraPtr = second->midPtr;
                first->midPtr = second->leftPtr;
                if (first->extraData == 0)
                {
                    first->rightPtr = first->extraPtr;
                }
            }
            if (c == 3)
            {
                first->extraPtr = second->leftPtr;
                first->rightPtr = second->midPtr;
            }
            if (first->leftPtr)
                first->leftPtr->fatherPtr = first;
            if (first->midPtr)
                first->midPtr->fatherPtr = first;
            if (first->rightPtr)
                first->rightPtr->fatherPtr = first;
            first->isNode = false;
            if (first->extraData)
                fixInsert(first);
        }
        else
        {
            rootPtr = second;
            rootPtr->isNode = false;
        }
    }
    BTNode *find(long long d) // calling findPrivate with rootPtr for insert
    {
        return findPrivate(d, rootPtr);
    }
    void printAll()
    {
        print(rootPtr);
        cout << "----------------------------" << endl;
    }

    //------------------------------------------------------delete
    void deleteNode(long long d)
    {
        BTNode *place = findDelete(d);
        cout << "deleting \n";
        if (place)
        {
            if (place->isNode)
            {
                cout << "is node\n";
                if (place->rightData)
                {
                    if (d == place->leftData->data)
                    {
                        delete place->leftData;
                        place->leftData = place->rightData;
                        place->rightData = 0;
                    }
                    else
                    {
                        delete place->rightData;
                        place->rightData = 0;
                    }
                }
                else
                {
                    if (place->fatherPtr->leftPtr == place)
                    {
                        cout << "its left child\n";
                        if (place->fatherPtr->midPtr)
                        {
                            if (place->fatherPtr->midPtr->rightData)
                            {
                                delete place->leftData;
                                cout << "is *\n";
                                place->leftData = place->fatherPtr->leftData;
                                place->leftData->self = place;
                                place->fatherPtr->leftData = place->fatherPtr->midPtr->leftData;
                                place->fatherPtr->leftData->self = place->fatherPtr;
                                place->fatherPtr->midPtr->leftData = place->fatherPtr->midPtr->rightData;
                                place->fatherPtr->midPtr->rightData = 0;
                                place->fatherPtr->midPtr->leftPtr = place->fatherPtr->midPtr->midPtr;
                                place->fatherPtr->midPtr->midPtr = place->fatherPtr->midPtr->rightPtr;
                                place->fatherPtr->midPtr->rightPtr = 0;
                            }
                            else
                            {
                                delete place->leftData;
                                fixDelete(place);
                            }
                        }
                        else
                        {
                            delete place->leftData;
                        }
                    }
                    else if (place->fatherPtr->midPtr == place)
                    {
                    }
                }
            }
        }
    }
    Node *dl(long long d)
    {
        BTNode *place = findDelete(d);
        Node *NTR = 0;
        if (place == 0)
        {
            // cout<< "what you want to delete " << d << " is not in tree \n";
            return 0;
        }
        if (place->isNode)
        {
            if (place->leftData->data == d)
            {
                BTNode *rp = rootPtr;
                NTR = place->leftData->nextField;
                delete place->leftData;
                place->leftData = place->rightData;
                place->rightData = 0;
                if (place == rootPtr)
                {
                    if (place->leftData == 0)
                        rootPtr = 0;
                }
                if (place != rp)
                    fixDelete(place);
            }
            else
            {
                NTR = place->rightData->nextField;
                delete place->rightData;
                place->rightData = 0;
            }
        }
        else
        {
            Node *nFR, *placeNode;
            if (place->leftData->data == d)
            {
                NTR = place->leftData->nextField;
                placeNode = place->leftData;
                if (place->midPtr)
                    nFR = findToReplaceR(place->midPtr);
                else
                    nFR = findToReplaceL(place->leftPtr);
                if (nFR->self->leftData = nFR)
                {
                    nFR->self->leftData = placeNode;
                    placeNode->self = nFR->self;
                    place->leftData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    place->leftData = 0;
                    place->leftData = place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                    // cout<<d<<"......\n";
                }
                else
                {
                    nFR->self->rightData = placeNode;
                    placeNode->self = nFR->self;
                    place->leftData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    // place->leftData=place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                }
            }
            else
            {
                NTR = place->rightData->nextField;
                placeNode = place->rightData;
                if (place->rightPtr)
                    nFR = findToReplaceR(place->rightPtr);
                else
                    nFR = findToReplaceL(place->midPtr);
                if (nFR->self->leftData = nFR)
                {
                    nFR->self->leftData = placeNode;
                    placeNode->self = nFR->self;
                    place->rightData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    place->leftData = place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                }
                else
                {
                    nFR->self->rightData = placeNode;
                    placeNode->self = nFR->self;
                    place->rightData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    // place->leftData=place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                }
            }
        }

        return NTR;
    }

    void fx(BTNode *root)
    {
        if (root)
        {
            if (root->leftData)
                root->leftData->self = root;
            if (root->rightData)
                root->rightData->self = root;
            if (root->leftPtr)
            {
                root->leftPtr->fatherPtr = root;
                fx(root->leftPtr);
            }
            if (root->midPtr)
            {
                root->midPtr->fatherPtr = root;
                fx(root->midPtr);
            }
            if (root->rightPtr)
            {
                root->rightPtr->fatherPtr = root;
                fx(root->rightPtr);
            }
        }
    }
    Node *dl(Node *dd)
    {
        // cout << "deleting : " <<dd<< " " << dd->data<< endl;
        BTNode *place = dd->self;
        long long d = dd->data;
        // printAll();
        fx(rootPtr);
        Node *NTR;
        if (place == 0)
        {
            cout << "what you want to delete " << d << " is not in tree \n";
            return 0;
        }
        if (place->isNode)
        {
            if (place->leftData->data == d)
            {
                BTNode *rp = rootPtr;
                NTR = place->leftData->nextField;
                delete place->leftData;
                place->leftData = place->rightData;
                place->rightData = 0;
                if (place == rootPtr)
                {
                    if (place->leftData == 0)
                        rootPtr = 0;
                }
                if (place != rp)
                    fixDelete(place);
            }
            else
            {
                NTR = place->rightData->nextField;
                delete place->rightData;
                place->rightData = 0;
            }
        }
        else
        {
            Node *nFR, *placeNode;
            if (place->leftData->data == d)
            {
                NTR = place->leftData->nextField;
                placeNode = place->leftData;
                if (place->midPtr)
                    nFR = findToReplaceR(place->midPtr);
                else
                    nFR = findToReplaceL(place->leftPtr);
                if (nFR->self->leftData = nFR)
                {
                    nFR->self->leftData = placeNode;
                    placeNode->self = nFR->self;
                    place->leftData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    place->leftData = 0;
                    place->leftData = place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                    // cout<<d<<"......\n";
                }
                else
                {
                    nFR->self->rightData = placeNode;
                    placeNode->self = nFR->self;
                    place->leftData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    // place->leftData=place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                }
            }
            else
            {
                NTR = place->rightData->nextField;
                placeNode = place->rightData;
                if (place->rightPtr)
                    nFR = findToReplaceR(place->rightPtr);
                else
                    nFR = findToReplaceL(place->midPtr);
                if (nFR->self->leftData = nFR)
                {
                    nFR->self->leftData = placeNode;
                    placeNode->self = nFR->self;
                    place->rightData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    place->leftData = place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                }
                else
                {
                    nFR->self->rightData = placeNode;
                    placeNode->self = nFR->self;
                    place->rightData = nFR;
                    nFR->self = place;
                    place = placeNode->self;
                    delete placeNode;
                    // place->leftData=place->rightData;
                    place->rightData = 0;
                    fixDelete(place);
                }
            }
        }
        // printAll();
        // cout<< "deleting : " <<d << " done\n";
        return NTR;
    }
    Node *findToReplaceL(BTNode *place)
    {
        if (place->isNode)
        {
            if (place->rightData)
                return place->rightData;
            else
                place->leftData;
        }
        else
        {
            if (place->rightPtr)
                return findToReplaceL(place->rightPtr);
            if (place->midPtr)
                return findToReplaceL(place->midPtr);
        }
        return 0;
    }
    Node *findToReplaceR(BTNode *place)
    {
        if (place->isNode)
        {
            return place->leftData;
        }
        else
        {
            return findToReplaceR(place->leftPtr);
        }
    }
    void fixDelete(BTNode *&place) // a is child number
    {
        if (!place->leftData)
        {
            if (place == rootPtr)
            {
                rootPtr = rootPtr->leftPtr;
                rootPtr->fatherPtr = 0;
                place->leftPtr = 0;
                delete place;
                return;
            }
            long long childNumber;
            if (place->fatherPtr->leftPtr == place)
                childNumber = 1;
            if (place->fatherPtr->midPtr == place)
                childNumber = 2;
            if (place->fatherPtr->rightPtr == place)
                childNumber = 3;
            BTNode *f = place->fatherPtr;
            if (childNumber == 1)
            {
                if (f->midPtr)
                {
                    if (f->midPtr->leftData == 0)
                        f->midPtr = 0;
                }
                if (f->midPtr)
                {

                    if (!f->midPtr->rightData)
                    {
                        place->leftData = f->leftData;
                        place->leftData->self = place;
                        if (f->midPtr)
                        {
                            place->rightData = f->midPtr->leftData;
                            if (place->rightData)
                                place->rightData->self = place;
                            place->midPtr = f->midPtr->leftPtr;
                            if (place->midPtr)
                                place->midPtr->fatherPtr = place;
                            place->rightPtr = f->midPtr->midPtr;
                            if (place->rightPtr)
                                place->rightPtr->fatherPtr = place;
                            f->midPtr->leftPtr = 0;
                            f->midPtr->rightPtr = 0;
                            f->midPtr->leftData = 0;
                            delete f->midPtr;
                        }
                        f->leftData = f->rightData;
                        f->rightData = 0;
                        f->midPtr = f->rightPtr;
                        if (f->leftPtr)
                            f->leftPtr->fatherPtr = f;
                        f->rightPtr = 0;
                        fixDelete(f);
                        return;
                    }
                    else
                    {
                        turnL(place);
                    }
                }
            }
            if (childNumber == 2)
            {
                if (f->rightPtr)
                {
                    if (f->rightPtr->leftData == 0)
                        f->rightPtr = 0;
                }
                if (f->leftPtr)
                {
                    if (f->leftPtr->rightData)
                    {
                        turnML(place);
                        fixDelete(f);
                        return;
                    }
                }
                if (f->rightPtr)
                {
                    if (f->rightPtr->rightData)
                    {
                        turnMR(place);
                        fixDelete(f);
                        return;
                    }
                }
                if (f->leftPtr)
                {
                    if (!f->leftPtr->rightData)
                    {
                        // cout<<"-here 2-"<<endl;
                        BTNode *p = f->leftPtr;
                        p->rightData = f->leftData;
                        p->rightData->self = p;
                        f->midPtr->leftData = 0;
                        p->rightPtr = place->leftPtr;
                        if (p->rightPtr)
                            p->rightPtr->fatherPtr = p;
                        place->leftPtr = 0;
                        delete f->midPtr;
                        if (f->rightPtr)
                        {
                            if (f->rightPtr->leftData == 0)
                            {
                                delete f->rightPtr;
                                f->rightPtr = 0;
                            }
                        }
                        f->leftData = f->rightData;
                        f->rightData = 0;
                        f->midPtr = f->rightPtr;
                        f->rightPtr = 0;
                        fixDelete(f);
                        return;
                    }
                }
                if (f->rightPtr)
                {
                    if (!f->rightPtr->rightData)
                    {
                        place->rightData = f->rightData;
                        place->rightData->self = place;
                        place->rightPtr = f->rightPtr->leftPtr;
                        if (place->rightPtr)
                            place->rightPtr->fatherPtr = place;
                        f->rightPtr->leftPtr = 0;
                        f->rightPtr->leftData = 0;
                        delete f->rightPtr;
                        f->rightData = 0;
                        f->rightPtr = 0;
                        fixDelete(f);
                        return;
                    }
                }
            }
            if (childNumber == 3)
            {
                if (f->midPtr)
                {
                    // cout<<"-here 3-"<<endl;

                    if (!f->midPtr->rightData)
                    {
                        BTNode *p = f->midPtr;
                        p->rightData = f->rightData;
                        p->rightData->self = p;
                        f->rightData = 0;
                        place->leftData = 0;
                        p->rightPtr = place->leftPtr;
                        if (p->rightPtr)
                            p->rightPtr->fatherPtr = p;
                        place->leftPtr = place->midPtr = place->rightPtr = 0;
                        place->fatherPtr->rightPtr = 0;
                        delete place;
                        fixDelete(f);
                        return;
                    }
                    else
                    {
                        turnR(place);
                        fixDelete(f);
                        return;
                    }
                }
            }
        }
    }
    void turnL(BTNode *place)
    {
        BTNode *f = place->fatherPtr;
        place->leftData = place->fatherPtr->leftData;
        place->leftData->self = place;
        place->fatherPtr->leftData = place->fatherPtr->midPtr->leftData;
        place->fatherPtr->leftData->self = place->fatherPtr;
        place->fatherPtr->midPtr->leftData = place->fatherPtr->midPtr->rightData;
        if (f->midPtr)
            place->fatherPtr->midPtr->leftData->self = f->midPtr;
        place->fatherPtr->midPtr->rightData = 0;
        place->midPtr = f->midPtr->leftPtr;
        place->fatherPtr->midPtr->leftPtr = place->fatherPtr->midPtr->midPtr;
        if (f->midPtr->leftPtr)
            f->midPtr->leftPtr->fatherPtr = f->midPtr;
        place->fatherPtr->midPtr->midPtr = place->fatherPtr->midPtr->rightPtr;
        if (f->midPtr->midPtr)
            f->midPtr->midPtr->fatherPtr = f->midPtr;
        place->fatherPtr->midPtr->rightPtr = 0;
    }
    void turnML(BTNode *place)
    {
        BTNode *f = place->fatherPtr;
        place->leftData = f->leftData;
        place->leftData->self = place;
        f->leftData = f->leftPtr->rightData;
        f->leftData->self = f;
        f->leftPtr->rightData = 0;
        place->midPtr = place->leftPtr;
        if (place->midPtr)
            place->midPtr->fatherPtr = place;
        place->leftPtr = f->leftPtr->rightPtr;
        if (place->leftPtr)
            place->leftPtr->fatherPtr = place;
        f->leftPtr->rightPtr = 0;
    }
    void turnMR(BTNode *place)
    {
        BTNode *f = place->fatherPtr;
        place->leftData = f->rightData;
        place->leftData->self = place;
        f->rightData = f->rightPtr->leftData;
        f->rightData->self = f;
        f->rightPtr->leftData = f->rightPtr->rightData;
        if (f->rightPtr->rightData)
            f->rightPtr->rightData->self = f->rightPtr;
        f->rightPtr->rightData = 0;
        place->midPtr = f->rightPtr->leftPtr;
        if (place->midPtr)
            place->midPtr->fatherPtr = place;
        f->rightPtr->leftPtr = f->rightPtr->midPtr;
        if (f->rightPtr->leftPtr)
            f->rightPtr->leftPtr->fatherPtr = f->rightPtr;
        f->rightPtr->midPtr = f->rightPtr->rightPtr;
        if (f->rightPtr->midPtr)
            f->rightPtr->midPtr->fatherPtr = f->rightPtr;
        f->rightPtr->rightPtr = 0;
    }
    void turnR(BTNode *place)
    {
        BTNode *f = place->rightPtr;
        place->leftData = f->rightData;
        place->leftData->self = place;
        f->rightData = f->midPtr->rightData;
        f->rightData->self = f;
        f->midPtr->rightData = 0;
        place->leftPtr = f->midPtr->rightPtr;
        if (place->leftPtr)
            place->leftPtr->fatherPtr = place;
        f->midPtr->rightPtr = 0;
    }
    // void deleteNode (long long d )
    // {
    //     BTNode* place = findDelete(d);
    //     if (place)
    //     {
    //         if (place->isNode)
    //         {
    //             delete
    //         }
    //     }
    // }

    Node *findMin()
    {
        return findM(rootPtr);
    }
    Node *findMember(long long d)
    {
        BTNode *a = findDelete(d);
        if (a)
        {
            if (a->leftData->data == d)
                return a->leftData;
            else
                return a->rightData;
        }
        return 0;
    }
    Node *findM(BTNode *root)
    {
        if (root)
        {
            if (root->isNode)
            {
                return root->leftData;
            }
            return findM(root->leftPtr);
        }
        else
            return 0;
    }
    BTNode *findDelete(long long d)
    {
        return findDeleteP(d, rootPtr);
    }

    vector<Node *> BT(long long a)
    {
        vector<Node *> ans;
        outputBT(rootPtr, a, ans);
        return ans;
    }
    vector<Node *> AND(long long a, long long b)
    {
        vector<Node *> ans;
        outputAND(rootPtr, a, b, ans);
        return ans;
    }
    vector<Node *> OR(long long a, long long b)
    {
        vector<Node *> ans;
        outputOR(rootPtr, a, b, ans);
        return ans;
    }
    vector<Node *> LS(long long a)
    {
        vector<Node *> ans;
        outputLT(rootPtr, a, ans);
        // for(int i =0 ; i<ans.size() ; i++)
        // {
        //     cout<<ans[i]->data<<" ";
        // }
        // cout<<"here\n";
        return ans;
    }

    //------------------------------------------------------
    void print(BTNode *n) // print
    {
        if (n)
        {
            if (n->leftData)
                cout << (n->leftData->self->leftData->data) << "  it was left  ";
            if (n->rightData)
                cout << n->rightData->self->rightData->data << "  it was right  ";
            cout << endl;
            print(n->leftPtr);
            print(n->midPtr);
            print(n->rightPtr);
        }
    }
    // void print (BTNode* n) // print
    // {
    //     if (n)
    //     {
    //         if (n->leftData)
    //             cout<< (n->leftData->data)<< "  it was left  ";
    //         if (n->rightData)
    //             cout<<n->rightData->data<<"  it was right  ";
    //         cout<<endl;
    //     print(n->leftPtr);
    //     print(n->midPtr);
    //     print(n->rightPtr);
    //     }
    // }
    // void print (BTNode* n) // print preorder
    // {
    //     if (n)
    //     {
    //     print(n->leftPtr);
    //         if (n->leftData)
    //             cout<< (n->leftData->data)<< "-";
    //     print(n->midPtr);
    //         if (n->rightData)
    //             cout<<n->rightData->data<<"-";
    //     print(n->rightPtr);
    //     }
    // }

    void outputBT(BTNode *n, long long bt, vector<Node *> &ans) // print preorder
    {
        if (n)
        {
            if (n->leftData)
            {
                if (n->leftData->data > bt)
                    outputBT(n->leftPtr, bt, ans);
                if (n->leftData->data > bt)
                    ans.push_back(n->leftData);
            }
            if (n->rightData)
            {
                if (n->rightData->data > bt)
                    outputBT(n->midPtr, bt, ans);
                if (n->rightData->data > bt)
                    ans.push_back(n->rightData);
            }
            else
            {
                outputBT(n->midPtr, bt, ans);
            }

            outputBT(n->rightPtr, bt, ans);
        }
    }
    // void outputBT (BTNode* n , long long bt,  vector <Node * >& ans) // print preorder
    // {
    //     if (n)
    //     {
    //         if (n->leftData)
    //         {
    //             // cout<< n -> leftData-> data <<">left ="<< bt<<endl;
    //             // if ( n -> leftData-> data>= bt )   outputBT(n->leftPtr , bt , ans);
    //             if ( n -> leftData-> data> bt ) ans.push_back(n->leftData);
    //         }
    //         if (n->rightData)
    //         {
    //             // cout<< n -> rightData-> data <<">right="<< bt<<endl;
    //             // if ( n -> rightData-> data>= bt ) outputBT(n->midPtr , bt , ans);
    //             if ( n -> rightData-> data> bt )ans.push_back(n->rightData);
    //         }
    //         outputBT(n->leftPtr , bt , ans);
    //         outputBT(n->midPtr , bt , ans);
    //         outputBT(n->rightPtr , bt , ans);
    //     }
    // }
    void outputLT(BTNode *n, long long lt, vector<Node *> &ans) // print preorder
    {
        // cout<<"here\n";
        if (n)
        {
            // cout<<n->leftData->data<<endl;
            // cout<<"here0\n";
            outputLT(n->leftPtr, lt, ans);
            // cout<<"here1\n";
            if (n->leftData)
                if (n->leftData->data < lt)
                    ans.push_back(n->leftData);
            // cout<<"here2\n";
            if (n->rightData)
            {
                if (n->leftData->data < lt)
                    outputLT(n->midPtr, lt, ans);
                if (n->rightData->data < lt)
                    ans.push_back(n->rightData);
                // cout<<"here4\n";
                if (n->rightPtr)
                {
                    if (n->leftData->data < lt)
                        outputLT(n->rightPtr, lt, ans);
                }
            }
            else if (n->midPtr)
            {
                if (n->midPtr && n->leftData->data < lt)
                    outputLT(n->midPtr, lt, ans);
                // cout<<"here3\n";
            }
        }
    }
    void outputAND(BTNode *n, long long bt, long long lt, vector<Node *> &ans) // print preorder
    {
        if (n)
        {
            if (n->leftData)
            {
                if (n->leftData->data >= bt)
                    outputAND(n->leftPtr, bt, lt, ans);
                if (n->leftData->data >= bt && n->leftData->data <= lt)
                    ans.push_back(n->leftData);
            }
            if (n->rightData)
            {
                if (n->rightData->data >= bt && n->leftData->data <= lt)
                    outputAND(n->midPtr, bt, lt, ans);
                if (n->rightData->data >= bt && n->rightData->data <= lt)
                    ans.push_back(n->rightData);
            }
            else
            {
                if (n->leftData->data <= lt)
                    outputAND(n->midPtr, bt, lt, ans);
            }
            if (n->rightData)
                if (n->rightData->data <= lt)
                    outputAND(n->rightPtr, bt, lt, ans);
        }
    }
    // void outputAND (BTNode* n , long long bt,long long lt,  vector <Node * > &ans) // print preorder
    // {
    //     if (n)
    //     {
    //         if (n->leftData)
    //         {
    //             // cout<< n -> leftData-> data <<">left ="<< bt<<endl;
    //             // if ( n -> leftData-> data>= bt )   outputBT(n->leftPtr , bt , ans);
    //             if ( n -> leftData-> data== bt) ans.push_back(n->leftData);
    //         }
    //         if (n->rightData)
    //         {
    //             // cout<< n -> rightData-> data <<">right="<< bt<<endl;
    //             // if ( n -> rightData-> data>= bt ) outputBT(n->midPtr , bt , ans);
    //             if ( n -> rightData-> data== bt )ans.push_back(n->rightData);
    //         }
    //         outputBT(n->leftPtr , bt , ans);
    //         outputBT(n->midPtr , bt , ans);
    //         outputBT(n->rightPtr , bt , ans);
    //     }
    // }
    void outputOR(BTNode *n, long long lt, long long bt, vector<Node *> &ans) // print preorder
    {
        if (n)
        {
            outputOR(n->leftPtr, bt, lt, ans);
            if (n->leftData)
                if (n->leftData->data >= bt || n->leftData->data <= lt)
                    ans.push_back(n->leftData);
            if (n->rightData)
            {
                if (n->rightData->data >= bt || n->leftData->data <= lt)
                    outputOR(n->midPtr, bt, lt, ans);
                if (n->rightData->data >= bt || n->rightData->data <= lt)
                    ans.push_back(n->rightData);
            }
            else
            {
                outputOR(n->midPtr, bt, lt, ans);
            }
            if (n->rightData)
                outputOR(n->rightPtr, bt, lt, ans);
        }
    }

    //=====================================================
    BTNode *rootPtr;
    long long nodeCounter;
    bool isEmpty;
    BTNode *getNewNode(long long d, BTNode *f = 0)
    {
        BTNode *newPtr = new BTNode;
        newPtr->leftData = newPtr->getNewNode(d);
        newPtr->fatherPtr = f;
        return newPtr;
    }
    BTNode *getNewNode(Node *d, BTNode *f = 0)
    {
        BTNode *newPtr = new BTNode;
        newPtr->leftData = d;
        d->self = newPtr;
        newPtr->fatherPtr = f;
        return newPtr;
    }
    BTNode *findPrivate(long long d, BTNode *root) // finding where to insert
    {
        if (root->isNode == true)
        {
            // cout<< "root " << root->leftData->data <<endl;
            return root;
        }
        else
        {
            if (d <= root->leftData->data)
                return findPrivate(d, root->leftPtr);
            if (root->rightData)
            {
                if (d <= root->rightData->data)
                    return findPrivate(d, root->midPtr);
                return findPrivate(d, root->rightPtr);
            }
            return findPrivate(d, root->midPtr);
        }
    }
    BTNode *findDeleteP(long long d, BTNode *root)
    {
        if (d == root->leftData->data)
            return root;
        if (root->rightData)
        {
            if (d == root->rightData->data)
                return root;
        }
        if (root->isNode == true)
        {
            return 0;
        }
        else
        {
            if (d <= root->leftData->data)
                return findDeleteP(d, root->leftPtr);
            if (root->rightData)
            {
                if (d <= root->rightData->data)
                    return findDeleteP(d, root->midPtr);
                return findDeleteP(d, root->rightPtr);
            }
            return findDeleteP(d, root->midPtr);
        }
    }
};

//--------------------------------------------------------------------------------
class table
{
public:
    table()
    {
        fieldsNmae.push_back("id");
        fieldsType.push_back("int");
        id = new BTree;
        deletedIds = new BTree;
        // deletedIds->insert(-1);
        fields.push_back(id);
        nextId = 1;
    }

    void inputField(string name, string type)
    {
        string namee = "", typee = "";
        for (int i = 0; i < name.size(); i++)
        {
            if (name[i] >= 'a' && name[i <= 'z'])
                namee += name[i];
        }
        for (int i = 0; i < type.size(); i++)
        {
            if (type[i] >= 'a' && type[i <= 'z'])
                typee += type[i];
        }
        fieldsNmae.push_back(namee);
        fieldsType.push_back(typee);
        fields.push_back(new BTree);
        // cout<< "."+namee+"."+typee+".\n";
    }

    void input(vector<ll> inp)
    {
        ll number = inp.size();
        ll minId = NID();
        Node *idNode = id->insert(minId);
        Node *forNextNode = idNode;
        Node *insertedNode;
        for (ll i = 1; i <= number; i++)
        {
            insertedNode = fields[i]->insert(inp[i - 1]);
            forNextNode->nextField = insertedNode;
            forNextNode = insertedNode;
        }
        forNextNode->nextField = idNode;
    }
    void input(vector<ll> inp, int minId)
    {
        ll number = inp.size();
        Node *idNode = id->insert(minId);
        Node *forNextNode = idNode;
        Node *insertedNode;
        for (ll i = 1; i <= number; i++)
        {
            insertedNode = fields[i]->insert(inp[i - 1]);
            forNextNode->nextField = insertedNode;
            forNextNode = insertedNode;
        }
        forNextNode->nextField = idNode;
    }

    ll NID()
    {
        Node *newPtr = deletedIds->findMin();
        if (newPtr)
        {
            // cout<<newPtr->data;
            if (newPtr)
            {
                ll ans = newPtr->data;
                deletedIds->dl(newPtr);
                return ans;
            }
            return nextId++;
        }
        else
            return nextId++;
    }

    void dlt(Node *id)
    {
        ll deleted = id->data;
        if (deleted != -1)
        {
            Node *NTD = id;
            for (ll i = 0; i < fields.size(); i++)
            {
                NTD = fields[i]->dl(NTD);
            }
            deletedIds->insert(deleted);
        }
    }
    void dlt(Node *id, ll a)
    {
        ll deleted = id->data;
        if (deleted != -1)
        {
            Node *NTD = id;
            for (ll i = 0; i < fields.size(); i++)
            {
                NTD = fields[i]->dl(NTD);
            }
            //  deletedIds->insert(deleted);
        }
    }

    vector<ll> output(Node *id)
    {
        if (id->data != -1)
        {
            vector<ll> ans;
            Node *NTD = id;
            for (ll i = 0; i < fields.size(); i++)
            {
                ans.push_back(NTD->data);
                NTD = NTD->nextField;
            }
            return ans;
        }
    }

    void p()
    {
        for (int i = 0; i < fieldsType.size(); i++)
        {
            cout << i << " " << fieldsNmae[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < fieldsType.size(); i++)
        {
            cout << i << " " << fieldsType[i] << " ";
        }
        cout << endl;
    }
    Node *getId(Node *i, int T)
    {
        if (T == 0)
            return i;
        int f = fields.size();
        return getId(i->nextField, (T + 1) % f);
    }

    void update(Node *i, vector<ll> a)
    {
        // cout<<"updating\n";
        if (i->data != -1)
        {
            ll minId = i->data;
            dlt(i, 1);
            input(a, minId);
        }
    }
    //======================================
    BTree *id;
    vector<string> fieldsNmae;
    vector<string> fieldsType;
    vector<BTree *> fields;
    BTree *deletedIds;
    ll nextId;
};

void swp(vector<Node *> &a, int i)
{
    Node *temp = a[i];
    a[i] = a[i - 1];
    a[i - 1] = temp;
}

vector<Node *> srt(vector<Node *> &a)
{
    bool c = true;
    for (int j = 0; j < a.size(); j++)
    {
        c = false;
        for (int i = 1; i < a.size(); i++)
        {
            if (a[i]->data < a[i - 1]->data)
            {
                swp(a, i);
                c == true;
            }
        }
    }
    return a;
}
