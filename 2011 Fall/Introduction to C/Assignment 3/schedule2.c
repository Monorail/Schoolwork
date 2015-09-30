//Alex Berliner
//COP 3223-003
//schedule2.c
//10/14/2011
#include <stdio.h>

int main()
{
int week[168];
int numSched,numEntries;
int i,j,k;
int timeStart, timeEnd,day;
int conflict = 0;
int usedHours;
FILE *fp;
fp=fopen("schedule.txt", "r");



fscanf(fp,"%d",&numSched);//read in number of schedules

for (i = 0;i<numSched;i++){
    usedHours = 0;
    for (j = 0; j <=167;j++)week[j] = 0;

    fscanf(fp,"%d",&numEntries);//read in number of entries per schedule

    for(j = 0;j<numEntries; j++){//loops for number of schedule entries

        fscanf(fp,"%d",&day);//read in event data
        fscanf(fp,"%d",&timeStart);
        fscanf(fp,"%d",&timeEnd);
        conflict = 0;//reset conflict finder
        for (k = 0;k <=(timeEnd - timeStart-1); k++){//loops based on number of hours at event
            if (week[day*24 +  timeStart + k] == 1) conflict = 1;//calculates position of hour in array and sets conflict to 1 if there's a conflict with the events
        }
        if(conflict == 0)//adds event to array if there's no conflict
            for (k = 0;k <=(timeEnd - timeStart-1); k++){
                week[day*24 + timeStart + k] = 1;
            }

    }
    for (j = 0;j <=167;j++){//calculates number of hours busy. I wish C could do 'for each' loops
        if (week[j] == 1)usedHours++;
    }
    printf("Schedule #%d contains %d hour(s) of scheduled activity.\n",i+1,usedHours);

}
fclose(fp);
return 0;
}
