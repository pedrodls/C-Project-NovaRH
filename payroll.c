#include "./year.h"
#include "./payroll.h"
#include "./employee.h"
#include "./bonus.h"
#include "./absence.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100
#define DISCOUNT 100
#define IRT 100
#define INSS 100

struct payroll
{
    float bonusValue;
    float discount;
    float baseSalary;
    float liquidSalary;
    float irt;
    float inss;
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

    return ((getEmployeeSalary(auxEmployee) * count) / 100);
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

        Payroll *newPayroll = (Payroll *)malloc(sizeof(Payroll));

        if (!newPayroll)
        {
            printf("Falha na Alocacao da folha de Pagamento\n");

            system("pause <Enter para continuar>!");

            return;
        }

        newPayroll->bonus = NULL;
        newPayroll->employee = aux_employee;
        newPayroll->absence = NULL;
        newPayroll->next = NULL;

        newPayroll->baseSalary = getEmployeeSalary(aux_employee);

        newPayroll->discount = getDiscountTotalValue(getTopAbsence(getStackAbsence(aux_employee)), aux_employee, newPayroll);

        newPayroll->bonusValue = getBonusTotalValue(getTopBonus(getStackBonus(aux_employee)), aux_employee, newPayroll);

        newPayroll->liquidSalary = newPayroll->baseSalary - newPayroll->discount + newPayroll->bonusValue;

        if (!oldPayroll)
        {

            oldPayroll = newPayroll;
        }
        else
        {
            newPayroll->next = oldPayroll;
            oldPayroll = newPayroll;
        }

        aux_employee = getNextEmployee(aux_employee);
    }

    Month *auxMonth = getCurrentMonth(getQueueMonth(year));

    setPayrollInCurrentMonth(oldPayroll, auxMonth);

    if (getMonthCode(auxMonth) == 1)
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

        printf("Funcionario        :%s\n", getEmployeeName(aux->employee));

        printf("\nFaltas \n");
        findAbsence(aux->absence);

        printf("\nBonus\n");
        findBonus(aux->bonus);

        printf("\nINSS                : %.2f\n", aux->inss);

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

        printf("Funcionario        :%s\n", getEmployeeName(aux->employee));

        printf("\nFaltas \n");
        findAbsence(aux->absence);

        printf("\nBonus\n");
        findBonus(aux->bonus);

        printf("\nINSS                : %.2f\n", aux->inss);

        printf("\nIRT                 : %.2f\n", aux->irt);

        printf("\nTotal de Descontos  : %.2f\n", aux->discount);

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
