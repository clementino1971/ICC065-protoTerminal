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
#include "./header/commands.h"

using namespace std;

//Map to store the function pointers
map<string,void(*)(char(*))> mapa;
bool TERMINAL = true;
char dir[FILENAME_MAX];

void runCommand(vector<string> command){
	
	//Close the terminal
	if(command[0] == "quit"){
		TERMINAL = false;
		return;
	}

	//run special functions
	if(mapa.find(command[0]) != mapa.end()){
		void (*choice)(char(*));
		choice = mapa[command[0]];
		choice(dir);
	}else{

		//Treat Here the | and &
		run(command);
	}

	return;

}

int main(int argc, char *argv[]){
	
	//Define Functions here	
	mapa["ls"] = &ls;
	mapa["cd"] = &cd;
	mapa["pwd"] = &pwd;	
	
	//Strings
	string currCommand;


	while(TERMINAL){
		
		//Get current dir
		getcwd(dir,sizeof(dir));

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
