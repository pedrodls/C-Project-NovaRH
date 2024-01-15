#include "employee.h"
#include "department.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_char 100

struct employee
{
    int code, status;
    char *name;
    float salary;
    Department *department;
    Employee *next;
};

Employee *initEmployee()
{
    return NULL;
}

// Descreve um colaborador
void describeColaborator(Employee *data)
{
    if (data)
        printf("\nCodigo: %d,\nNome: %s,\nSalario: %f,\nEstado: %s\nDepartamento: %s\n\n", getEmployeeCode(data), getEmployeeName(data), getEmployeeSalary(data), getEmployeeStatus(data) ? "Ativo" : "Desativado", data->department ? getDepartmentName(data->department): "NULL");
}

// Criar um Funcionario
Employee *createEmployee(Employee *data, int code, char *name, float salary)
{
    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));

    if (!newEmployee)
    {
        printf("Falha na Alocacao de memória para Funcionario\n");
        return data;
    }
    // Inserção no Início
    newEmployee->code = code;
    newEmployee->status = 1;
    newEmployee->name = name;
    newEmployee->salary = salary;
    newEmployee->department = NULL;
    newEmployee->next = data;

    printf("\n\nFuncionario criado com sucesso!\n\n");
    return newEmployee;
}

// Encontra um Funcionario
Employee *findOneEmployee(Employee *data, int code)
{
    Employee *aux = data;

    while (aux && aux->code != code)
        aux = aux->next;

    return aux;
}

// Encontra todos departamentos
void findAllEmployees(Employee *data)
{
    if (!data)
        printf("Lista Vazia\n");
    else
    {
        Employee *aux = data;
        while (aux != NULL)
        {
            describeColaborator(aux);

            aux = aux->next;
        }
    }
}

// Atualiza o dado de um funcionário
Employee *updateEmployee(Employee *data, int code)
{
    Employee *employeeData = findOneEmployee(data, code);

    char *newName = (char *)malloc(sizeof(size_char));
    int newState;
    float newSalary;

    if (employeeData)
    {
        fflush(stdin);

        printf("Novo nome <apenas Enter para ignorar>: ");
        fgets(newName, size_char, stdin);
        newName[strcspn(newName, "\n")] = '\0';

        printf("\nSalario: ");
        scanf("%f", &newSalary);

        printf("\nAtivar - 1 | Desactivar - 0: ");
        scanf("%d", &newState);

        /* printf("\nCodigo do departamento: ");
        scanf("%d", &departCode);

        if (departCode > 0 && findOneDepartment(departments, departCode))
        {
            setEmployeeDepartment(employeeData, departCode);
            printf("\nDepartamento atualizado com sucesso!\n");
        }
        else if (departCode > 0 && !findOneDepartment(departments, departCode))
        {
            printf("\nDepartamento nao encontrado!\n");
        } */

        if (!(strcmp(newName, employeeData->name) == 0))
        {
            setEmployeeName(employeeData, newName);
            printf("\nNome atualizado com sucesso!\n");
        }

        if (!(employeeData->status == newState && (newState >= 0 && newState <= 1)))
        {
            setEmployeeStatus(employeeData, newState);
            printf("Estado atualizado com sucesso!\n");
        }

        if (!(employeeData->salary == newSalary))
        {
            setEmployeeSalary(employeeData, newSalary);
            printf("Salario atualizado com sucesso!\n");
        }

        printf("\n\nFuncionario actualizado com sucesso!\n\n");
    }
    else
        printf("Funcionario nao encontrado!\n");

    return data;
}

Employee *employeeDepartment(Employee *data, Department *data_department)
{

    if (!data)
        printf("NAO EXISTEM FUNCIONARIOS\n----------------------------------\n\n");
    else
    {
        if (!(getDepartmentCode(data_department) > 0))
        {
            printf("NAO EXISTEM DEPARTAMENTOS\n----------------------------------\n\n");
            return data;
        }

        Employee *aux_employee = data;
        Department *aux_department = data_department;

        int dCode, eCode;

        printf("\t\nFUNCIONARIOS\n");
        while (aux_employee)
        {
            printf("+------------------------------------------+\n");
            printf("  %s (cod: %d)\n", aux_employee->name, aux_employee->code);
            printf("+------------------------------------------+\n");
            aux_employee = aux_employee->next;
        }

        printf("\t\nDEPARTAMENTOS\n");
        while (aux_department)
        {
            printf("+------------------------------------------+\n");
            printf("  %s (cod: %d)\n", getDepartmentName(aux_department), getDepartmentCode(aux_department));
            printf("+------------------------------------------+\n");
            aux_department = nextDepartment(aux_department);
        }

        fflush(stdin);

        printf("Codigo <FUNCIONARIO>: ");
        scanf("%d", &eCode);

        printf("Codigo <DEPARTAMENTO>: ");
        scanf("%d", &dCode);

        aux_department = findOneDepartment(data_department, dCode);

        aux_employee = findOneEmployee(data, eCode);

        if (!(aux_department && aux_employee))
        {

            printf("Dados nao encontrados\n----------------------------------\n\n");

            return data;
        }

        aux_employee->department = aux_department;

        printf("Departamento do Funcionario Atualizado!\n----------------------------------\n\n");

        return data;
    }

    return data;
}

Employee *deleteEmployee(Employee *data, int code)
{
    Employee *aux = data, *ant = NULL;

    while (aux && aux->code != code)
    {
        ant = aux;
        aux = aux->next;
    }

    if (!aux)
    {
        printf("Funcionario nao Encontrado!\n");
        return data;
    }
    else if (aux == data)
    { // encontrou no inicio
        data = aux->next;
        free(aux);
    }
    else
    {
        ant->next = aux->next;
    }

    printf("\nFuncionario Eliminado Com Sucesso\n");
    return data;
}

// retorna o nome do funcionário
char *getEmployeeName(Employee *employee)
{
    return employee->name;
}

// retorna o código do funcionário
int getEmployeeCode(Employee *employee)
{
    return employee ? employee->code : 0;
}
// retorna o estado do funcionário
int getEmployeeStatus(Employee *employee)
{
    return employee->status;
}
// retorna o nif da empresa
float getEmployeeSalary(Employee *employee)
{
    return employee->salary;
}

// Mètodos Setters
void setEmployeeName(Employee *employee, char *value)
{
    employee->name = value;
}
void setEmployeeCode(Employee *employee, int value)
{
    employee->code = value;
}
void setEmployeeStatus(Employee *employee, int value)
{
    employee->status = value;
}
void setEmployeeSalary(Employee *employee, float value)
{
    employee->salary = value;
}