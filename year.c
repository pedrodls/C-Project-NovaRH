#include <stdio.h>
#include <stdlib.h>
#include "year.h"
#include "payroll.h"

char *months[] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

struct month
{
    char *name;
    int code;
    struct month *next;
    Payroll *payrolls;
};

struct queueMonth
{
    Month *startMonth, *endMonth;
};

struct year
{
    int year;

    struct year *next;
    QueueMonth *months;
};

struct queueYear
{
    Year *startYear, *endYear;
};
// inicializa a fila do ano
QueueYear *initYear()
{
    QueueYear *newYear = (QueueYear *)malloc(sizeof(QueueYear));

    if (!newYear)
    {
        printf("Falha na alocação da Fila do ano\n");
        return NULL;
    }

    newYear->startYear = newYear->endYear = NULL;
}
// inicializa a fila dos meses
QueueMonth *initMonth()
{
    QueueMonth *newMonth = (QueueMonth *)malloc(sizeof(QueueMonth));

    if (!newMonth)
    {
        printf("Falha na alocação da Fila dos meses\n");
        return NULL;
    }

    newMonth->startMonth = newMonth->endMonth = NULL;
}
// Lista todos os anos
void findAllYear(QueueYear *year)
{
    if (!year || !year->startYear)
        printf("Lista Vazia\n");
    else
    {
        Year *aux = year->startYear;

        while (aux)
        {
            printf("%d\n", aux->year);
            aux = aux->next;
        }
        printf("\n\n");
    }
}
// LIsta todos os anos com os seus meses
void findAllYearMonth(QueueYear *year)
{
    if (!year || !year->startYear)
        printf("Lista Vazia\n");
    else
    {
        Year *aux = year->startYear;

        while (aux)
        {
            printf("%d\n", aux->year);
            Month *aux_month = aux->months->startMonth;
            if (!aux_month)
                printf("    Lista Vazia\n");
            while (aux_month)
            {
                printf("%s\n", aux_month->name);
                aux_month = aux_month->next;
            }
            printf("\n-------------------------\n");
            aux = aux->next;
        }
        printf("\n\n");
    }
}

// cria um novo ano definindo também os meses
QueueYear *enqueueYear(QueueYear *queueYear, int year)
{

    if (!queueYear)
    {
        printf("Falha na Fila do Ano\n");
        return queueYear;
    }

    Year *newYear = (Year *)malloc(sizeof(Year));
    if (!newYear)
    {
        printf("Falha na Alocacao do Ano\n");
        return queueYear;
    }

    newYear->months = initMonth();

    newYear->year = year;

    newYear->next = NULL;

    if (!queueYear->startYear)
        queueYear->startYear = queueYear->endYear = newYear;
    else
    {
        queueYear->endYear->next = newYear;
        queueYear->endYear = newYear;
    }

    return queueYear;
}

// cria um novo ano definindo também os meses
QueueMonth *enqueueMonth(QueueMonth *queueMonth)
{

    if (!queueMonth)
    {
        printf("Falha na Fila do Mes\n");
        return queueMonth;
    }

    Month *newMonth = (Month *)malloc(sizeof(Month));

    if (!newMonth)
    {
        printf("Falha na Alocacao do Mes\n");
        return queueMonth;
    }

    newMonth->next = NULL;
    newMonth->payrolls = NULL;

    if (!queueMonth->startMonth)
    {
        newMonth->code = 0;
        newMonth->name = months[0];

        queueMonth->startMonth = queueMonth->endMonth = newMonth;
    }
    else
    {
        newMonth->code = queueMonth->endMonth->code + 1;
        newMonth->name = months[queueMonth->endMonth->code + 1];

        queueMonth->endMonth->next = newMonth;

        queueMonth->endMonth = newMonth;
    }

    return queueMonth;
}

// recebe a fila de um ano
QueueMonth *getQueueMonth(QueueYear *year)
{
    // vou precisar do endYear dessa fila e retornar o QueueMonth
    return year->endYear->months;
}

int getCurrentYear(QueueYear *year)
{
    return year->endYear->year;
}

Month *getCurrentMonth(QueueMonth *month)
{
    return month->endMonth;
}

char *getMonthName(Month *month)
{
    return month->name;
}

Payroll *getLastPayroll(Month *month)
{

    Month *aux = month;

    return aux->payrolls;
}

void setPayrollInCurrentMonth(Payroll *payroll, Month *month)
{
    month->payrolls = payroll;
}
