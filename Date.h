#ifndef MYDATE
#define MYDATE

#define MAX_YEAR 2024
#define MIN_YEAR 2010
#define SPECIAL_TAV '#'

typedef struct
{
    int			day;
    int			month;
    int			year;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(const char* date, Date* pDate);
void	printDate(const Date* pDate);

#endif