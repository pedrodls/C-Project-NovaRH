#include "./bonus.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100
//definição da struct bonus
struct bonus
{
    char *desc;
    float perc;
    Bonus *next;
};
//definição da struct pilha de bonus
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
//Elimina um bonus
Bonus *popBonus(StackBonus *head)
{
    if (!head || !head->top)
    {
        printf("NAO EXISTE BONUS\n");
        return NULL;
    }
    Bonus *aux = head->top;
    head->top = head->top->next;
    free(aux);

    return aux;
}
//Métodos Getters
// retorna o topo da pilha bonus
Bonus *getTopBonus(StackBonus *head)
{
    return head->top;
}

// retorna a descrição do bonus
char *getBonusDesc(Bonus *bonus)
{
    return bonus->desc;
}
// retorna a percentagem do bonus
float getBonusPerc(Bonus *bonus)
{
    return bonus->perc;
}
// retorna o proximo bonus da lista
Bonus *getNextBonus(Bonus *bonus)
{
    return bonus->next;
}
//apresenta todos os bonus de uma lista
void findBonus(Bonus *bonus)
{
    Bonus *aux = bonus;

    while (aux)
    {
        printf("\nDescricao: %s - Percentagem: %.2f%\n\n", aux->desc, aux->perc);
        aux = aux->next;
    }
}
//Métodos Setters
//actualiza a descrição de um bonus
void setBonusDesc(Bonus *bonus, char *desc)
{
    bonus->desc = desc;
}
//actualiza a percentagem de um bonus
void setBonusPerc(Bonus *bonus, float perc)
{
    bonus->perc = perc;
}
//actualiza o next de um nó
void setBonusNext(Bonus *oldBonus, Bonus *newBonus)
{
    oldBonus->next = newBonus;
}
