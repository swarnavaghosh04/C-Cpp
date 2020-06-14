#include <stdio.h>

int main(int agrc, char** argv){
	for(int i = 0; i < argc; i++){
		printf("%s\n", argv[i]);
	}
	return 0;
}
