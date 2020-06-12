#include "../header/commands.h"

// deve ser colcado na main 
//     if(argc == 1) ls(".");
// 	else ls(argv[1]);

void ls(vector<string> args){
	struct dirent *namelist;
	// copia o diretorio passado
    char dir[FILENAME_MAX];

    if(args.size()<=1) getcwd(dir,FILENAME_MAX);
    else strcpy(dir,args[1].c_str());

	DIR *drt =opendir(dir);
    
	if(!drt){
		if(errno == ENOENT){
			perror("Directory does not exist");
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
        if(namelist->d_type==DT_DIR){
            printf(ANSI_COLOR_CYAN STYLE_BOLD "%s/\n", namelist->d_name);
            printf(STYLE_NO_BOLD);
            printf(ANSI_COLOR_RESET);

            continue;
        }
		std::cout << namelist->d_name << "\n";
	}
	std::cout << "\n";
}

void pwd(char* dir){
    std::cout << dir;
}

void run(vector<string> commands){
    int nWords = commands.size();

    char *myArgs[nWords+1];
    myArgs[nWords]=NULL;

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

    }
    execvp(myArgs[0], myArgs);
    return;
}
// colocar na main
// char s[FILENAME_MAX]; 
// getcwd(s, FILENAME_MAX);
// if(argc == 1) cd(".",s);
// else cd(argv[1],s);



void cd(vector<string> args){
	
    if(args.size()<=1) {
        fprintf(stderr,"cd deve ter ao menos um parâmetro\n");
        return;
    }

    char dir[FILENAME_MAX];
    char newDir[FILENAME_MAX];
    char currDir[FILENAME_MAX];

    getcwd(currDir, FILENAME_MAX);
    strcpy(dir,args[1].c_str());

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