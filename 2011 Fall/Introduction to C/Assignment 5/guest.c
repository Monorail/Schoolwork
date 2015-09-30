//Alex Berliner
//COP 3223-003
//guest.c
//11/18/2011
#include <stdio.h>
#include <string.h>

void eleSwap(char (*first)[19], char (*last)[19],int *numPeople, int *priority,int pos1,int pos2);
void seleSort(char (*first)[19], char (*last)[19],int *numPeople, int *priority,int numGuests);
void readInfo(FILE *fp, char (*first)[19], char (*last)[19],int *numPeople, int *priority,int numGuests);
void fileOut(char (*first)[19], char (*last)[19],int *numPeople,int numPoss,int maxGuests);
void alphaSort(char (*first)[19], char (*last)[19],int *numPeople, int *priority,int finGuests);
int capCheck(int *numPeople, int *priority,int numGuests,int maxGuests);
int main(){

    int numGuests, maxGuests,numPoss=0,highPri=0;//numPoss is the number of possible families able to go. highPri is the highest priority family able to go.
    int i,j = 0;

    FILE *fp;
    fp = fopen("allguests.txt","r");

    fscanf(fp,"%d %d",&numGuests,&maxGuests);

    int numPeople[numGuests];
    char first[numGuests][19], last[numGuests][19];
    int priority[numGuests];

    readInfo(fp,first,last,numPeople, priority,numGuests);
    //for (i = 0;i<10;i++)printf("%s, %s, %d, %d\n",last[i],first[i],numPeople[i],priority[i],numGuests);
    //printf("\n\n");
    seleSort(first, last, numPeople, priority, numGuests);
    //printf("capCheck = %d\n",capCheck(numPeople, priority,numGuests, maxGuests));
    highPri = capCheck(numPeople, priority,numGuests, maxGuests);

    for(i = 0;i < 10;i++){
        if (highPri>=priority[i])numPoss++;//determine number of families able to attend
    }
    //change array for surviving families
    maxGuests = 0;
    for (i = 0;i<numPoss;i++)maxGuests+=numPeople[i];//recalculates maxGuests to be the max number of guests on the final list
    alphaSort(first, last, numPeople, priority, numPoss);
    fileOut(first,last,numPeople,numPoss, maxGuests);
    return 0;
}


void eleSwap(char (*first)[19], char (*last)[19],int *numPeople, int *priority,int pos1,int pos2){//swaps elements from all arrays
    char temp[19];
    strcpy(temp,first[pos1]);
    strcpy(first[pos1],first[pos2]);
    strcpy(first[pos2],temp);

    strcpy(temp,last[pos1]);
    strcpy(last[pos1],last[pos2]);
    strcpy(last[pos2],temp);


    int iTemp = numPeople[pos1];
    numPeople[pos1] = numPeople[pos2];
    numPeople[pos2] = iTemp;

    iTemp = priority[pos1];
    priority[pos1] = priority[pos2];
    priority[pos2] = iTemp;
}



void seleSort(char (*first)[19], char (*last)[19],int *numPeople, int *priority,int numGuests){//sort arrays by priority, then last name, then first name
    int i,j;
    for (i = 0; i< numGuests; i++){
        for (j = i; j<numGuests; j++){
            if (priority[i]>priority[j])eleSwap(first, last,numPeople, priority,j,i);
                else if (priority[i]==priority[j] && strcmp(last[i],last[j]) >=1)eleSwap(first, last,numPeople, priority,j,i);
                    else if (strcmp(last[i],last[j]) == 0 && strcmp(first[i],first[j]) >=1)eleSwap(first, last,numPeople, priority,j,i);
        }
    }
    //for (i = 0;i<10;i++)printf("%s, %s, %d,\t%d\n",last[i],first[i],numPeople[i],priority[i],numGuests);
}

void alphaSort(char (*first)[19], char (*last)[19],int *numPeople, int *priority,int numGuests){//sort arrays last name, then first name
    int i,j;
    for (i = 0; i< numGuests; i++){
        for (j = i; j<numGuests; j++){
            if (strcmp(last[i],last[j]) >=1)eleSwap(first, last,numPeople, priority,j,i);
                    else if (strcmp(last[i],last[j]) == 0 && strcmp(first[i],first[j]) >=1)eleSwap(first, last,numPeople, priority,j,i);
        }
    }
    //for (i = 0;i<10;i++)printf("%s, %s, %d,\t%d\n",last[i],first[i],numPeople[i],priority[i],numGuests);
}

void readInfo(FILE *fp,char (*first)[19],char (*last)[19],int *numPeople, int *priority,int numGuests){
    int i=0;
    for (i = 0; i < numGuests; i++){
         fscanf(fp,"%s %s %d %d",&first[i], &last[i], &numPeople[i], &priority[i]);
         //printf("%s,%s,%d,%d\n",last[i],first[i],numPeople[i],priority[i]);
    }
    fclose(fp);
}

int capCheck(int *numPeople, int *priority,int numGuests,int maxGuests){//returns number of possible families for a list already sorted by priority
    int i,j,finPri=0,pplTemp = 0, pplCtr = 0;
    while(pplCtr < maxGuests && finPri <= priority[numGuests]){
        finPri++;
        for(i = 0; i < numGuests;i++){
            if (priority[i] == finPri)pplTemp+=numPeople[i];
        }
        //printf("finPri = %d\npplTemp = %d\npplCtr = %d\n\n",finPri,pplTemp,pplCtr);
        if((pplTemp + pplCtr)<maxGuests)pplCtr+=pplTemp;
            else{
                maxGuests = pplCtr;
                return finPri-1;
            }
        pplTemp = 0;
    }
    maxGuests = pplCtr;
    return finPri;
}

void fileOut(char (*first)[19], char (*last)[19],int *numPeople,int numPoss,int finGuests){//writes final guest list
    int i;
    FILE *fp;
    fp = fopen("finalguestlist.txt","w");
    fprintf(fp,"%d %d\n",numPoss,finGuests);//writes number of families and people
    printf("%d %d\n",numPoss,finGuests);
    for(i=0; i <numPoss;i++){
        fprintf(fp,"%s,%s,%d\n",last[i],first[i],numPeople[i]);//prints final list
        printf("%s, %s %d\n",last[i],first[i],numPeople[i]);
    }
    fclose(fp);
}
