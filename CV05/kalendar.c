#include <stdio.h>

static char *name_of_month[] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

static unsigned char first_day_in_year = 4; 		// 1. 1. 2016 is Friday
static char *day_of_week[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" };
static int days_in_month[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	//static int first_day_in_september = 3; // 1. 9. 2016 is Thursday

unsigned char month = 0;
unsigned char day = 0;

unsigned char startDay(unsigned char mon){
	int sum = first_day_in_year;
	for (unsigned char i = 0; i < mon; i++){
		sum += days_in_month[i];
	}
	return sum % 7;
}

void monthInit (unsigned char mon){
	printf(" %s\n", name_of_month[mon]);

	for (unsigned char i = 0; i < 7; i++){
		printf (" %s", day_of_week[i]);
	}

	unsigned char helper = startDay(mon);
	printf("\n");
	for (day = 0; day < helper; day++){
		printf("   ");
	}

	for (unsigned char date = 1; date <= days_in_month[month]; date++){
		if (day %7 == 0 && date != 1) printf("\n");
		if (date < 10) printf(" ");
		printf(" ");
		printf ("%d", date);
		day++;
	}
	printf("\n");
}

int main (void){
	while (month < 12){
		printf ("\n");
		monthInit(month);
		month++;
	}
	return 0;
}
