#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>

int is_file(const char *path);
int is_directory(const char *path);
void parse(char *path);


int main(int argc, char **argv) {

	if (argc > 1) {
		const char *path = argv[argc-1];
		printf("path: %s\n", path);
		const char *path_is_file = is_file(path) ? "TRUE" : "FALSE";
		const char *path_is_dir = is_directory(path) ? "TRUE" : "FALSE";
		printf("path is file %s\n", path_is_file);
		printf("path is dir %s\n", path_is_dir);
	}
	return 0;
}


int is_directory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int is_file(const char *path) {
    struct stat statbuf;
    stat(path, &statbuf);
    return S_ISREG(statbuf.st_mode);
}

void parse(char *path) {

}
