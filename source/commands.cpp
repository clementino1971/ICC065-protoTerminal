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
	// colocar na main
	// char s[FILENAME_MAX]; 
    // getcwd(s, FILENAME_MAX);
    // if(argc == 1) cd(".",s);
	// else cd(argv[1],s);
   
void cd(const char *dir, char * currDir){
    char newDir[FILENAME_MAX];
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
