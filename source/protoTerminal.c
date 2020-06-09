#include "protoTerminal.h"

// deve ser colcado na main 
//     if(argc == 1) ls(".");
// 	else ls(argv[1]);

void ls(const char *dir){
	struct dirent *namelist;
	DIR *drt =opendir(dir);
	if(!drt){
		if(errno == ENOENT){
			perror("Dictory does not exist");
		} else {
			perror("Unable to read the repository");
			exit(EXIT_FAILURE);
		}
	}
	while ((namelist = readdir(drt)) != NULL){
		if(namelist->d_name[0] == '.') continue;
		printf("%s \n", namelist->d_name);
	}
	printf("\n");
}

void pwd(){
    char cwd[FILENAME_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}