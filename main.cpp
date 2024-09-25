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
// #include"Dataset.h"
//---------------------------------------------------------------------------------

ll changeTI(string a, int n, table *t)
{
    string b = t->fieldsType[n];
    if (b == "int")
        return ITI(a);

    if (b == "string")
        return STI(a);

    if (b == "timestamp")
    {
        return DTI(a);
    }
    return 0;
}
string changeTS(ll a, int n, table *t)
{
    string b = t->fieldsType[n];
    if (b == "int")
        return ITI(a);

    if (b == "string")
        return ITS(a);

    if (b == "timestamp")
    {
        return ITD(a);
    }
    return 0;
}

int main()
{
    int n;
    cin >> n;
    getchar();
    string *input;
    input = new string[n];
    for (int i = 0; i < n; i++)
    {
        getline(cin, input[i]);
    }
    for (int i = 0; i < n; i++)
    {
        bool cc = false;
        string a = input[i];
        for (int j = 1; j < a.size(); j++)
        {
            if (a[j] == '(')
                cc = true;
            if (!cc)
            {
                if (a[j] == ' ' && a[j - 1] == ' ')
                    a = a.substr(0, j) + a.substr(j + 1);
            }
            else
            {
                if (a[j] == ' ' && a[j - 1] == ',')
                    a = a.substr(0, j) + a.substr(j + 1);
                if (a[j] == ',' && a[j - 1] == ' ')
                    a = a.substr(0, j - 1) + a.substr(j);
            }
        }
        input[i] = a;
        // cout<< i << "  :   " <<a << endl;
    }
    vector<string> tablesName;
    vector<table *> tables;
    int tNumber = 0;
    for (int i = 0; i < n; i++)
    {
        // cout<< i <<endl;
        int j = 0;
        string inp = input[i];
        if (inp[0] == 'C')
        {
            tNumber++;
            string a = "";
            for (j = 13; inp[j] != ' '; j++)
            {
                if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] >= 'A' && inp[j] <= 'Z') || (inp[j] == '/'))
                    a += inp[j];
            }
            tablesName.push_back(a);
            tables.push_back(new table);
            while (inp[j] == ' ' || inp[j] == '(')
                j++;
            a = "";
            string aa = "";
            int s = 0;
            for (j; j <= inp.size(); j++)
            {
                if (inp[j] == ' ' || inp[j] == ',' || inp[j] == ')')
                {
                    s++;
                    s %= 3;
                }
                if (s == 0)
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                }
                else if (s == 1)
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        aa += inp[j];
                }
                else if (s == 2)
                {
                    s = 0;
                    tables[tNumber - 1]->inputField(a, aa);
                    a = "";
                    aa = "";
                }
            }
            vector<ll> minData;
            for (int j = 0; j < tables[tNumber - 1]->fields.size() - 1; j++)
            {
                minData.push_back(-1);
            }
        }

        //--------------------------------------insert into

        else if (inp[0] == 'I')
        {
            string a = "", aa = "";
            for (j = 12; inp[j] != ' '; j++)
            {
                if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] >= 'A' && inp[j] <= 'Z') || (inp[j] == '/'))
                    a += inp[j];
            }
            int t = 0;
            while (tablesName[t] != a)
                t++;
            while (inp[j] != '(')
                j++;
            j++;
            vector<ll> ins;
            int counter = 1;
            a = "";
            for (j; j <= inp.size(); j++)
            {
                if (inp[j] != ',' && inp[j] != ')')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                }
                else
                {
                    // cout<<"."+a+".\n";
                    ins.push_back(changeTI(a, counter, tables[t]));
                    counter++;
                    a = "";
                }
            }

            tables[t]->input(ins);

            // cout<<"end of insert\n";
        }

        //-------------------------- delete

        else if (inp[0] == 'D')
        {
            // cout<<"deleting \n";
            int s, ss;
            string a = "", aa = "";
            for (j = 12; inp[j] != ' '; j++)
            {
                if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] >= 'A' && inp[j] <= 'Z') || (inp[j] == '/'))
                    a += inp[j];
            }
            // cout<<","+a+".\n";
            int t = 0;
            while (tablesName[t] != a)
                t++;
            while (inp[j] != 'E')
                j++;
            j += 4;
            bool chek = false;
            for (int k = j; k < inp.size(); k++)
            {
                if (inp[k] == '&' || inp[k] == '|')
                {
                    chek = true;
                    break;
                }
            }
            if (chek)
            {
                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                char v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp[j] != '&' && inp[j] != '|'; j++)
                {
                    if (inp[j] == '&' || inp[j] == '|')
                        break;
                    aa += inp[j];
                }
                vector<Node *> ansTD;
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> ans;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        ans.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    ans = srt(ans);
                }
                char andOr = inp[j];
                j++;
                for (int m = 0; m < ans.size(); m++)
                {
                    cout << ans[m]->data << "    " << ans[m]->nextField->nextField->nextField->data << "\n";
                }
                //===========================

                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp.size(); j++)
                {
                    if (inp[j] != ' ' && inp[j] != ')')
                        aa += inp[j];
                }
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> anss;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        anss.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    anss = srt(anss);
                }
                // for (int m = 0 ; m <anss.size() ;m++ )
                // {
                //     cout<<anss[m]->data << "    " <<anss[m]->nextField->nextField->nextField->data<< "\n";
                // }

                // for (int m = 0 ; m< anss.size() ; m++)
                // {
                //     cout<< anss[m]->data<< " " ;
                // }
                // cout<< endl;
                // for(int m = 0 ; m < ansTD .size() ; m++)
                // {
                //     cout<< ansTD2[m]->data<<" ";
                // }
                vector<Node *> finalAns;
                if (andOr == '&')
                {
                    cout << "and\n";
                    int s1 = 0, s2 = 0;
                    while (s1 < ans.size() && s2 < anss.size())
                    {
                        if (ans[s1]->data < anss[s2]->data)
                        {
                            s1++;
                        }
                        else if (ans[s1]->data > anss[s2]->data)
                        {
                            s2++;
                        }
                        else if (ans[s1]->data == anss[s2]->data)
                        {
                            finalAns.push_back(ans[s1]);
                            s2++;
                            s1++;
                        }
                    }
                }
                else if (andOr == '|')
                {
                    cout << "or";
                    int s1 = 0, s2 = 0;
                    while (s1 < ans.size() && s2 < anss.size())
                    {
                        if (ans[s1] < ans[s2])
                        {
                            finalAns.push_back(ans[s1]);
                            s1++;
                        }
                        else if (ans[s1] > ans[s2])
                        {
                            finalAns.push_back(anss[s2]);
                            s2++;
                        }
                        else if (ans[s1] > ans[s2])
                        {
                            finalAns.push_back(ans[s1]);
                            s2++;
                            s1++;
                        }
                    }
                    while (s1 < ans.size() - 1)
                    {
                        finalAns.push_back(ans[s1]);
                        s1++;
                    }
                    while (s2 < anss.size() - 1)
                    {
                        finalAns.push_back(anss[s2]);
                        s2++;
                    }
                }
                for (int k = 0; k < finalAns.size(); k++)
                {
                    tables[t]->dlt(finalAns[k]);
                }
            }
            //------------------------------------------
            else
            {
                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                {
                    // cout<<"."+a+"."+tables[t]->fieldsNmae[s]+".\n";
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                }
                // cout<<"here\n";
                char v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp.size(); j++)
                {
                    if (inp[j] != ' ' && inp[j] != ' ')
                        aa += inp[j];
                }
                vector<Node *> ansTD;
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> ans;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        ans.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    ans = srt(ans);
                }
                for (int k = 0; k < ans.size(); k++)
                {
                    // cout<< "ok\n";
                    tables[t]->dlt(ans[k]);
                }

                // a="";
                // while(inp[j]!='<' && inp[j]!='>' && inp[j]!= '=')
                // {
                //     a+=inp[j];
                //     j++;
                // }
                // for(s=0 ; s < tables[t]->fieldsNmae.size() ; s++)
                //     if (tables[t]->fieldsNmae[s] == a) break;

                // j++;
                // for(j ; j< inp.size() ;j++)
                //     aa+=inp[j];
                // vector<Node*> ansTD;
                // if (inp[j]=='<')
                //     ansTD =tables[t]->fields[s]->LS(changeTI(aa , s , tables[t]));
                // if (inp[j]=='>')
                //     ansTD =tables[t]->fields[s]->BT(changeTI(aa , s , tables[t]));
                // if (inp[j]=='=')
                // {
                //     ll p = changeTI(aa , s , tables[t]);
                //     ansTD =tables[t]->fields[s]->AND(p,p);
                //     j++;
                // }
                // if(ansTD.size())
                // {

                //     vector<Node*>ans;
                //     for(int k=0 ; k < ansTD.size() ; k++)
                //         ans.push_back(tables[t]->getId(ansTD[k] , s));
                //     srt(ans);
                //     for(int k = 0 ; k < ans.size() ; k++)
                //     {
                //         tables[t]->dlt(ans[k]);
                //     }
                // }

                // cout<<"end of delete\n";
            }
        }

        else if (inp[0] == 'S')
        {
            int s;
            vector<int> flds;
            int j = 0;
            string a = "", aa = "";
            for (j = 7; inp[j] != ')' && inp[j] != '*'; j++)
            {
                if ((inp[j] >= 'a' && inp[j] <= 'z') || inp[j] == ',')
                    a += inp[j];
            }
            j += 6;
            while (inp[j] == ' ')
                j++;
            for (j; inp[j] != ' '; j++)
            {
                if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] >= 'A' && inp[j] <= 'Z') || (inp[j] == '/'))
                    aa += inp[j];
            }
            int t = 0;
            while (tablesName[t] != aa)
                t++;
            string temp = "";
            if (a != "")
            {

                for (int h = 0; h < a.size(); h++)
                {
                    if (a[h] >= 'a' && a[h] <= 'z')
                    {
                        temp += a[h];
                    }
                    else
                    {
                        for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                            if (tables[t]->fieldsNmae[s] == temp)
                                break;
                        flds.push_back(s);
                        s = 0;
                        temp = "";
                    }
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                    if (tables[t]->fieldsNmae[s] == temp)
                        break;
                flds.push_back(s);
            }
            j += 6;

            //--------------------------------------------------------
            bool chek = false;
            for (int k = j; k < inp.size(); k++)
            {
                if (inp[k] == '&' || inp[k] == '|')
                {
                    chek = true;
                    break;
                }
            }
            if (chek)
            {
                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                    {
                        a += inp[j];
                    }
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                {
                    // cout<<"."+tables[t]->fieldsNmae[s]+"."+a+".\n";
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                }
                char v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp[j] != '&' && inp[j] != '|'; j++)
                {
                    if (inp[j] == '&' || inp[j] == '|')
                        break;
                    aa += inp[j];
                }

                vector<Node *> ansTD;
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                {
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                    // cout<<"here\n";
                }
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> ans;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        ans.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    ans = srt(ans);
                }
                char andOr = inp[j];
                j++;
                //===========================

                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                    {
                        a += inp[j];
                    }
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp.size(); j++)
                {
                    if (inp[j] != ' ' && inp[j] != ')')
                        aa += inp[j];
                }
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> anss;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        anss.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    anss = srt(anss);
                }
                // for (int m = 0 ; m <anss.size() ;m++ )
                // {
                //     cout<<anss[m]->data << "    " <<anss[m]->nextField->nextField->nextField->data<< "\n";
                // }

                vector<Node *> finalAns;
                if (andOr == '&')
                {
                    cout << "and\n";
                    int s1 = 0, s2 = 0;
                    while (s1 < ans.size() && s2 < anss.size())
                    {
                        if (ans[s1]->data < anss[s2]->data)
                        {
                            s1++;
                        }
                        else if (ans[s1]->data > anss[s2]->data)
                        {
                            s2++;
                        }
                        else if (ans[s1]->data == anss[s2]->data)
                        {
                            finalAns.push_back(ans[s1]);
                            s2++;
                            s1++;
                        }
                    }
                }
                else if (andOr == '|')
                {
                    cout << "or\n";
                    int s1 = 0, s2 = 0;
                    while (s1 < ans.size() && s2 < anss.size())
                    {
                        if (ans[s1] < anss[s2])
                        {
                            finalAns.push_back(ans[s1]);
                            s1++;
                        }
                        else if (ans[s1] > anss[s2])
                        {
                            finalAns.push_back(anss[s2]);
                            s2++;
                        }
                        else if (ans[s1] == anss[s2])
                        {
                            finalAns.push_back(ans[s1]);
                            s2++;
                            s1++;
                        }
                    }
                    while (s1 < ans.size())
                    {
                        finalAns.push_back(ans[s1]);
                        s1++;
                    }
                    while (s2 < anss.size())
                    {
                        finalAns.push_back(anss[s2]);
                        s2++;
                    }
                }
                for (int k = 0; k < finalAns.size(); k++)
                {
                    vector<ll> AFS = (tables[t]->output(finalAns[k]));
                    for (int h = 0; h < AFS.size(); h++)
                    {
                        if (flds.size() == 0)
                        {
                            // cout<<"\nAFS  :  "<<AFS[h]<<endl;
                            cout << changeTS(AFS[h], h, tables[t]) << " ";
                            // cout << AFS[h]<<" ";
                        }
                        else
                        {
                            for (int m = 0; m < flds.size(); m++)
                            {
                                if (flds[m] == h)
                                {
                                    cout << changeTS(AFS[h], h, tables[t]) << " ";
                                    // cout << AFS[h]<<" ";
                                }
                            }
                        }
                    }
                    cout << endl;
                }
            }
            // //------------------------------------------
            else
            {
                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                    {
                        a += inp[j];
                    }
                    j++;
                }
                // cout<<a<<endl;
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                {
                    // cout<<"."+tables[t]->fieldsNmae[s]+"."+a+".\n";
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                }
                char v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp.size(); j++)
                {
                    if (inp[j] != ' ' && inp[j] != ' ')
                        aa += inp[j];
                }
                vector<Node *> ansTD;
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> ans;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        ans.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    ans = srt(ans);
                }
                for (int k = 0; k < ans.size(); k++)
                {
                    // cout<<"from table :" << tablesName[t] << " : \n";
                    vector<ll> AFS = (tables[t]->output(ans[k]));
                    for (int h = 0; h < AFS.size(); h++)
                    {
                        if (flds.size() == 0)
                        {
                            // cout<<"\nAFS  :  "<<AFS[h]<<endl;
                            cout << changeTS(AFS[h], h, tables[t]) << " ";
                            // cout << AFS[h]<<" ";
                        }
                        else
                        {
                            for (int m = 0; m < flds.size(); m++)
                            {
                                if (flds[m] == h)
                                {
                                    cout << changeTS(AFS[h], h, tables[t]) << " ";
                                    // cout << AFS[h]<<" ";
                                }
                            }
                        }
                    }
                    cout << endl;
                }
            }
            // cout<<"end of select \n";
        }

        else if (inp[0] == 'U')
        {
            // cout<<"updating:\n";
            int s, ss;
            string a = "", aa = "";
            for (j = 7; inp[j] != ' '; j++)
            {
                if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] >= 'A' && inp[j] <= 'Z') || (inp[j] == '/'))
                    a += inp[j];
            }
            int t = 0;
            while (tablesName[t] != a)
            {
                // cout<<t<<endl;
                t++;
            }
            while (inp[j] != '(')
                j++;
            vector<ll> ins;
            int counter = 1;
            a = "";
            for (j; j <= inp.size(); j++)
            {
                if (inp[j] != ',' && inp[j] != ')')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                    // cout<<"."+tablesName[t]+"."+a+".\n";
                }
                else
                {
                    ins.push_back(changeTI(a, counter, tables[t]));
                    counter++;
                    a = "";
                }
                if (inp[j] == ')')
                    break;
            }
            while (inp[j] != 'E')
            {
                j++;
            }
            j += 3;

            //--------------------------------------------------------
            bool chek = false;
            for (int k = j; k < inp.size(); k++)
            {
                if (inp[k] == '&' || inp[k] == '|')
                {
                    chek = true;
                    break;
                }
            }

            if (chek)
            {
                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                char v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp[j] != '&' && inp[j] != '|'; j++)
                {
                    if (inp[j] == '&' || inp[j] == '|')
                        break;
                    aa += inp[j];
                }
                vector<Node *> ansTD;
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> ans;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        ans.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    ans = srt(ans);
                }
                char andOr = inp[j];
                j++;
                //===========================

                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp.size(); j++)
                {
                    if (inp[j] != ' ' && inp[j] != ')')
                        aa += inp[j];
                }
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> anss;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        anss.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    anss = srt(anss);
                }
                vector<Node *> finalAns;
                if (andOr == '&')
                {
                    cout << "and\n";
                    int s1 = 0, s2 = 0;
                    while (s1 < ans.size() && s2 < anss.size())
                    {
                        if (ans[s1]->data < anss[s2]->data)
                        {
                            s1++;
                        }
                        else if (ans[s1]->data > anss[s2]->data)
                        {
                            s2++;
                        }
                        else if (ans[s1]->data == anss[s2]->data)
                        {
                            finalAns.push_back(ans[s1]);
                            s2++;
                            s1++;
                        }
                    }
                }
                else if (andOr == '|')
                {
                    cout << "or\n";
                    int s1 = 0, s2 = 0;
                    while (s1 < ans.size() && s2 < anss.size())
                    {
                        if (ans[s1] < anss[s2])
                        {
                            finalAns.push_back(ans[s1]);
                            s1++;
                        }
                        else if (ans[s1] > anss[s2])
                        {
                            finalAns.push_back(anss[s2]);
                            s2++;
                        }
                        else if (ans[s1] > ans[s2])
                        {
                            finalAns.push_back(ans[s1]);
                            s2++;
                            s1++;
                        }
                    }
                    while (s1 < ans.size())
                    {
                        finalAns.push_back(ans[s1]);
                        s1++;
                    }
                    while (s2 < anss.size())
                    {
                        finalAns.push_back(anss[s2]);
                        s2++;
                    }
                }
                for (int m = 0; m < finalAns.size(); m++)
                {
                    tables[t]->update(finalAns[m], ins);
                }
            }
            //------------------------------------------
            else
            {
                a = "", aa = "";
                while (inp[j] != '<' && inp[j] != '>' && inp[j] != '=')
                {
                    if ((inp[j] >= 'a' && inp[j] <= 'z') || (inp[j] >= '0' && inp[j] <= '9') || (inp[j] == '/'))
                        a += inp[j];
                    j++;
                }
                for (s = 0; s < tables[t]->fieldsNmae.size(); s++)
                    if (tables[t]->fieldsNmae[s] == a)
                        break;
                char v = inp[j];
                j++;
                if (inp[j] == '=')
                    j++;

                for (j; j < inp.size(); j++)
                {
                    if (inp[j] != ' ' && inp[j] != ' ')
                        aa += inp[j];
                }
                vector<Node *> ansTD;
                if (v == '<')
                {
                    ansTD = tables[t]->fields[s]->LS(changeTI(aa, s, tables[t]));
                }
                if (v == '>')
                    ansTD = tables[t]->fields[s]->BT(changeTI(aa, s, tables[t]));
                if (v == '=')
                {
                    ll p = changeTI(aa, s, tables[t]);
                    // cout<<"-- "<<p<<" -- "<<changeTI("lale4" ,s, tables[t])<<endl;
                    ansTD = tables[t]->fields[s]->AND(p, p);
                }
                vector<Node *> ans;
                if (ansTD.size() != 0)
                {
                    for (int k = 0; k < ansTD.size(); k++)
                    {
                        ans.push_back(tables[t]->getId(ansTD[k], s));
                    }
                    ans = srt(ans);
                }
                // for (int m = 0 ; m <ans.size() ;m++ )
                // {
                //     cout<<ans[m]->data << "    " <<ans[m]->nextField->nextField->nextField->data<< "\n";
                // }
                vector<ll> iid;

                for (int m = 0; m < ans.size(); m++)
                {
                    if (ans[m]->data != 0)
                    {
                        tables[t]->update(ans[m], ins);
                    }
                }
            }

            // cout<<"endof update\n";
        }
    }
    //  cout<<"***************finish**************";

    return 0;
}
