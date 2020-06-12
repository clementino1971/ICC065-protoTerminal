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
map<string,void(*)(vector<string>)> mapa;
set<char> possible_delimiters,special_characters;
bool TERMINAL = true;
char dir[FILENAME_MAX];

void generate_file_name(char* filename, int size) {
    strcpy(filename,"/tmp/");
    for(int i = 5; i < size; i++) {
        filename[i]=rand()%26+'A';
    }
    filename[size]=0;
    return;
}

void runCommand(vector<string> command){
    if(command.empty()) return;
	
	//Close the terminal
	if(command[0] == "quit"){
		TERMINAL = false;
		return;
	}
    if(command[0] == "pwd") {
        pwd(dir);
    }

	//run special functions
	if(mapa.find(command[0]) != mapa.end()){
		void (*choice)(vector<string>);
		choice = mapa[command[0]];
		choice(command);
	}else{

		//Treat Here the | and &
		run(command);
	}

	return;

}

void recursive_run(vector<string> command, string stdout_dir="") {
    for(auto it: command) {
        printf("#%s\n",it.c_str());
    }
    for(int i = command.size()-1; i>=0; i--) {
        if(command[i]=="&") {
            //aqui é pra rodar o que tiver em args e retornar pro futuro, e chamar um fork pro que rolar antes do &
            int rc = fork();
            if(rc < 0){
                fprintf(stderr, "Erro no fork\n");
                exit(1);
            }else if(rc == 0){
                vector<string> child_command(command.begin(), command.begin()+i);
                recursive_run(child_command);
            }else{
                vector<string> args(command.begin()+i+1, command.end());
                runCommand(args);
            }
        }
        else if(command[i]=="|") {
            char output[101];
            generate_file_name(output,100);
            vector<string> child_command(command.begin(), command.begin()+i);
            printf("%d\n",i);
            recursive_run(child_command,output);
            freopen(output, "r+", stdin);
            if(!stdout_dir.empty()) freopen(stdout_dir.c_str(), "w+", stdout);
            vector<string> args(command.begin()+i+1, command.end());
            runCommand(args);
        }
    } 
    runCommand(command);
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
        if(cin.eof()) TERMINAL=false;
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

            string new_word = clean_backwards(word);
			if(!new_word.empty())command.push_back(new_word);
		} while(ss);	
		
		//Call the function that treat the string and run the command
		recursive_run(command);
	}
}
