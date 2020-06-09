/*--------------------------------*-------*----------------------------------*\
  Sistemas Operacionais I         | Felipe Franco
  Proto-Terminal  		  | Fernando Neves
				  | Marcos Paulo Lopes
				  | Thailsson Clementino
\*---------------------------------------------------------------------------*/

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<sstream>

using namespace std;

//Map to store the function pointers
map<string,void(*)()> mapa;
bool TERMINAL = true;

void runCommand(vector<string> command){
	
	//Close the terminal
	if(command[0] == "quit"){
		TERMINAL = false;
		return;
	}

	//run special functions
	if(mapa.find(command[0]) != mapa.end()){
		void (*choice)();
		choice = mapa[command[0]];
		choice();
	}else{
		//run others functions
	}

	return;

}

int main(int argc, char *argv[]){
	
	//Define Functions here	
	//mapa["ls"] = 
	//mapa["cd"] = 
	//mapa["pwd"] =	
	
	//Strings
	string currCommand;
	string dir = "~/";


	while(TERMINAL){
		
		//Vector to store the words in a command
		vector<string> command;

		//A print because is nice
		cout << dir << "> ";
		
		// Readind the command and put the words in vector
		getline(cin, currCommand);
		istringstream ss(currCommand);

	       	do{
			string word;
			ss >> word;

			command.push_back(word);
		}while(ss);	
		
		//Call the function that treat the string and run the command
		runCommand(command);
	}
}
