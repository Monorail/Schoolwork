#include <stdio.h>
#include <string.h>
#define MAX_LEN 19
typedef struct family {
    char first[MAX_LEN];
    char last[MAX_LEN];
    int num_people;
    int priority;
} family_type;
void passy(family_type *test);
int main(){
    family_type test[5];
    passy(test);
    printf("%s\n",test[0].first);

    return 0;
}

void passy(family_type *test){
    char lol[] = {'h','i','\0'};
    strcpy(test[0].first,lol);
}
