/*--------------------------------*-------*----------------------------------*\
  Sistemas Operacionais I         | Felipe Franco
  Proto-Terminal  		  | Fernando Neves
				  | Marcos Paulo Lopes
				  | Thailsson Clementino
\*---------------------------------------------------------------------------*/

#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<sstream>
#include "./header/commands.h"

using namespace std;

//Map to store the function pointers
map<string,void(*)(char(*))> mapa;
set<char> possible_delimiters,special_characters;
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

char balance(const char* a, char del=0) {
    int i = 0;
    while(a[i]!=0) {
        if(!del) {
            if((i==0 || a[i-1]!='\\') && possible_delimiters.count(a[i])) del=a[i];
        }
        else {
            if((i==0 || a[i-1]!='\\') && a[i]==del) del=0;
        }
        i++;
    } 
    return del;
}

string clean_backwards(string a) {
    string cleaned="";
    for(int i = a.size()-1;i>=0;i--) {
        if((i==0 || a[i-1]!='\\') && special_characters.count(a[i]));
        else cleaned = a[i]+cleaned;
    } 
    return cleaned;
}

int main(int argc, char *argv[]){
	
	//Define Functions here	
	mapa["ls"] = &ls;
	mapa["cd"] = &cd;
	mapa["pwd"] = &pwd;	
	
	//Strings
	string currCommand;

    //Defining delimiters
    possible_delimiters.insert('\'');
    possible_delimiters.insert('"');

    //Defining escapable special characters
    special_characters.insert('\\');
    special_characters.insert('\'');
    special_characters.insert('"');


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

        do {
			string word;
			ss >> word;

            char delimiter=balance(word.c_str());
            while(delimiter) {
                if(!ss) {
                    cout << "> ";
                    getline(cin,currCommand);
                    ss.clear();
                    ss.str(currCommand);
                } 
                string next_word;
                ss >> next_word;
                delimiter=balance(next_word.c_str(),delimiter);
                word=word+" "+next_word;
            }

			command.push_back(clean_backwards(word));
            cout << command[command.size()-1] << endl;
		} while(ss);	
		
		//Call the function that treat the string and run the command
		runCommand(command);
	}
}
