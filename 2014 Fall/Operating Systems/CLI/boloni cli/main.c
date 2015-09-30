#include <stdio.h>
#include <signal.h>

int main( int argc, const char* argv[] ){
	char command[40];
	int looping = 1;
	while(looping){
		printf("# ");
		scanf("%s", command);
		
		if(strcmp(command, "quit") == 0){
			return 0;
		} else if(strcmp(command, "murder") == 0){
			int proc;
			if(scanf("%d", &proc) != EOF){
				kill(proc, SIGKILL);
			}
		}
		
		printf("%s\n", command);
	}
	return 0;
}

char *getLine(){
	
	return null;
}
