#include"Header.h"


Node* createNode(string word){
	Node* p = new Node;
	p->data = word;
	p->ptr = NULL;
	return p;
}

void Init(Stack& L){
	L.head = NULL;
	L.tail = NULL;
}

bool IsEmpty(Stack L) {
	if (L.head == L.tail && L.head == nullptr) {
		return 1;
	}
	
	return 0;
}

void Push(Stack& L, string word){
	Node* p = createNode(word);
	if (IsEmpty(L) == 1)
	{
		L.head = p;
		L.tail = L.head;
	}
	else
	{
		L.tail->ptr = p;
		L.tail = p;
	}
}

void Pop(Stack& L){
	if (L.head == L.tail){
		delete L.head;
		L.head = nullptr;
		L.tail = nullptr;
	}
	else
	{
		Node* p = L.head;
		while (p->ptr != L.tail)
		{
			p = p->ptr;
		}
		delete L.tail;
		L.tail = nullptr;
		L.tail = p;
	}
}

string Top(Stack& L){
	return L.tail->data;
}

int32_t CheckFile(string expression) {
	int32_t Prekey = -2;
	int32_t openparenthesis = 0;
	int32_t closeparenthesis = 0;
	for (int32_t i = 0; i < expression.size(); i++){
		string word = "";
		while (i < expression.size() && expression[i] != ' '){
			word += expression[i];
			i++;
		}

		int32_t key = OperandOrNot(word);
		if (Prekey == -2 && key == 0) return 0; // Operators can't appear at the beginning of the expression
		if (key == -1) return -1; // check if there is any letter in the expression
		if (Prekey == key && key != 1) // if there are 2 operands or 2 operators next to each other 
			return -2;
		else
		{
			Prekey = key;
		}
		if (expression[0] != '(' && key == 1) return -3; // format error
		if (expression[i] == ')') openparenthesis++;
		if (expression[i] == '(') closeparenthesis++;
		if (expression[i] == ')') {
			if (openparenthesis > closeparenthesis) return -4;  // format error
		}
	}

	Stack L;
	Init(L);

	for (int32_t i = 0; i < expression.size(); i++){
		string sub = "";
		if (expression[i] == '(')
		{
			sub += expression[i];
			Push(L, sub);
		}
		else if (expression[i] == ')')
		{
			if (IsEmpty(L) == 1)
				return -5;
			else
				Pop(L);
		}
	}

	if (openparenthesis != closeparenthesis) return -6; // format error


	return 1;
}

int32_t OperandOrNot(string word) // using to check if the word is an operand or an operator
{
	if (word == "*" || word == "/" || word == "%" || word == "+" || word == "-" || word == "^")
		return 0;
	else if (word == "(" || word == ")")
		return 1;
	else
	{
		for (int i = 0; i < word.size(); i++)
		{
			if ((word[i] < '0' || word[i] > '9') && word[i] != '-' && word[i] != '.')
				return -1;
		}
		return 2;
	}
}

int32_t OrderOfOperations(char token)
{// this function returns the priority of each math operator
	int priority = 0;
	switch (tolower(token)){
	case '^':
		priority = 4;
		break;
	case '*': case '/': case '%':
		priority = 3;
		break;
	case '-':
		priority = 2;
		break;
	case '+':
		priority = 1;
		break;
	}
	return priority;
}

bool IsMathOperator(char token){// this function checks if operand is a math operator
	switch (tolower(token)){
	case '+': case '-': case '*': case '/':
	case '%': case '^': case '$': case 'c':
	case 's': case 't':
		return true;
		break;
	default:
		return false;
		break;
	}
}

string ConvertInfixToPostfix(string infix) {

	string postfix="";
	Stack charStack;

	Init(charStack);

	char token=' ';
	// remove all whitespace from the string
	infix.erase(std::remove_if(infix.begin(), infix.end(), [](char c) {
		return std::isspace(static_cast<unsigned char>(c));
		}), infix.end());

	// automatically convert negative numbers to have the ~ symbol
	for (unsigned x = 0; x < infix.length(); ++x) {
		token = infix[x];
		if (infix[x] != '-') {
			continue;
		}
		else if (x + 1 < infix.length() && IsMathOperator(infix[x + 1])) {
			continue;
		}
		if (x == 0 || infix[x - 1] == '(' || IsMathOperator(infix[x - 1])) {
			infix[x] = '~';
		}
	}

	for (unsigned x = 0; x < infix.length(); ++x)
	{
		if ((isdigit(infix[x])) || (infix[x] == '.') || (infix[x] == '~'))
		{
			postfix += infix[x];
		}
		else if (isspace(infix[x]))
		{
			continue;
		}
		else if (IsMathOperator(infix[x]))
		{
			postfix += " ";
			while ((!IsEmpty(charStack)) &&
				(OrderOfOperations(token) >= OrderOfOperations(infix[x])))
			{

				postfix += Top(charStack);
				Pop(charStack);
			}
			// push the remaining math operator onto the stack
			Push(charStack,&infix[x]);
		}
		// push outer parentheses onto stack
		else if (infix[x] == '(')
		{
			Push(charStack, &infix[x]);
		}
		else if (infix[x] == ')')
		{
			// pop the current math operator from the stack
			while ((!IsEmpty(charStack)) && (Top(charStack) != "("))
			{
				// place the math operator onto the postfix string
				postfix += Top(charStack);
				// pop the next operator from the stack and
				// continue the process until complete
				Pop(charStack);
			}

			if (!IsEmpty(charStack)) // pop '(' symbol off the stack
			{
				Pop(charStack);
			}
			else // no matching '('
			{
				cout << "\nPARENTHESES MISMATCH #1\n";
				return "-1";
			}
		}
		else
		{
			cout << "\nINVALID INPUT #1\n";
			//exit(1);
			return "-1";
		}
	}

	// place any remaining math operators from the stack onto
	// the postfix array
	while (!IsEmpty(charStack)){
		postfix += Top(charStack);;
		Pop(charStack);
	}

	return postfix;
}

string GetOperand(string expression, int& i){
	string operand = "";
	if (expression[i] == '-')
	{
		operand += expression[i];
		i++;
	}
	while ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.')
	{
		operand += expression[i];
		i++;
		if (i == expression.length()) break;
	}
	return operand;
}

string calculateValue(string operand2, string operators, string operand1) {
	double Result = 0.0;

	if (operators == "^"){
		Result = 1;
		Result = pow(atof(operand2.c_str()), (int)atoi(operand1.c_str()));
	}
	else if (operators == "%"){
		Result = (int32_t)atof(operand2.c_str()) % (int32_t)atof(operand1.c_str());
	}
	else if (operators == "*"){
		Result = atof(operand2.c_str()) * atof(operand1.c_str());
	}
	else if (operators == "/"){
		Result = atof(operand2.c_str()) / atof(operand1.c_str());
	}
	else if (operators == "+") {
		Result = atof(operand2.c_str()) + atof(operand1.c_str());
	}
	else if (operators == "-"){
		Result = atof(operand2.c_str()) - atof(operand1.c_str());
	}

	return to_string(Result);
}

double calculateExpression(string expression){

	Stack Operands;
	Stack Operators;

	Init(Operands);
	Init(Operators);

	for (int32_t i = 0; i < expression.length(); i++){
		if ((expression[i] >= '0' && expression[i] <= '9') ||
			(expression[i] == '-' && (expression[i + 1] >= '0' && expression[i + 1] <= '9')))
			// Operand can be negative or positive 
		{
			string operand = GetOperand(expression, i);
			Push(Operands, operand);
			i--;
		}
		else if (expression[i] != ' '){
			string operators = "";
			if (expression[i] == '(')
			{
				operators += expression[i];
				Push(Operators, operators);
			}
			else if (expression[i] == ')')
			{
				while (Top(Operators) != "(")
				{
					string operands1 = Top(Operands);
					Pop(Operands);

					string operands2 = Top(Operands);
					Pop(Operands);

					operators = Top(Operators);
					Pop(Operators);

					Push(Operands, calculateValue(operands2, operators, operands1));
				}

				Pop(Operators);
			}
			else
			{
				string operators = "";
				if (!IsEmpty(Operators) && OrderOfOperations(expression[i]) <= OrderOfOperations(Top(Operators)[0])){
					while (!IsEmpty(Operators) && OrderOfOperations(expression[i]) <= OrderOfOperations(Top(Operators)[0])){
						string operands1 = Top(Operands);
						Pop(Operands);

						string operands2 = Top(Operands);
						Pop(Operands);

						operators = Top(Operators);
						Pop(Operators);

						Push(Operands, calculateValue(operands2, operators, operands1));
					}
					operators = "";
					operators += expression[i];
					Push(Operators, operators);
				}
				else{
					operators += expression[i];
					Push(Operators, operators);
				}
			}
		}
	}
	
	string operators = "";
	while (!IsEmpty(Operators)){
		string operands1 = Top(Operands);
		Pop(Operands);

		string operands2 = Top(Operands);
		Pop(Operands);

		operators = Top(Operators);
		Pop(Operators);

		Push(Operands, calculateValue(operands2, operators, operands1));
	}

	double Result = atof(Top(Operands).c_str());
	Pop(Operands);
	return Result;
}

void ReadFileInfix(ifstream &fi, string &expression){
	while (!fi.eof()) {
		getline(fi, expression);
	}
}

void WriteFileResult(ofstream& fo, string expression) {

	int32_t check = CheckFile(expression);
	
	if (check == 0) {
		fo << "0" << endl;
		fo << "Operators can't appear at the beginning of the expression" << endl;
	}
	else if (check == -1) {
		fo << "0" << endl;
		fo << "There is non-numeric in the expression" << endl;
	}
	else if (check == -2) {
		fo << "0" << endl;
		fo << "There are 2 operands or 2 operators next to each other" << endl;
	}
	else if (check == -3) {
		fo << "0" << endl;
		fo << "Format error" << endl;	
	}
	else if (check == -4) {
		fo << "0" << endl;
		fo << "Format error" << endl;
	}
	else if (check == -5) {
		fo << "0" << endl;
		fo << "Unbalanced parentheses expression " << endl;
	}
	else if (check == -6) {
		fo << "0" << endl;
		fo << "Format error" << endl;
	} else{
		fo << "1" << endl;
		fo << calculateExpression(expression) << endl;
	}
}