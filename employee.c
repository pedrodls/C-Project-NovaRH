#include "employee.h"
#include "payroll.h"
#include "department.h"
#include "bonus.h"
#include "absence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_char 100

/* employee
{
    int code, status;
    char *name;
    char *cargo;
    char *conta;
    int idade;
    float salary;
    StackBonus *bonus;
    StackAbsence *absence;
    Department *department;
    Employee *next;
};*/

struct employee
{
    int code, status;
    char *BI;
    char *name;
    float salary;
    StackBonus *bonus;
    StackAbsence *absence;
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
    {
        printf("\nCodigo: %d,\nBI: %s, \nNome: %s,\nSalario: %.2f,\nEstado: %s\nDepartamento: %s\n\n", getEmployeeCode(data), getEmployeeBI(data), getEmployeeName(data), getEmployeeSalary(data), getEmployeeStatus(data) ? "Ativo" : "Desativado", data->department ? getDepartmentName(data->department) : "NULL");

        printf("\nBonus de %s: \n", getEmployeeName(data));
        findAllBonus(data);
        printf("\n------------------------------------------------\n\n");

        printf("\nFaltas de %s: \n", getEmployeeName(data));

        findAllAbsence(data);

        printf("\n------------------------------------------------\n\n");
    }
}

// Descreve um colaborador de forma simples
void simpleDescribeColaborator(Employee *data)
{
    if (data)
    {
        printf("\nCodigo: %d - Nome: %s\n", getEmployeeCode(data), getEmployeeName(data));
    }
}

// Criar um Funcionario
Employee *createEmployee(Employee *data, int code, char *BI, char *name, float salary)
{
    Employee *auxEmployee = findOneEmployeeByCardId(data, BI);

    if (auxEmployee)
    {
        printf("Este funcionario[BI=%s] ja existe!\n", BI);
        return data;
    }

    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));

    if (!newEmployee)
    {
        printf("Falha na Alocacao de memória para Funcionario\n");
        return data;
    }

    // Inserção no Início
    newEmployee->code = code;
    newEmployee->status = 1;
    newEmployee->BI = BI;
    newEmployee->name = name;
    newEmployee->salary = salary;
    newEmployee->department = NULL;
    newEmployee->bonus = initBonus();
    newEmployee->absence = initAbsence();
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

Employee *findOneEmployeeByCardId(Employee *data, char *BI)
{
    Employee *aux = data;

    while (aux && !(strcmp(strlwr(aux->BI), strlwr(BI)) == 0))
        aux = aux->next;

    return aux;
}

// Encontra todos funcionarios
void findAllEmployees(Employee *data, int type)
{
    if (!data)
        printf("Lista de Funcionarios Vazia\n");
    else
    {
        Employee *aux = data;

        printf("Lista de Funcionarios\n\n");

        while (aux && getEmployeeStatus(aux))
        {
            !type ? describeColaborator(aux)
                  : simpleDescribeColaborator(aux);

            aux = aux->next;
        }
        printf("\n\n");
    }
}

// Encontra todos bonus
void findAllBonus(Employee *data)
{
    Bonus *aux_bonus = getTopBonus(data->bonus);
    if (!aux_bonus || !data)
        printf("Lista de Bonus Vazia\n\n");
    else
    {
        while (aux_bonus)
        {
            printf("\nDescricao: %s - Percentagem: %.2f", getBonusDesc(aux_bonus), getBonusPerc(aux_bonus));
            aux_bonus = getNextBonus(aux_bonus);
        }
    }
}

// Encontra todas as faltas
void findAllAbsence(Employee *data)
{
    Absence *aux = getTopAbsence(data->absence);

    if (!aux || !data)
        printf("Lista de Faltas Vazia\n\n");
    else
    {
        while (aux)
        {
            printf("\nDescricao: %s - Quantidade: %d", getAbsenceDesc(aux), getAbsenceQtd(aux));

            aux = getNextAbsence(aux);
        }
    }
}

void findAllAbsenceFromPayroll(Absence *absence)
{
    Absence *aux = absence;

    if (!aux)
        printf("Lista de Faltas Vazia\n\n");
    else
    {
        while (aux)
        {
            printf("\nDescricao: %s - Quantidade: %d", getAbsenceDesc(aux), getAbsenceQtd(aux));

            aux = getNextAbsence(aux);
        }
    }
}

// Atualiza o dado de um funcionário
void updateEmployee(Employee *employeeData, int code, char *BI, char *newName, float newSalary, int newState)
{
    int updated = 0;

    if (!(strcmp(newName, employeeData->name) == 0))
    {
        if (strlen(newName) > 0)
        {
            setEmployeeName(employeeData, newName);
            printf("\nNome atualizado com sucesso!\n");
            updated = 1;
        }
    }

    if (!(strcmp(BI, employeeData->BI) == 0))
    {
        if (strlen(BI) > 0)
        {
            setEmployeeBI(employeeData, BI);
            printf("\nBI atualizado com sucesso!\n");
            updated = 1;
        }
    }

    if (!(employeeData->status == newState && (newState >= 0 && newState <= 1)))
    {
        setEmployeeStatus(employeeData, newState);
        printf("\nEstado atualizado com sucesso!\n");
        updated = 1;
    }

    if (!(employeeData->salary == newSalary))
    {
        setEmployeeSalary(employeeData, newSalary);
        printf("\nSalario atualizado com sucesso!\n");
        updated = 1;
    }

    if (!updated)
    {
        printf("\nDados nao atualizados!\n");
    }
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
Department *findEmployeeByDepartment(Department *department, Employee *employee, int code)
{
    Department *aux_department = findOneDepartment(department, code);
    Employee *aux_employee = employee;

    /**/
    if (!aux_department)
        printf("\nDEPARTAMENTO NAO ENCONTRADO!\n----------------------------------\n\n");
    else
    {
        int count = 0;
        while (aux_employee)
        {
            if (getDepartmentCode(aux_employee->department) == code)
            {
                if (count == 0)
                    printf("\t\nFUNCIONARIOS DO DEPARTAMENTO:\n");

                printf("+------------------------------------------+\n");
                printf("  %s (cod: %d)\n", aux_employee->name, aux_employee->code);
                printf("+------------------------------------------+\n");
                aux_employee = aux_employee->next;
                count = 1;
            }
        }
        if (!count)
            printf("\t\n- - - NAO HA FUNCIONARIOS NESSE DEPARTAMENTO\n\n");
    }

    return department;
}
// cria um bonus para o funcionario
Employee *createBonus(Employee *employee, int code, char *desc, float perc)
{
    Employee *aux_employee = findOneEmployee(employee, code); // Localizando funcionario
    if (aux_employee)
    {
        aux_employee->bonus = pushBonus(aux_employee->bonus, desc, perc);
        printf("Bonus adicionado com Sucesso\n");
    }
    else
        printf("Funcionario nao encontrado\n");

    return employee;
}
// elimina o ultimo bonus do funcionário
Employee *deleteBonus(Employee *employee, int code)
{
    Employee *aux_employee = findOneEmployee(employee, code); // Localizando funcionario

    if (aux_employee)
    {
        if (!getTopBonus(aux_employee->bonus))
        {
            printf("NAO EXISTE BONUS\n");

            return employee;
        }
        else
        {

            popBonus(aux_employee->bonus);
            printf("Bonus removido com Sucesso\n");
        }
    }
    else
        printf("Funcionario nao encontrado\n");

    return employee;
}

Employee *createAbsence(Employee *employee, int code, char *desc)
{
    Employee *aux_employee = findOneEmployee(employee, code); // Localizando funcionario
    if (aux_employee)
    {
        aux_employee->absence = pushAbsence(aux_employee->absence, desc);
        printf("Falta adicionado com Sucesso\n");
    }
    else
        printf("Funcionario nao encontrado\n");

    return employee;
}
// elimina a ultima féria do funcionário
Employee *deleteAbsence(Employee *employee, int code)
{
    Employee *aux_employee = findOneEmployee(employee, code); // Localizando funcionario

    if (aux_employee)
    {
        if (!getTopAbsence(aux_employee->absence))
        {
            printf("NAO EXISTEM FALTAS\n");

            return employee;
        }
        else
        {

            popAbsence(aux_employee->absence);

            printf("Falta removido com Sucesso!\n");
        }
    }
    else
        printf("Funcionario nao encontrado\n");

    return employee;
}

char *getEmployeeName(Employee *employee)
{
    return employee->name;
}

char *getEmployeeBI(Employee *employee)
{
    return employee->BI;
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

StackAbsence *getStackAbsence(Employee *employee)
{
    return employee->absence;
}

StackBonus *getStackBonus(Employee *employee)
{
    return employee->bonus;
}

Employee *getNextEmployee(Employee *employee)
{
    return employee->next;
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

void setEmployeeBI(Employee *employee, char *value)
{
    employee->BI = value;
}