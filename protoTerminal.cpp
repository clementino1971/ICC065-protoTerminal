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

		run(command);
	}

	return;

}

void recursive_run(vector<string> command, int stdout_pipe[2]=NULL) {
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
            vector<string> child_command(command.begin(), command.begin()+i);
            int pipefd[2];
            pipe(pipefd);
            recursive_run(child_command,pipefd);
            int rc = fork();
            if(rc < 0){
                cout << "Fork Failed\n";
                exit(1);
            } else if(rc == 0){
                int saved_stdout=-1;
                int saved_stdin=-1;
                if(stdout_pipe!=NULL) {
                    saved_stdout = dup(1);
                    dup2(stdout_pipe[1],1);
                }
                saved_stdin=dup(0);
                dup2(pipefd[0],0);
                vector<string> args(command.begin()+i+1, command.end());
                runCommand(args);
                dup2(saved_stdin,0);
                close(pipefd[0]);
                if(saved_stdout!=-1) dup2(saved_stdout,1);
                kill(getpid(), SIGTERM);
            }
            else {
                int wc = wait(NULL);
                if(stdout_pipe!=NULL) {
                    close(stdout_pipe[1]);
                }
            }
            return;
        }
    } 
    int rc = fork();
    if(rc < 0){
        cout << "Fork Failed\n";
        exit(1);
    } else if(rc == 0){
        int saved_stdout=-1;
        if(stdout_pipe!=NULL) {
            saved_stdout = dup(1);
            dup2(stdout_pipe[1],1);
        }
        runCommand(command);
        if(saved_stdout!=-1) dup2(saved_stdout,1);
        kill(getpid(), SIGTERM);
    }
    else {
        int wc = wait(NULL);
        if(stdout_pipe!=NULL) {
            close(stdout_pipe[1]);
        }
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
