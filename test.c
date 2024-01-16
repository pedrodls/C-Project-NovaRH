
#include <stdlib.h>
#include <stdio.h>
#include "bonus.h"
#include "absence.h"
#include <string.h>

#define size_char 50
#define size_char_phone 10
#define size_char_nif 14


int main(){
    StackAbsence *newAbsence = initAbsence();
    pushAbsence(newAbsence, "descricao");
    pushAbsence(newAbsence, "descricao");
    pushAbsence(newAbsence, "descricao");
    popAbsence(newAbsence);
    popAbsence(newAbsence);


    findAllAbsence(newAbsence);
}
