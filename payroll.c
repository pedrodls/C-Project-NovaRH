#include "./year.h"
#include "./payroll.h"
#include "./employee.h"
#include "./bonus.h"
#include "./absence.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100
#define DISCOUNT_FAULT 2
#define IRT_MAX 25
#define IRT 13
#define INSS 3

struct payroll
{
    float bonusValue;
    float discount;
    float baseSalary;
    float inss;
    float irt;
    float liquidSalary;
    Bonus *bonus;
    Absence *absence;
    Employee *employee;
    Payroll *next;
};

float getDiscountTotalValue(Absence *absence, Employee *employee, Payroll *newPayroll)
{
    int count = 0;

    Absence *auxAbsence = absence;

    Employee *auxEmployee = employee;

    while (auxAbsence)
    {

        Absence *newAbsence = (Absence *)malloc(sizeof(absence));

        setAbsenceDesc(newAbsence, getAbsenceDesc(auxAbsence));
        setAbsenceQtd(newAbsence, getAbsenceQtd(auxAbsence));

        if (!newPayroll->absence)
            setAbsenceNext(newAbsence, NULL);
        else
            setAbsenceNext(newAbsence, newPayroll->absence);

        newPayroll->absence = newAbsence;

        count += getAbsenceQtd(auxAbsence);

        popAbsence(getStackAbsence(auxEmployee));

        auxAbsence = getNextAbsence(auxAbsence);
    }

    return ((getEmployeeSalary(auxEmployee) * (count * DISCOUNT_FAULT) / 100));
}

float getBonusTotalValue(Bonus *bonus, Employee *employee, Payroll *newPayroll)
{
    int count = 0;

    Bonus *auxBonus = bonus;

    Employee *auxEmployee = employee;

    while (auxBonus)
    {

        Bonus *newBonus = (Bonus *)malloc(sizeof(bonus));

        setBonusDesc(newBonus, getBonusDesc(auxBonus));
        setBonusPerc(newBonus, getBonusPerc(auxBonus));

        if (!newPayroll->bonus)
            setBonusNext(newBonus, NULL);
        else
            setBonusNext(newBonus, newPayroll->bonus);

        newPayroll->bonus = newBonus;

        count += getBonusPerc(auxBonus);

        popBonus(getStackBonus(auxEmployee));

        auxBonus = getNextBonus(auxBonus);
    }

    return ((getEmployeeSalary(auxEmployee) * count) / 100);
}

// Cria folha de pagamento

void createPayroll(Employee *employee, QueueYear *year)
{

    Employee *aux_employee = employee;

    if (!aux_employee)
    {
        printf("NAO EXISTEM FUNCIONARIOS\n");

        return;
    }

    Payroll *oldPayroll = NULL;

    while (aux_employee)
    {

        Payroll *newPayroll = (Payroll *)malloc(sizeof(Payroll *));

        // Na folha de pagamento, não queremos fazer refência direta para que atualizando o funcionário, altera a folha de pagamento;

        Employee *newEmployee = (Employee *)malloc(sizeof(Employee *));

        if (!newPayroll || newEmployee)
        {
            printf("Falha na Alocacao\n");

            system("pause <Enter para continuar>!");

            return;
        }

        newEmployee = aux_employee;

        if (getEmployeeStatus(aux_employee))
        {
            newPayroll->bonus = NULL;
            newPayroll->employee = newEmployee;
            newPayroll->absence = NULL;
            newPayroll->next = NULL;

            newPayroll->irt = 0.00;

            if (getEmployeeSalary(aux_employee) >= 101000.00 && getEmployeeSalary(aux_employee) < 120000000.00)
            {
                newPayroll->irt = (getEmployeeSalary(aux_employee) * IRT) / 100;
            }
            else if (getEmployeeSalary(aux_employee) >= 120000000.00)
            {
                newPayroll->irt = (getEmployeeSalary(aux_employee) * IRT_MAX) / 100;
            }

            newPayroll->inss = (getEmployeeSalary(aux_employee) * INSS) / 100;

            newPayroll->baseSalary = getEmployeeSalary(aux_employee);

            newPayroll->discount = getDiscountTotalValue(getTopAbsence(getStackAbsence(aux_employee)), aux_employee, newPayroll) + newPayroll->inss + newPayroll->irt;

            newPayroll->bonusValue = getBonusTotalValue(getTopBonus(getStackBonus(aux_employee)), aux_employee, newPayroll);

            newPayroll->liquidSalary = (newPayroll->baseSalary - newPayroll->discount) + newPayroll->bonusValue;

            if (!oldPayroll)
            {

                oldPayroll = newPayroll;
            }
            else
            {
                newPayroll->next = oldPayroll;
                oldPayroll = newPayroll;
            }
        }

        aux_employee = getNextEmployee(aux_employee);
    }

    Month *auxMonth = getCurrentMonth(getQueueMonth(year));

    setPayrollInCurrentMonth(oldPayroll, auxMonth);

    if (getMonthCode(auxMonth) == 11)
    {
        year = enqueueYear(year, getYear(getCurrentYear(year)) + 1);

        enqueueMonth(getQueueMonth(year));
    }
    else
        enqueueMonth(getQueueMonth(year));

    printf("Folha de Pagamento criada com sucesso!\n");
}

void describeYearHistoryPayroll(Payroll *payroll, int year, Month *month)
{
    Payroll *aux = payroll;

    if (!aux)
    {
        printf("Final do Historico\n");

        return;
    }

    printf("_________________________________________________________\n\n");

    printf("\tFOLHA DE PAGAMENTO (%d/%s)\n",
           year,
           getMonthName(month));

    printf("_________________________________________________________\n");

    while (aux)
    {

        printf("Funcionario        : %s\n", getEmployeeName(aux->employee));

        printf("\nFaltas \n");
        findAbsence(aux->absence);

        printf("\nBonus\n");
        findBonus(aux->bonus);

        printf("\nINSS                : %.2f\n", (aux->inss));

        printf("\nIRT                 : %.2f\n", aux->irt);

        printf("\nTotal de Descontos  : %.2f\n", aux->discount);

        printf("\nTotal de Bonus      : %.2f\n", aux->bonusValue);

        printf("\nSalario Bruto       : %.2f\n", aux->baseSalary);

        printf("\nSalario Liquido     : %.2f\n", aux->liquidSalary);

        printf("_________________________________________________________\n");

        aux = aux->next;
    }
}

void describePayroll(Payroll *payroll, Year *year, int type)
{
    Payroll *aux = payroll;

    if (!aux)
    {
        printf("NAO EXISTE FOLHA DE PAGAMENTO\n");

        return;
    }

    printf("_________________________________________________________\n\n");

    type ? printf("\tULTIMA FOLHA DE PAGAMENTO (%d/%s)\n",
                  getYear(year),
                  getMonthName(getCurrentMonth(getQueueMonthFromYear(year))))

         : printf("\tULTIMA FOLHA DE PAGAMENTO (%d/%s)\n",
                  getYear(year),
                  getMonthName(getPreviousMonth(getQueueMonthFromYear(year))));

    printf("_________________________________________________________\n");

    while (aux)
    {

        printf("Funcionario        : %s\n", getEmployeeName(aux->employee));

        printf("\nFaltas \n");
        findAbsence(aux->absence);

        printf("\nBonus\n");
        findBonus(aux->bonus);

        printf("\nINSS                : %.2f\n", (aux->inss));

        printf("\nIRT                 : %.2f\n", aux->irt);

        printf("\nTotal de Desconto   : %.2f\n", aux->discount);

        printf("\nTotal de Bonus      : %.2f\n", aux->bonusValue);

        printf("\nSalario Bruto       : %.2f\n", aux->baseSalary);

        printf("\nSalario Liquido     : %.2f\n", aux->liquidSalary);

        printf("_________________________________________________________\n");

        aux = aux->next;
    }
}

Payroll *getNextPayroll(Payroll *payroll)
{
    return payroll->next;
}

Absence *getAbsenceFromPayroll(Payroll *payroll)
{
    return payroll->absence;
}
