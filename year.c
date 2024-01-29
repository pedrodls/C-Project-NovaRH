#include <stdio.h>
#include <stdlib.h>
#include "year.h"
#include "payroll.h"

char *months[] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho","Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
//definição da struct month
struct month
{
    char *name;
    int code;
    struct month *next;
    struct month *prev;
    Payroll *payrolls;
};
//fila do mês
struct queueMonth
{
    Month *startMonth, *endMonth;
};
//definição da struct year
struct year
{
    int year;

    struct year *next;
    struct year *prev;

    QueueMonth *months;
};
//fila do year
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

    newYear->prev = queueYear->endYear;

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

// cria um novo mes
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
    newMonth->prev = queueMonth->endMonth;
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

// recebe a fila de um ano, retorna a fila do mês do último ano
QueueMonth *getQueueMonth(QueueYear *year)
{
    // vou precisar do endYear dessa fila e retornar o QueueMonth
    return year->endYear->months;
}
//retorna a fila do mês de determinado ano
QueueMonth *getQueueMonthFromYear(Year *year)
{
    // Traz os meses de um ano
    return year->months;
}
//retorna o ano corrente
Year *getCurrentYear(QueueYear *year)
{
    return year->endYear;
}
//retorna o valor do ano
int getYear(Year *year)
{
    return year->year;
}
//retorna o mês corrente
Month *getCurrentMonth(QueueMonth *month)
{
    return month->endMonth;
}
//retorna o més anterior ao corrente
Month *getPreviousMonth(QueueMonth *month)
{
    return month->endMonth->prev;
}
//retorna o ano anterior ao corrente
Year *getPreviousYear(QueueYear *year)
{
    return year->endYear->prev;
}
//retorna o nome do mês
char *getMonthName(Month *month)
{
    return month->name;
}
//retorna o código do més
int getMonthCode(Month *month)
{
    return month->code;
}
//retorna a folha de pagamento de determinado mês
Payroll *getLastPayroll(Month *month)
{

    Month *aux = month;

    if (!aux)
    {
        return NULL;
    }

    return aux->payrolls;
}
//actualiza o payroll do mês
void setPayrollInCurrentMonth(Payroll *payroll, Month *month)
{
    month->payrolls = payroll;
}
//apresenta todos os anos q foram efectuados folha de salário
void getYearHistory(QueueYear *queueYear)
{
    Year *aux = queueYear->startYear;

    while (aux)
    {
        Month *auxMonth = aux->months->startMonth;

        while (auxMonth && auxMonth->payrolls)
        {

            describeYearHistoryPayroll(auxMonth->payrolls, aux->year, auxMonth);

            auxMonth = auxMonth->next;
        }

        aux = aux->next;
    }
}
