//Alex Berliner
//COP 3223-003
//weather.c
//10/14/2011
#include <stdio.h>
int main(){
int day   [10000];
int month [10000];
int year  [10000];
float temp[10000];
int wedDay;
int wedMonth;
int entCount = 0;
char fileLoc [50];
FILE *fp;


printf("What is the month and day of your wedding?\n");
scanf("%d %d",&wedMonth,&wedDay);//ask user for wedding time

printf("What file stores your city's temperature data?\n");
scanf("%s",&fileLoc);//ask user for weather file
fp=fopen(fileLoc, "r");

do{//read in file data
fscanf(fp,"%d",&month[entCount]);
fscanf(fp,"%d",&day[entCount]);
fscanf(fp,"%d",&year[entCount]);
fscanf(fp,"%f",&temp[entCount]);
entCount++;
}while(month[entCount-1]!=-1);

int i;
float dayAvg = 0;
int dayCount = 0;
for (i = 0; i <=entCount;i++){
    if(day[i] == wedDay && temp[i]!=-99){//checks for days that are equal to given day, and for days with no temperature
    dayCount++;//counts number of days to divide with
    dayAvg+=temp[i];//accumulator for temperatures for day average
    }
}

dayAvg = dayAvg/dayCount;
printf("The average temperature on your wedding day is %.2lf degrees F.\n",dayAvg);


float monthAvg = 0;
int monthCount = 0;
for (i = 0; i <=entCount;i++){
    if( month[i] == wedMonth && temp[i]!=-99){//checks for days that are equal to given month, and for days with no temperature
    monthCount++;//counts number of days to divide with
    monthAvg+=temp[i];//accumulator for temperatures for days average
    }
}
monthAvg = monthAvg/monthCount;
printf("The average temperature on your wedding month is %.2lf degrees F.\n",monthAvg);
if (monthAvg>=60 && monthAvg<=75 && dayAvg>=60 && dayAvg<=75){
    printf("The weather looks good for an outdoor wedding!\n");
}
else{
    printf("It’s probably best to move the wedding indoors, sorry.");
}
fclose(fp);
return 0;
}
