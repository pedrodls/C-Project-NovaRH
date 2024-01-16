#include "./bonus.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100

struct bonus
{
    char *desc;
    float perc;
    Bonus *next;
};

struct stackBonus
{
    Bonus *top;
};

// Inicialização os Bonus quando a mesma não possui algum registro

StackBonus *initBonus()
{
    StackBonus *newBonus = (StackBonus *)malloc(sizeof(StackBonus));
    if (!newBonus)
    {
        printf("Falha na Alocacao da Pilha do Bonus\n");
        return NULL;
    }
    newBonus->top = NULL;
    return newBonus;
}

// Criar um Bonus
StackBonus *pushBonus(StackBonus *head, char *desc, float perc)
{
    if (!head)
    {
        printf("Falha na Pilha Bonus\n");
        return head;
    }

    Bonus *newBonus = (Bonus *)malloc(sizeof(Bonus));
    if (newBonus)
    {
        newBonus->desc = desc;
        newBonus->perc = perc;
        newBonus->next = head->top;

        head->top = newBonus;
    }
    else
        printf("Falha na Alocacao de Bonus\n");

    return head;
}

Bonus *popBonus(StackBonus *head)
{
    if (!head || !head->top){
        printf("NAO EXISTE BONUS\n");
        return NULL;
    }
    Bonus *aux = head->top;
    head->top = head->top->next;
    free(aux);
    return aux;
}

// Encontra todos Bonuss
void *findAllBonus(StackBonus *head)
{
    if (!head || !head->top)
        printf("NAO EXISTEM BONUS\n___________________________\n\n");
    else
    {
        Bonus *aux = head->top;
        while (aux){
            printf("Descricao: %s\nPercentagem: %.2f\n", aux->desc, aux->perc);
            aux = aux->next;
        }
    }
}

