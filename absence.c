#include "./absence.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100

struct absence
{
    char *desc;
    int qtd;
    Absence *next;
};

struct stackAbsence
{
    Absence *top;
};

// Inicialização as faltas quando a mesma não possui algum registro
StackAbsence *initAbsence()
{
    StackAbsence *newAbsence = (StackAbsence *)malloc(sizeof(StackAbsence));
    if (!newAbsence)
    {
        printf("Falha na Alocacao da Pilha do Absence\n");
        return NULL;
    }

    newAbsence->top = NULL;
    return newAbsence;
}

// Criar um Absence
StackAbsence *pushAbsence(StackAbsence *head, char *desc)
{
    if (!head)
    {
        printf("Falha na Pilha Absence\n");
        return head;
    }

    Absence *newAbsence = (Absence *)malloc(sizeof(Absence));
    if (newAbsence)
    {
        newAbsence->desc = desc;
        newAbsence->qtd = 1;
        newAbsence->next = head->top;

        head->top = newAbsence;
    }
    else
        printf("Falha na Alocacao de Absence\n");

    return head;
}

Absence *popAbsence(StackAbsence *head)
{
    if (!head || !head->top){
        printf("NAO EXISTE Absence\n");
        return NULL;
    }
    Absence *aux = head->top;
    head->top = head->top->next;
    free(aux);
    return aux;
}

// Encontra todas as faltas
void *findAllAbsence(StackAbsence *head)
{
    if (!head || !head->top)
        printf("NAO EXISTEM FALTAS\n___________________________\n\n");
    else
    {
        Absence *aux = head->top;
        while (aux){
            printf("Descricao: %s\nQuantidade: %d\n", aux->desc, aux->qtd);
            aux = aux->next;
        }
    }
}

