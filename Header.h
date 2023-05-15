#ifndef _HEADER_H_
#define _HEADER_H


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

struct Node {
	string data;
	Node* ptr;
};

struct Stack {
	Node* head;
	Node* tail;
};

void Init(Stack& L);

void Pop(Stack& L);

string Top(Stack& L);

void Push(Stack& L, string word);

bool IsEmpty(Stack L);

Node* createNode(string word);

int32_t CheckFile(string expression);

int32_t OperandOrNot(string word);

int32_t OrderOfOperations(char token);

string ConvertInfixToPostfix(string infix);

bool IsMathOperator(char token);

string GetOperand(string expression, int& i);

string calculateValue(string b, string operators, string a);

double calculateExpression(string expression);

void ReadFileInfix(ifstream& fi, string& expression);

void WriteFileResult(ofstream& fo, string expression);

#endif // !_HEADER_H_