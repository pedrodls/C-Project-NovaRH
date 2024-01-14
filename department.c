#include "department.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_char 100

struct department
{
    int code;
    int status;
    char *name;
    int colaborators;
    Department *next;
};

// Inicialização da Empresa quando a mesma não possui algum registro
Department *initDepartment()
{
    Department *newDepartment = (Department *)malloc(sizeof(Department));

    if (newDepartment)
    {
        newDepartment->code = 0;
        newDepartment->name = "";
        newDepartment->colaborators = 0;
        newDepartment->status = 0;
        newDepartment->next = NULL;
    }
    else
        printf("Falha na Alocação do departamento\n");

    return newDepartment;
}

// Criar um departamento
Department *createDepartment(Department *head, char *name)
{

    if (head->code > 0)
    {
        Department *newDepartment = (Department *)malloc(sizeof(Department));

        if (!newDepartment)
        {
            printf("Falha na Alocação do departamento\n");
            return head;
        }

        newDepartment->code = head->code + 1;

        newDepartment->name = name;

        newDepartment->colaborators = 0;

        newDepartment->next = head;

        newDepartment->status = 1;

        return newDepartment;
    }

    if (head->code == 0)
    {
        head->name = name;
        head->code = 1;
        head->colaborators = 0;
        head->status = 1;
    }

    return head;
}

// Descreve um departamento
void *describeDepartment(Department *data)
{
    if (data)
        printf("\nCodigo: %d,\nNome: %s,\nColaboradores: %d,\nEstado: %s\n\n", data->code, data->name, data->colaborators, data->code ? "Ativo" : "Deasativado");
}

// Encontra um departamento
void *findOneDepartment(Department *data, int code)
{
    Department *aux = data;

    while (aux && aux->code != code)
        aux = aux->next;

    return aux;
}

// Encontra todos departamentos
void *findAllDepartments(Department *data)
{
    if (data->code == 0)
        printf("Lista Vazia\n");
    else
    {
        Department *aux = data;
        while (aux)
        {
            describeDepartment(aux);
            aux = aux->next;
        }
    }
}

// Atualiza um departamento
Department *updateDepartment(Department *data, int code)
{
    Department *departmentData = findOneDepartment(data, code);

    char *newName = (char *)malloc(sizeof(size_char));
    int newState;

    if (departmentData)
    {
        printf("\nClique enter caso nao deseja atualizar o campo!\n");

        fflush(stdin);

        printf("Novo nome: ");
        fgets(newName, size_char, stdin);
        newName[strcspn(newName, "\n")] = '\0';

        printf("\nAtivar - 1 | Desactivar - 2: ");
        scanf("%d", &newState);

        if (!(strcmp(newName, departmentData->name) == 0))
        {
            departmentData->name = newName;

            printf("\nNome atualizado com sucesso!\n");
        }

        if (!(departmentData->status == newState))
        {
            departmentData->name = newName;

            printf("Status atualizado com sucesso!\n");
        }
    }
    else
        printf("Departamento nao encontrado!\n");

    return data;
}

Department *deleteDepartment(Department *data, int code){
    Department *aux = data, *ant = NULL;

    while (aux && aux->code != code){
        ant = aux;
        aux = aux->next;
    }

    if(!aux){
        printf("Departamento nao Encontrado!\n");
        return data;
    }
    else if(aux == data){ //encontrou no inicio
        data = aux->next;
        free(aux);
    }else{
        ant->next = aux->next;
    }

    if(data == NULL)
        data = initDepartment();
    
    printf("\nDepartamento Eliminado Com Sucesso\n");
    return data;
}