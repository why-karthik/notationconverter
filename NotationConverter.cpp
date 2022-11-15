//Student A: Sri Sai Koushik Yaganti, UID: U65258662
//Student B: Karthik Yechuri, UID: U51358914
#include <bits/stdc++.h>
#include "NotationConverter.hpp"
using namespace std;

bool dlinkeddeck ::checkinvchar(string inStr)
{
    for (unsigned int i = 0; i < inStr.length(); i++)
    {
        string s(1, inStr[i]);
        if (isOperand(inStr[i]))
        {
            continue;
        }
        else if (s == "(" || s == ")" || s == " ")
        {
            continue;
        }
        else if (s == "+" || s == "-" || s == "*" || s == "/")
        {
            continue;
        }
        else
        {
            
            return 1;
        }
    }
    return 0;
}

void dlinkeddeck ::insertFront(string &a)
{   //inserting at front
    Node *first = new Node();
    first->value = a;
    first->prev = NULL;
    first->next = head;
    if (head != NULL)
        head->prev = first;
    head = first;
}
void dlinkeddeck ::insertBack(string &b)
{   //inserting at the end
    Node *last = new Node();
    Node *p = head;
    last->value = b;
    last->next = NULL;
    if (p == NULL)
    {
        last->prev = NULL;
        p = last;
        return;
    }
    while (p->next != NULL)
        p = p->next;
    last->prev = p;
    p->next = last;
}
void dlinkeddeck ::removeFront()
{   //removing the first node
    if (head == NULL)
    {
        return;
    }
    if (head->next == NULL)
    {
        head = NULL;
        return;
    }
    head->next->prev = NULL;
    head = head->next;
}
void dlinkeddeck ::removeBack()
{   //removing the last node
    Node *p = head;
    if (p == NULL)
    {
        return;
    }
    if (p->next == NULL)
    {
        p = NULL;
        return;
    }
    while (p->next->next != NULL)
        p = p->next;
    p->next = NULL;
    free(p);
}
string dlinkeddeck ::getFront()
{   //accessing the data in first node
    string x = head->value;
    return x;
}
string dlinkeddeck ::getBack()
{   //accessing the data in last node
    Node *p = head;
    while (p->next != NULL)
        p = p->next;
    string x = p->value;
    return x;
}

bool dlinkeddeck ::isOperand(char x)
{   //checking if the passed value is an operand or not
    return (x >= 'a' && x <= 'z') ||
           (x >= 'A' && x <= 'Z');
}

string NotationConverter ::postfixToInfix(string inStr)
{
    if(checkinvchar(inStr) == 1){
        __throw_runtime_error("invalid string");//checking for invalid cases to throw
    }
    // string s;
    for (unsigned int i = 0; i < inStr.length(); i++)
    {
        string s(1, inStr[i]);
        if (isOperand(inStr[i]))
        {
            insertFront(s);
        }
        else if (s == " ")
        {
            continue;
        }
        else 
        {
            string y = "(";
            string x = (getFront());
            removeFront();
            string z = (getFront());
            removeFront();
            y.append(z + " ");
            y.append(s + " ");
            y.append(x);
            y.append(")");

            insertFront(y);//sending back to deck
        }
    }
    return getFront();
}
string NotationConverter ::infixToPostfix(string inStr)//describing the infixToPostfix() function
{
    if(checkinvchar(inStr) == 1){
        __throw_runtime_error("invalid string");
    }
    string out = "";
    for (unsigned int i = 0; i < inStr.length(); i++)
    {
        string s(1, inStr[i]);
        if (s == " ")//ignoring space
        {
            continue;
        }
        if (isOperand(inStr[i]))
        {

            out.append(s + " ");

            continue;
        }
        if (s == "+" || s == "-" || s == "*" || s == "/")
        {

            if (head == NULL)
            {
                insertFront(s);
            }
            else
            {
                insertFront(s);
            }
            continue;
        }
        if (s == "(")
        {
            insertFront(s);
        }
        else if (s == ")")//when s is equal to ), we add the first operator to the string and pop it along with the ( corresponding to the ).
        {
            out.append(getFront() + " ");
            removeFront();
            removeFront();
        }
    }
    return out;
};
string NotationConverter ::infixToPrefix(string inStr)
{
    if(checkinvchar(inStr) == 1){
        __throw_runtime_error("invalid string");
    }
    int n = inStr.length() - 1;// initializing a variable n for reversing the string
    for (int i = 0; i <= n; i++)
    {
        swap(inStr[i], inStr[n]);//reverse the string
        n = n - 1;
    }
    // cout<<inStr;
    for (unsigned int i = 0; i < inStr.length(); i++)
    {
        string s(1, inStr[i]);// replacing the ('s with )'s and vice versa in the reversed string 
        if (s == "(")
        {
            inStr[i] = ')';
        }
        else if (s == ")")
        {
            inStr[i] = '(';
        }
        else
        {
            continue;
        }
    }

    inStr = infixToPostfix(inStr);
    n = inStr.length() - 1;
    for (int i = 0; i <= n; i++)//reversing it again to get the prefix from the profix
    {
        swap(inStr[i], inStr[n]);
        n = n - 1;
    }
    return inStr;
}
string NotationConverter ::prefixToInfix(string inStr)//describing the prefixToInfix() function
{
    if(checkinvchar(inStr) == 1){
        __throw_runtime_error("invalid string");//checking for invalid cases to throw
    }
    int n = inStr.length() - 1;
    for (int i = 0; i <= n; i++)//reverse the string
    {
        swap(inStr[i], inStr[n]);
        n = n - 1;
    }
    // cout<<inStr;
    inStr = postfixToInfix(inStr);
    n = inStr.length() - 1;
    for (int i = 0; i <= n; i++)//reverse the string
    {
        swap(inStr[i], inStr[n]);
        n = n - 1;
    }

    for (unsigned int i = 0; i < inStr.length(); i++)
    {
        string s(1, inStr[i]);// replacing the ('s with )'s and vice versa in the reversed string 
        if (s == "(")
        {
            inStr[i] = ')';
        }
        else if (s == ")")
        {
            inStr[i] = '(';
        }
        else
        {
            continue;
        }
    }
    return inStr;
}
string NotationConverter ::prefixToPostfix(string inStr)//describing the prefixToPostfix function
{
    if(checkinvchar(inStr) == 1){
        __throw_runtime_error("invalid string");//checking for invalid cases to throw
    }
    inStr = prefixToInfix(inStr);
    inStr = infixToPostfix(inStr);
    return inStr;
}
string NotationConverter ::postfixToPrefix(string inStr)//describing the postfixToPrefix function
{
    if(checkinvchar(inStr) == 1){
        __throw_runtime_error("invalid string");//checking for invalid cases to throw
    }
    inStr = postfixToInfix(inStr);
    inStr = infixToPrefix(inStr);
    return inStr;
}
