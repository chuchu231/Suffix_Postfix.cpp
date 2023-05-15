// fit@hcmus
// Nguyen Le Thuong
// 21120145
// 21CTT2

#include "Header.h"

int main() {

	string Postfix = "";
	string expression = "";
	ifstream fi;
	ofstream fo;

	fi.open("infix.txt");
	fo.open("result.txt");

	if (!fi.is_open()) {
		cout << "Can't open file infix.txt !" << endl;
	} else{

		ReadFileInfix(fi, expression);
		cout << "Infix: " << expression << endl;
		
		Postfix = ConvertInfixToPostfix(expression);
		if (Postfix!="-1") {
			cout << "Postfix: " << Postfix << endl;
			cout << "Equal: " << calculateExpression(expression) << endl;
		}
		else {
			cout << "Can't convert infix to postfix !\n";
		}

	}

	if (!fo.is_open()) {
		cout << "Can't create this file !" << endl;
	}
	else {
		Postfix = ConvertInfixToPostfix(expression);
		if (Postfix != "-1") {
			WriteFileResult(fo, expression);
			cout << "Writing in file result.txt is successful\n";
		}
		else {
			fo << "Can't convert infix to postfix !\n";
		}
	}
	fi.close();
	fo.close();
	
	return 0;
}