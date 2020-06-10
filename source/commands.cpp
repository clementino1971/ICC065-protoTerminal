#include "../header/commands.h"

// deve ser colcado na main 
//     if(argc == 1) ls(".");
// 	else ls(argv[1]);

void ls( char *dir){
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
		std::cout << namelist->d_name << "\n";
	}
	std::cout << "\n";
}

void pwd(char *dir){
    std::cout << dir << "\n\n";

}
