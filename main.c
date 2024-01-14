#include <stdlib.h>
#include <stdio.h>
#include "company.h"
#include "department.h"
#include <string.h>


#define size_char 50
#define size_char_phone 10
#define size_char_nif 14

int main()
{
    Company *myCompany = initCompany();
    readCompany(myCompany);
    printf("%s\n", getName(myCompany));
    printf("%s\n", getEmail(myCompany));
    printf("%s\n", getAddress(myCompany));
    printf("%s\n", getPhone(myCompany));
    printf("%s\n", getNIF(myCompany));

    return 0;
}


