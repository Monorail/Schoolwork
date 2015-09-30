//Alex Berliner
//COP 3223-003
//schedule.c
//10/14/2011
#include <stdio.h>

int main()
{
int week[168];
int numSched,numEntries;
int i,j,k;
int timeStart, timeEnd,day;
int conflict;
FILE *fp;
fp=fopen("schedule.txt", "r");



fscanf(fp,"%d",&numSched);//read in number of schedules

for (i = 0;i<numSched;i++){

    for (j = 0; j <=167;j++)week[j] = 0;//reset entire schedule for loop

    fscanf(fp,"%d",&numEntries);//read in number of entries per schedule

    for(j = 0;j<numEntries; j++){//loops for number of schedule entries

        fscanf(fp,"%d",&day);//read in event data
        fscanf(fp,"%d",&timeStart);
        fscanf(fp,"%d",&timeEnd);

        for (k = 0;k <=(timeEnd - timeStart-1); k++){
            if (week[day*24 +  timeStart + k] != 1)week[day*24 + timeStart + k] = 1;//calculates position of hour in array and sets it to 1
            else conflict = 1;//if the array position is already 1, conflict will be set to true for the schedule
        }
    }
    if(conflict != 1)printf("Schedule #%d: Good job, no conflicts!\n",i+1);//tell user whether their schedule has a conflict
    else printf("Schedule #%d: Sorry, you double booked yourself again.\n",i+1);
    conflict = 0;//reset conflict
}
fclose(fp);
return 0;
}
