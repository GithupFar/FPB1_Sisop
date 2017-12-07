// This calendar example is provided by:
// http://www.codingunit.com Programming Tutorials

#include<stdio.h>
#include<stdlib.h>
#define TRUE    1
#define FALSE   0

int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[]=
{
	" ",
	"\n\tJanuary",
	"\n\tFebruary",
	"\n\tMarch",
	"\n\tApril",
	"\n\tMay",
	"\n\tJune",
	"\n\tJuly",
	"\n\tAugust",
	"\n\tSeptember",
	"\n\tOctober",
	"\n\tNovember",
	"\n\tDecember"
};


int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	
	d1 = (year - 1)/ 4;
	d2 = (year - 1)/ 100;
	d3 = (year - 1)/ 400;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}


int determineleapyear(int year)
{
	if(year% 4 == FALSE && year%100 != FALSE || year%400 == FALSE)
	{
		days_in_month[2] = 29;
		return TRUE;
	}
	else
	{
		days_in_month[2] = 28;
		return FALSE;
	}
}

void calendar(int year, int daycode,int x)
{
	int month, day;
	for ( month = 1; month < x; month++ )
	{
		
			// Set position for next month
			daycode = ( daycode + days_in_month[month] ) % 7;
	}
		printf("%s %d", months[month],year);
		printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		
		// Correct the position for the first date
		for ( day = 1; day <= 1 + daycode * 5; day++ )
		{
			printf(" ");
		}
		
		// Print all the dates for one month
		for ( day = 1; day <= days_in_month[month]; day++ )
		{
			printf("%2d", day );
			
			// Is day before Sat? Else start next line Sun.
			if ( ( day + daycode ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
        printf("\n");
}


int main(int argc,char *argv[])
{
	int year, daycode, leapyear,x,Input[3],status;
	while(status<argc-1)
    {
        status++;
        Input[status] = atoi(argv[status]);
    }

    x = Input[1];
    
    if(x==-3)
    {
        year = 2017;
        int a = 11,b = 12, c = 1;
        daycode = determinedaycode(year);
	    determineleapyear(year);
	    calendar(year, daycode,a);
        calendar(year, daycode,b);
        calendar(year, daycode,c);
        printf("\n");
    }
    else
    {
        year = Input[2];
        daycode = determinedaycode(year);
	    determineleapyear(year);
	    calendar(year, daycode,x);
	    printf("\n");
    }
}
