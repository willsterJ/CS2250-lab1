#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

#define MAX_DEF 16
#define MAX_SYMBOL 256


bool ERROR = false;
int ModuleIndex = 0;
int symbolIndex = 0;
int globalOffset = 0;

typedef struct Modules{
	int offset;
	char **symbolList;
	int * symbolValList;

} ModuleS;
struct Modules *ModuleList; // declare Module to be initialized in main()
char **symbol;	// create  list to store symbols. ** for pointer to array of char (i.e.) string
int *symValue;	// initilize dynamic array of symbol values



void firstPass(ifstream& infile) {
	cout << "firstPass" << endl;
	int lineNumber = 0; // ERROR, track line number for error reporting

	int TEST = 1;
	while (!infile.eof() && TEST <= 5) {
		
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
		
		//printf ("token: %s ",token);
		
		int localdefcount=0;
		while (token != NULL){
			printf (" inloop: %s ",token);
			char *tokencpy;
			tokencpy = strdup(token); // make a copy of the string
			symbol[symbolIndex] = tokencpy;	// add to global symbol list

			token = strtok (NULL, " "); // next token

			if (!isdigit(*token)){	// check if input is an integer
				cout << "not integer";
				break;
			}
			symValue[symbolIndex] = atoi(token) + ModuleList[ModuleIndex].offset;	// add module index to symbol relative address
			
			token = strtok (NULL, " ");
			symbolIndex++;
			localdefcount++;
		}
		
		
		// ERROR handling
		if (localdefcount < defcount){
			printf("ERROR: Not enough symbols in declaration");
			ERROR = true;
		}
		else if (localdefcount > defcount){
		}
		else{

		}

		ModuleIndex++;
		
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




		TEST++;
	}

	printf("\n");
}

int main() {
	// initialize Module List
	ModuleList = (ModuleS*)malloc(sizeof(ModuleS));
	
	symbol = (char **)malloc(sizeof(char*)*MAX_DEF);
	int k;
	for (k=0; k<MAX_DEF; k++){		// initilize c-string memory malloc for each symbol element
		symbol[k] = (char *)malloc(sizeof(char)*10);
		symbol[k] = "empty";
	}
	symValue = (int *)malloc(sizeof(int)*MAX_DEF);
	

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
	
	printf("SYMBOL TABLE: \n");
	
	int i;
	for (i=0; i<symbolIndex; i++){
		printf("%s: %d \n",symbol[i], symValue[i]);
	}
	

	infile.close();
	system("pause");

	return 0;
}