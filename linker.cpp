#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

bool ERROR = false;
int ModuleIndex = 0;
int globalOffset = 0;

typedef struct Modules{
	int offset;
	char **symbolList;
	int * symbolValList;

} ModuleS;
struct Modules *ModuleList; 
// declare Module to be initialized in main()




void firstPass(ifstream& infile) {
	cout << "firstPass" << endl;
	int lineNumber = 0; // ERROR, track line number for error reporting

	int TEST = 1;
	while (!infile.eof()) {
		string line1, line2, line3;
		getline(infile, line1);	// store first line into line1 => definition list
		getline(infile, line2); // use list
		getline(infile, line3); // program text
		int charoffset = 0;	// ERROR, track char offset

		ModuleList[ModuleIndex].offset = globalOffset;	// set module offset to current global offset

		/*--------------------HANDLE DEFINITIONS------------------------*/

		// convert string to C-string to make strcpy work
		char *xline = new char[line1.length() + 1];
		strcpy(xline, line1.c_str());

		// use strtok and delimitter " " to parse through each line
		char *token;

		token = strtok(xline, " ");
		printf("%s ", token);	// read the first char of the line
		int defcount = atoi(token);	// convert first token to definition count

		token = strtok (NULL, " ");

		char **symbol;	// create temporary list to store symbols. ** for pointer to array of char (i.e.) string
		symbol = (char **)malloc(sizeof(char*)*defcount);
		int k;
		
		
		for (k=0; k<defcount; k++){		// initilize c-string memory malloc for each symbol element
			symbol[k] = (char *)malloc(sizeof(char)*10);
		}
		
		
		int *symValue;	// initilize dynamic array of symbol values
		symValue = (int *)malloc(sizeof(int)*defcount);
		
		int i = 0;
		int j = 0;
		while (token != NULL){
			//printf ("%s ",token);
			char *tokencpy = " ";

			tokencpy = strdup(token); // make a copy of the string
			//strcat(tokencpy, "\0");
			
			symbol[i++] = tokencpy;	// add to symbol list
			
			printf("%s ",symbol[i-1]);
			//cout << "strlen: "<< strlen(symbol[i-1]);

			token = strtok (NULL, " "); // next token

			if (!isdigit(*token)){
				cout << "not integer";
				break;
			}
			symValue[j++] = atoi(token) + ModuleList->offset;	// add absolute address to symValue list
			token = strtok (NULL, " ");
		}
		
		// ERROR handling
		if (i < defcount){
			printf("ERROR: Not enough symbols in declaration");
			ERROR = true;
		}
		else if (i > defcount){
		}
		else{

		}

		//ModuleList[ModuleIndex].symbolList = (char **)malloc(sizeof(char*)*defcount);
		//ModuleList[ModuleIndex].symbolValList = (int *)malloc(sizeof(int)*defcount);

		//ModuleList[ModuleIndex].symbolList = symbol;
		//ModuleList[ModuleIndex].symbolValList = symValue;
		cout << "test" << ModuleIndex << endl;
		//printf("%s ",symbol[0]);

		ModuleIndex++;

		free(symbol);
		free(symValue);
		free(token);
		free(xline);

		/*----------------------MODULE OFFSETS-----------------------------*/
		/*
		// convert string to C-string to make strcpy work
		
		char *xline3 = new char[line3.length() + 1];
		strcpy(xline3, line3.c_str());
		
		// use strtok and delimitter " " to parse through each line
		char *token3;
		token3 = strtok(xline3, " ");
		
		printf("%s ", token3);	// read the first char of the line
		int instructcount = atoi(token3);	// convert first token to definition count
		
		token3 = strtok (NULL, " ");

		char **operand;	// create temporary list to store symbols. ** for pointer to array of char (i.e.) string
		operand = (char **)malloc(sizeof(char*)*instructcount);
		int *opNum;
		opNum = (int *)malloc(sizeof(int)*instructcount);
		
		i=0;
		j=0;
		int localOffset = 0;	// keep track of local offset in each module. To be used in module offset
		while (token3 != NULL){
			char *tokencpy = " ";
			tokencpy = strdup(token3);
			operand[i++] = tokencpy;

			token3 = strtok (NULL, " ");

			if (!isdigit(*token3)){
				cout << "not integer";
				break;
			}
			opNum[j++] = atoi(token3);	// add to opNum list

			token3 = strtok (NULL, " ");
			localOffset++;
		}
		globalOffset = localOffset;	// set global offset to total local offset

		*/
		
		cout << endl;





	}
	printf("\n");
}

int main() {
	// initialize Module List
	ModuleList = (ModuleS*)malloc(sizeof(ModuleS));

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


	cout << "----------------------------------"<<endl;
	
	cout << "hi" <<endl;
	//cout << ModuleList[0].symbolList[0];
	/*
	int i;
	for (i=0; i<ModuleCount; i++){
		printf("%s: %d ",ModuleList->symbolList[i], ModuleList->symbolValList[i]);

	}
	*/

	infile.close();
	system("pause");

	return 0;
}