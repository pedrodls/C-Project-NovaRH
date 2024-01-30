#include "employee.h"
#include "payroll.h"
#include "department.h"
#include "bonus.h"
#include "absence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_char 100
// definição da struct funcionário
struct employee
{
    int code;
    int status;
    int age;
    char *IBAN;
    char *gender;
    char *BI;
    char *name;
    float salary;
    StackBonus *bonus;
    StackAbsence *absence;
    Department *department;
    Employee *next;
};
// ponteiro da lista funcionário inicializa com NULL
Employee *initEmployee()
{
    return NULL;
}

// Descreve um colaborador
void describeColaborator(Employee *data)
{
    if (data)
    {
        printf("\nCodigo: %d,\nBI: %s, \nGenero: %s, \nIBAN: %s, \nNome: %s,\nIdade: %d,\nSalario: %.2f,\nEstado: %s\nDepartamento: %s\n\n", getEmployeeCode(data), getEmployeeBI(data), getEmployeeGender(data), getEmployeeIBAN(data), getEmployeeName(data), getEmployeeAge(data), getEmployeeSalary(data), getEmployeeStatus(data) ? "Ativo" : "Desativado", data->department ? getDepartmentName(data->department) : "NULL");

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
Employee *createEmployee(Employee *data, int code, char IBAN[], char name[], float salary, int age, char *BI, char *gender)
{

    char *newIban = (char *)malloc(size_char);

    char *newName = (char *)malloc(size_char);

    char *newBI = (char *)malloc(size_char);

    char *newGender = (char *)malloc(sizeof(char));

    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));

    if (!newEmployee || !newBI || !newIban || !newName || !newGender)
    {
        printf("Falha na Alocacao de memória para Funcionario\n");
        return data;
    }

    newIban = IBAN;

    newName = name;

    newBI = BI;

    newGender = gender;

    // Inserção no Início
    newEmployee->age = age;
    newEmployee->code = code;
    newEmployee->status = 1;
    newEmployee->IBAN = newIban;
    newEmployee->BI = newBI;
    newEmployee->gender = gender;
    newEmployee->name = newName;
    newEmployee->salary = salary;
    newEmployee->department = NULL;
    newEmployee->bonus = initBonus();
    newEmployee->absence = initAbsence();
    newEmployee->next = data;

    printf("\n\nFuncionario criado com sucesso!\n\n");
    return newEmployee;
}

// Encontra um Funcionario Pelo BI
Employee *findOneEmployeeByCardId(Employee *data, char *BI)
{
    Employee *aux = data;

    while (aux && !(strcmp(strlwr(aux->BI), strlwr(BI)) == 0))
        aux = aux->next;

    return aux;
}

// Encontra um Funcionario
Employee *findOneEmployee(Employee *data, int code)
{
    Employee *aux = data;

    while (aux && aux->code != code)
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

        while (aux)
        {
            if (getEmployeeStatus(aux))
            {
                !type ? describeColaborator(aux)
                      : simpleDescribeColaborator(aux);
            }

            aux = aux->next;
        }
        printf("\n\n");
    }
}

// Encontra todos funcionarios desabilitados

void findAllDisabledEmployees(Employee *data)
{
    if (!data)
        printf("Lista de Funcionarios Vazia\n");
    else
    {
        Employee *aux = data;

        char op;
        int employeeCode, cont = 0;

        printf("Lista de Funcionarios Desativados\n\n");

        while (aux && !getEmployeeStatus(aux))
        {
            describeColaborator(aux);
            cont++;
            aux = aux->next;
        }

        if (cont > 0)
        {
            printf("\n\n");
            printf("1 - Habilitar\n");
            printf("2 - Sair\n");

            fflush(stdin);
            printf("Opcao: ");

            scanf("%c", &op);

            printf("\n\n");

            switch (op)
            {
            case '1':
                printf("Codigo do funcionario: ");
                scanf("%d", &employeeCode);

                aux = findOneEmployee(data, employeeCode);

                if (aux)
                {
                    setEmployeeStatus(data, 1);
                    printf("Funcionario atualizado com sucesso!");
                }
                else
                    printf("Funcionario nao encontrado!");

                break;

            default:
                return;
                break;
            }
        }
    }
}
// apresenta todos os funcionários aposentados
void findAllOldEmployees(Employee *data)
{
    if (!data)
        printf("Lista de Funcionarios Vazia\n");
    else
    {
        Employee *aux = data;

        char op;
        int employeeCode;

        printf("Lista de Funcionarios Na Reforma\n\n");

        while (aux && getEmployeeAge(aux) > 60)
        {
            describeColaborator(aux);
            aux = aux->next;
        }
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
// lista as faltas de uma lista do payroll
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
void updateEmployee(Employee *employeeData, int code, char *IBAN, char *newName, float newSalary, int newState, int age)
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

    if (!(strcmp(IBAN, employeeData->IBAN) == 0))
    {
        if (strlen(IBAN) > 0)
        {
            setEmployeeIBAN(employeeData, IBAN);
            printf("\nIBAN atualizado com sucesso!\n");
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

    if (!(employeeData->age == age))
    {
        setEmployeeAge(employeeData, age);
        printf("\nIdade atualizada com sucesso!\n");
        updated = 1;
    }

    if (!updated)
    {
        printf("\nDados nao atualizados!\n");
    }
}
// actualiza a idade de todos funcionário após o payroll
void updateEmployeeAge(Employee *employees)
{

    Employee *aux = employees;

    while (aux)
    {
        aux->age = aux->age + 1;

        aux = aux->next;
    }
}
// vincula o funcionário ao departamento
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
// elimina um funcionário da losta
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
// cria faltas para o funcionario
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
// elimina a ultima falta do funcionário
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
// Métodos Getters
// retorna o nome do funcionário
char *getEmployeeName(Employee *employee)
{
    return employee->name;
}
// retorna o iban do funcionário
char *getEmployeeIBAN(Employee *employee)
{
    return employee->IBAN;
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
// Pega a idade de um colaborador
int getEmployeeAge(Employee *employee)
{
    return employee->age;
}
// retorna o salário do funcionário
float getEmployeeSalary(Employee *employee)
{
    return employee->salary;
}

// Retorna o BI de um Funcionario
char *getEmployeeBI(Employee *employee)
{
    return employee->BI;
}

// Retorna o genero de um Funcionario
char *getEmployeeGender(Employee *employee)
{
    return employee->gender;
}
// retorn a pilha de falta do funcionário
StackAbsence *getStackAbsence(Employee *employee)
{
    return employee->absence;
}
// retorna a pilha de bonus do funcionário
StackBonus *getStackBonus(Employee *employee)
{
    return employee->bonus;
}
// retorna o próximo endereço do funcionário
Employee *getNextEmployee(Employee *employee)
{
    return employee->next;
}

// Mètodos Setters
// actualiza o nome do funcionário
void setEmployeeName(Employee *employee, char *value)
{
    employee->name = value;
}
// actualiza o código do funcionário
void setEmployeeCode(Employee *employee, int value)
{
    employee->code = value;
}
// actualiza o estado do funcionário
void setEmployeeStatus(Employee *employee, int value)
{
    employee->status = value;
}
// actualiza o salário do funcionário
void setEmployeeSalary(Employee *employee, float value)
{
    employee->salary = value;
}
// actualiza o iban do funcionário
void setEmployeeIBAN(Employee *employee, char *value)
{
    employee->IBAN = value;
}
// actualiza a idade do funcionário
void setEmployeeAge(Employee *employee, int value)
{
    employee->age = value;
}

// Insere o BI num Funcionario
void setEmployeeBI(Employee *employee, char *value)
{
    employee->BI = value;
}

// Insere o Genero num Funcionario
void setEmployeeGender(Employee *employee, char *value)
{
    employee->gender = value;
}
