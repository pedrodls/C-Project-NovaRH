#include "./employee.h"
#include "./payroll.h"
#include "./bonus.h"
#include "./absence.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100

struct payroll
{
    int day, month, year;
    float bonusValue;
    float discount;
    float baseSalary;
    float liquidSalary;
    Bonus *bonus;
    Absence *absence;
    Employee *employee;
    Payroll *next;
};

struct queuePayroll
{
    Payroll *start;
    Payroll *end;
};

QueuePayroll *initPayroll()
{
    QueuePayroll *newPayroll = (QueuePayroll *)malloc(sizeof(QueuePayroll));
    
    if (!newPayroll)
    {
        printf("Falha na Alocacao da Fila do Payroll\n");
        return NULL;
    }

    newPayroll->start = newPayroll->end = NULL;
    return newPayroll;
}

// Criar um Payroll
QueuePayroll *enqueuPayroll(QueuePayroll *head)
{
    if (!head){
        printf("Falha na Fila Payroll\n");
        return head;
    }

    Payroll *newPayroll = (Payroll *)malloc(sizeof(Payroll));


    //logica do tempo
    return head;
}
/*
void *findAllPayroll(QueuePayroll *head)
{
    if (!head || !head->start)
        printf("NAO EXISTEM FALTAS\n___________________________\n\n");
    els e
    {
        Payroll *aux = head->start;
        while (aux){
            printf("Descricao: %s\nQuantidade: %d\n", aux->desc);
            aux = aux->next;
        }
    }
}
*/

