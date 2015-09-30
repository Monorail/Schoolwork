//Alex Berliner
//COP 3223-003
//guest_struct.c
//12/2/2011
#include <stdio.h>
#include <string.h>
#define MAX_LEN 19

typedef struct family {
    char first[MAX_LEN];
    char last[MAX_LEN];
    int numPeople;
    int priority;
} family_type;

void eleSwap(family_type *familytd,int pos1,int pos2);
void seleSort(family_type *familytd,int numGuests);
void readInfo(FILE *fp, family_type *familytd,int numGuests);
void fileOut(family_type *familytd,int numPoss,int maxGuests);
void alphaSort(family_type *familytd,int numGuests);
int capCheck(family_type *familytd,int numGuests,int maxGuests);
int main(){

    int numGuests, maxGuests,numPoss=0,highPri=0;//numPoss is the number of possible families able to go. highPri is the highest priority family able to go.
    int i,j = 0;

    FILE *fp;
    fp = fopen("allguests.txt","r");

    fscanf(fp,"%d %d",&numGuests,&maxGuests);

    family_type familytd[numGuests];
    readInfo(fp,familytd,numGuests);


    seleSort(familytd, numGuests);

    highPri = capCheck(familytd,numGuests, maxGuests);

    for(i = 0;i < 10;i++){
        if (highPri>=familytd[i].priority)numPoss++;//determine number of families able to attend
    }
    //change array for surviving families
    maxGuests = 0;
    for (i = 0;i<numPoss;i++)maxGuests+=familytd[i].numPeople;//recalculates maxGuests to be the max number of guests on the final list
    alphaSort(familytd, numPoss);
    fileOut(familytd,numPoss, maxGuests);
    return 0;
}


void eleSwap(family_type *familytd,int pos1,int pos2){//swaps elements from all arrays
    char temp[19];
    strcpy(temp,familytd[pos1].first);
    strcpy(familytd[pos1].first,familytd[pos2].first);
    strcpy(familytd[pos2].first,temp);

    strcpy(temp,familytd[pos1].last);
    strcpy(familytd[pos1].last,familytd[pos2].last);
    strcpy(familytd[pos2].last,temp);


    int iTemp = familytd[pos1].numPeople;
    familytd[pos1].numPeople = familytd[pos2].numPeople;
    familytd[pos2].numPeople = iTemp;

    iTemp = familytd[pos1].priority;
    familytd[pos1].priority = familytd[pos2].priority;
    familytd[pos2].priority = iTemp;
}



void seleSort(family_type *familytd,int numGuests){//sort arrays by priority, then last name, then first name
    int i,j;
    for (i = 0; i< numGuests; i++){
        for (j = i; j<numGuests; j++){
            if (familytd[i].priority>familytd[j].priority)eleSwap(familytd,j,i);
                else if (familytd[i].priority==familytd[j].priority && strcmp(familytd[i].last,familytd[j].last) >=1)eleSwap(familytd,j,i);
                    else if (strcmp(familytd[i].last,familytd[j].last) == 0 && strcmp(familytd[i].first,familytd[j].first) >=1)eleSwap(familytd,j,i);
        }
    }
    //for (i = 0;i<10;i++)printf("%s, %s, %d,\t%d\n",last[i],first[i],numPeople[i],priority[i],numGuests);
}

void alphaSort(family_type *familytd,int numGuests){//sort arrays last name, then first name
    int i,j;
    for (i = 0; i< numGuests; i++){
        for (j = i; j<numGuests; j++){
            if (strcmp(familytd[i].last,familytd[j].last) >=1)eleSwap(familytd,j,i);
                    else if (strcmp(familytd[i].last,familytd[j].last) == 0 && strcmp(familytd[i].first,familytd[j].first) >=1)eleSwap(familytd,j,i);
        }
    }
    //for (i = 0;i<10;i++)printf("%s, %s, %d,\t%d\n",last[i],first[i],numPeople[i],priority[i],numGuests);
}

void readInfo(FILE *fp, family_type *familytd,int numGuests){
    int i=0;
    for (i = 0; i < numGuests; i++){
         fscanf(fp,"%s %s %d %d",&familytd[i].first, &familytd[i].last, &familytd[i].numPeople, &familytd[i].priority);
         //printf("%s,%s,%d,%d\n",last[i],first[i],numPeople[i],priority[i]);
    }
    fclose(fp);
}

int capCheck(family_type *familytd,int numGuests,int maxGuests){//returns number of possible families for a list already sorted by priority
    int i,j,finPri=0,pplTemp = 0, pplCtr = 0;
    while(pplCtr < maxGuests && finPri <= familytd[numGuests].priority){
        finPri++;
        for(i = 0; i < numGuests;i++){
            if (familytd[i].priority == finPri)pplTemp+=familytd[i].numPeople;
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

void fileOut(family_type *familytd,int numPoss,int maxGuests){//writes final guest list
    int i;
    FILE *fp;
    fp = fopen("finalguestlist.txt","w");
    fprintf(fp,"%d %d\n",numPoss,maxGuests);//writes number of families and people
    printf("%d %d\n",numPoss,maxGuests);
    for(i=0; i <numPoss;i++){
        fprintf(fp,"%s,%s,%d\n",familytd[i].last,familytd[i].first,familytd[i].numPeople);//prints final list
        printf("%s, %s %d\n",familytd[i].last,familytd[i].first,familytd[i].numPeople);
    }
    fclose(fp);
}

