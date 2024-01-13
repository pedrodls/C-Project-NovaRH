#include "department.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        newDepartment->colaborators = 0;
        newDepartment->status = 0;
    }
    else
        printf("Falha na Alocação do departamento\n");

    return newDepartment;
}

// Criar um departamento
Department *createDepartment(Department *head, char *name)
{
    Department *newDepartment = (Department *)malloc(sizeof(Department));

    if (newDepartment)
    {
        newDepartment->name = name;

        newDepartment->colaborators = 0;

        newDepartment->next = head;

        newDepartment->status = 1;
    }
    else
        printf("Falha na Alocação do departamento\n");

    return newDepartment;
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
    Department *aux = data;

    while (aux)
    {

        describeDepartment(aux);

        aux = aux->next;
    }
}

// Atualiza um departamento
void *updateDepartment(Department *data, int code)
{
    Department *departmentData = findOneDepartment(data, code);

    char *newName;
    int newState;

    if (departmentData)
    {
        describeDepartment(departmentData);
        printf("Clique enter caso não deseja atualizar o campo!\n");

        fflush(stdin);

        printf("Novo nome: ");
        scanf("%s", newName);

        printf("Ativar - 1 | Desactivar - 2: ");
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
}
// Busca de Informações da Empresa apartid dos arquivos
Department *readDepartment()
{

    return NULL;
}