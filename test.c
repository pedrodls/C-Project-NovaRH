
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "year.h"
#include "payroll.h"
#include "employee.h"

int main(){
    QueueYear *year = initYear();
    year = enqueueYear(year, 2024);
    
    enqueueMonth(getQueueMonth(year));
    
    printf("%d\n", getCurrentYear(year));
    printf("%s\n", getCurrentMonth(getQueueMonth(year)));

}
