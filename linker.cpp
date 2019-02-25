#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

#define MAX_DEF 16
#define MAX_SYMBOL 256


bool ERROR = false;
int ModuleIndex = 0;
int symbolIndex = 0;
int globalOffset = 0;

class Symbols{
public:
	char *symbol;
	int addr;

	Symbols(){
		symbol = "";
		addr = 0;
	}
	Symbols(char* insymbol, int* inaddr){
		symbol = insymbol;
		addr = *inaddr;
	}
};

class Instructions{
public:
	char instr;
	int opcode;
	Instructions(){
		instr = ' ';
		opcode = 0;
	}
};

class Modules{
public:
	static int ModuleCount;
	int offset;
	vector<Symbols> symbols;
	vector<Instructions> instructions;

	Modules(){
		offset = 0;
	}
};
int Modules::ModuleCount = 0;
/*
typedef struct Modules{
	int offset;
	Symbols *symbols;
	Instructions *instructions;
	char *typeList;
	int *opNum;

} ModuleS;
*/
//struct Modules *ModuleList; // declare Module to be initialized in main()

vector<Symbols> globalSymbol;	// create blobal dynamic list of symbols;
vector<Modules> ModuleList;



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

		//ModuleList[ModuleIndex].offset = globalOffset;	// set module offset to current global offset
		Modules localModule;
		localModule.offset = globalOffset;
		ModuleList.push_back(localModule);

		cout << "Module "<< Modules::ModuleCount <<endl;
	
		/*--------------------HANDLE DEFINITIONS------------------------*/
		
		
		// convert string to C-string to make strcpy work
		char *xline = new char[line1.length() + 1];
		strcpy(xline, line1.c_str());

		// use strtok and delimitter " " to parse through each line
		char *token;

		token = strtok(xline, " ");
		//printf("%s ", token);	// read the first char of the line
		int defcount = atoi(token);	// convert first token to definition count

		token = strtok (NULL, " ");
		
		//printf ("token: %s ",token);
		
		int localdefcount=0;
		
		
		while (token != NULL){
			//printf (" inloop: %s ",token);

			Symbols localSymb;

			char *tokencpy;
			tokencpy = strdup(token); // make a copy of the string
			localSymb.symbol = tokencpy;
			
			token = strtok (NULL, " "); // next token

			if (!isdigit(*token)){	// check if input is an integer
				cout << "not integer";
				break;
			}

			//localSymb.addr = atoi(token) + ModuleList[ModuleIndex].offset;	// add module index to symbol relative address

			token = strtok (NULL, " ");

			globalSymbol.push_back(localSymb);	// push symbol on global list

			symbolIndex++;
			localdefcount++;
		}
		
		
		
		// ERROR handling
		if (localdefcount < defcount){
			printf("ERROR: Not enough symbols in declaration\n");
			ERROR = true;
		}
		else if (localdefcount > defcount){
		}
		else{

		}
		
		free(token);
		free(xline);

		
		
		/*----------------------MODULE OFFSETS-----------------------------*/
		
		
		// convert string to C-string to make strcpy work
		
		char *xline3 = new char[line3.length() + 1];
		strcpy(xline3, line3.c_str());
		
		// use strtok and delimitter " " to parse through each line
		char *token3;
		token3 = strtok(xline3, " ");
		
		printf("%s ", token3);	// read the first char of the line
		int instructcount = atoi(token3);	// convert first token to definition count
		
		token3 = strtok (NULL, " ");

		/*
		char *type;	// create temporary list to store symbols. ** for pointer to array of char (i.e.) string
		type = (char *)malloc(sizeof(char)*instructcount);
	
		int *opNum;
		opNum = (int *)malloc(sizeof(int)*instructcount);
		*/
		
		int i=0;
		int j=0;
		while (token3 != NULL){
			Instructions localInstr;

			char *tokencpy;
			tokencpy = strdup(token3);

			printf("%c ", tokencpy[0]);

			if (isalpha(tokencpy[0]) && strlen(tokencpy) == 1){		//check if type is correct format
				//type[i++] = tokencpy[0];
				localInstr.instr = tokencpy[0];
			}
			else{
				printf( "ERROR - wrong operand\n");
				ERROR = true;
			}

			token3 = strtok (NULL, " ");
			printf(" %s ", token3);

			if (strlen(token3) != 4){
				cout << "incorrect intruction";
				break;
			}
			//opNum[j++] = atoi(token3);	// add to opNum list
			localInstr.opcode = atoi(token3);

			token3 = strtok (NULL, " ");

			
			localModule.instructions.push_back(localInstr);	// append local instruct to localModule

		}
		globalOffset += instructcount;

		
		//ModuleList[ModuleIndex].offset = globalOffset;
		ModuleList.at(Modules::ModuleCount).offset = globalOffset;
		
		//ModuleList[ModuleIndex].typeList = type;
		//ModuleList[ModuleIndex].opNum = opNum;
		//ModuleList[ModuleIndex]

		Modules::ModuleCount ++;

		free(token3);
		free(xline3);
		
		
		cout << endl;


		TEST++;
	}

	printf("\n");
}

int main() {
	// initialize Module List
	//ModuleList = (ModuleS*)malloc(sizeof(ModuleS));

	cout << "Enter file name: ";
	char filename[50];
	ifstream infile;
	//cin.getline(filename,50);
	infile.open("input.txt");		// change param to infile

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

	for (i=0; i<globalSymbol.size(); i++){
		//printf("%s: %d \n",symbol[i], symValue[i]);
		printf("%s: %d \n", globalSymbol.at(i).symbol, globalSymbol.at(i).addr);
	}

	/*
	for (i=0; i<ModuleList.size(); i++){
		printf("%c ", ModuleList.at(i).);
	}
	*/

	infile.close();
	system("pause");

	return 0;
}