#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;



void firstPass(ifstream& infile) {
	cout << "firstPass" << endl;
	while (!infile.eof()) {
		string line;
		getline(infile, line);	// store next line into s
		//cout << s << endl;

		char token[50];
		char *tokenParser;

		// convert string to C-string
		char *xline = new char[line.length() + 1];
		strcpy(xline, line.c_str());

		// use strtok and delimitter " " to parse through each line
		tokenParser = strtok(xline, " ");
		printf("%s ", tokenParser);	// read the first char of the line

		/*
		while (tokenParser != NULL){
			printf ("%s ",tokenParser);


			tokenParser = strtok (NULL, " ");
		}
		*/
		cout << endl;


	}
	printf("\n");
}

int main() {

	cout << "Enter file name: ";
	char filename[50];
	ifstream infile;
	//cin.getline(filename,50);
	infile.open("input.txt");		// change input to infile

	if (infile.is_open()) {
		cout << "yes" << endl;
		firstPass(infile);


	}
	else {
		cout << "Exception: File Does Not Exist!" << endl;
	}

	infile.close();
	system("pause");

	return 0;
}