#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

// defines
#define ANSI_BLUE "\e[1;34m" // bold blue color
#define ANSI_RESET "\e[0m" // resets color to normal text

// global variables
int directories = 0;
int files = 0;

// pre-defines
void parse(const char *path, int level);


int main(int argc, char **argv) {	

	const char *path = argc > 1 ? argv[2] : ".";
	printf("%s\n", path);
	parse(path, 0);
	printf("\n\n\n%d files, %d directories\n", files, directories);

	return 0;
}

// if a path is a directory, returns 0 on error
int is_directory(const char *path) {
   	struct stat statbuf;
   	if (stat(path, &statbuf) != 0) {
       return 0;
   	}
   	return S_ISDIR(statbuf.st_mode);
}

// // if path is a regular file 
// int is_file(const char *path) {//XXX: this function is probably not needed
//     struct stat statbuf;
//     stat(path, &statbuf);
//     return S_ISREG(statbuf.st_mode);
// }

// returns the number of dirs inside path
int get_file_count(const char *path) {
	struct dirent *de;  
    DIR *dr = opendir(path);
	int count = 0;
    while ((de = readdir(dr)) != NULL) {
		count++;
	}
	closedir(dr);
	return count;
}

// parses path recursively and prints the tree of it
void parse(const char *path, int level) {
	struct dirent *de;  
    DIR *dr = opendir(path);
    if (!dr) {
        perror("Could not open current directory" );
		return;
	}
	
	bool first_file = true;
	int count = get_file_count(path);
	int file_number = 0;
    while ((de = readdir(dr)) != NULL) {
        char *name = de->d_name;
		char real_path[strlen(name)+1+strlen(path)];
		strcat(real_path, path);
		strcat(real_path, "/");
		strcat(real_path, name);

		// making sure that im not accessing dot files, '..' or '.' 
		if (name[0] != '.') {
			if (level > 0) {
				for (int i = 0; i < level; i++) {
					printf("│  ");
				}
			}

			bool is_dir = is_directory(real_path);

			if (file_number == count-1) {
				printf("└──");
			}
			else {
				printf("├──");
			}

			if (is_dir) {
				printf("%s%s%s\n", ANSI_BLUE, name, ANSI_RESET);
				directories++;
				parse(real_path, level+1);
			}
			else if (!is_dir) {
				printf("%s\n", name);
				files++;
			}
		}
		first_file = false;
		file_number++;
	}

    closedir(dr); 

}
