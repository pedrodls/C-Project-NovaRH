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