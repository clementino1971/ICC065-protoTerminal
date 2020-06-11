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


