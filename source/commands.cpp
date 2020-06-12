#include "../header/commands.h"

// deve ser colcado na main 
//     if(argc == 1) ls(".");
// 	else ls(argv[1]);

void ls( char *dir){
	struct dirent *namelist;
	// copia o diretorio passado
	DIR *drt =opendir(dir);
	if(!drt){
		if(errno == ENOENT){
			perror("Dictory does not exist");
		} else {
			perror("Unable to read the repository");
			exit(EXIT_FAILURE);
		}
	}
	//aqui ele le as entradas do diretorios
	// entradas = aquivos, diretorios etc 
	// ele le com o readdir
	while ((namelist = readdir(drt)) != NULL){
		if(namelist->d_name[0] == '.') continue;
		std::cout << namelist->d_name << "\n";
	}
	std::cout << "\n";
}

void pwd(char *dir){
    std::cout << dir << "\n\n";
}

void run(vector<string> commands){
	int nWords = commands.size();

	int rc = fork();
	if(rc < 0){
		cout << "Fork Failed\n";
		exit(1);
	}else if(rc == 0){
		char *myArgs[nWords];

		for(int i=0;i<nWords;i++){
			char* buffer = new char[commands[i].length()+1];
			strcpy(buffer, commands[i].c_str());
				

			if(strcmp(buffer,"<") == 0){
				buffer = new char[commands[i+1].length()+1];
				strcpy(buffer,commands[i+1].c_str());	
				
				freopen(buffer,"r+",stdin);

				i++;
				continue;
			}
			
			if(strcmp(buffer,">") == 0){
				buffer = new char[commands[i+1].length()+1];
				strcpy(buffer, commands[i+1].c_str());

				freopen(buffer, "w+", stdout);				
				i++;
				continue;
			}

			myArgs[i] = buffer;

			if(i==nWords-1) 
				myArgs[i] = NULL;
		}
			
		execvp(myArgs[0], myArgs);
		cout << "Isso não deve ser impresso\n";
	}else{
		int wc = wait(NULL);
		return;
	}
}

	// colocar na main
	// char s[FILENAME_MAX]; 
    // getcwd(s, FILENAME_MAX);
    // if(argc == 1) cd(".",s);
	// else cd(argv[1],s);

   
void cd( char *dir){
    char newDir[FILENAME_MAX];
	char currDir[FILENAME_MAX];
	getcwd(currDir, FILENAME_MAX);
	//pega permissao para voltar pra main
    uid_t uid = getuid();
    struct passwd* pwd = getpwuid(uid);
    //comando pra voltar pra main
    if(dir=="." || dir=="$HOME" || dir =="~"){
        chdir(pwd->pw_dir);
    }else{
        chdir(dir);
    }
	//verifica se o diretorio eh valido
    getcwd(newDir, FILENAME_MAX);
    if(strcmp(currDir,newDir) != 0) strcpy(currDir,newDir);
    else std::cout<<"cd:"<< dir <<": No such file or directory"<<"\n";
}
