#include "./year.h"
#include "./payroll.h"
#include "./employee.h"
#include "./bonus.h"
#include "./absence.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100
#define IRT 100
#define DISCOUNT 100
#define INSS 100

struct payroll
{
    float bonusValue;
    float discount;
    float baseSalary;
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

    Payroll *newPayroll = (Payroll *)malloc(sizeof(Payroll));

    if (!newPayroll)
    {
        printf("Falha na Alocacao da folha de Pagamento\n");

        return;
    }

  /*   if (!getEmployeeStatus(aux_employee))
    {

        return;
    } */

    newPayroll->bonus = NULL;
    newPayroll->employee = employee;
    newPayroll->absence = NULL;
    newPayroll->next = NULL;

    newPayroll->baseSalary = getEmployeeSalary(aux_employee);

    newPayroll->discount = getDiscountTotalValue(getTopAbsence(getStackAbsence(aux_employee)), aux_employee, newPayroll);

    newPayroll->bonusValue = getBonusTotalValue(getTopBonus(getStackBonus(aux_employee)), aux_employee, newPayroll);

    newPayroll->liquidSalary = newPayroll->baseSalary - newPayroll->discount + newPayroll->bonusValue;

    /*  while (aux_employee)
     {

         aux_employee = getNextEmployee(aux_employee);
     } */

    Month *auxMonth = getCurrentMonth(getQueueMonth(year));

    setPayrollInCurrentMonth(newPayroll, auxMonth);

    printf("Folha de Pagamento criada com sucesso!\n");
}

void describePayroll(Payroll *payroll, QueueYear *year)
{
    Payroll *aux = payroll;

    printf("_________________________________________________________\n\n");
    printf("\tULTIMA FOLHA DE PAGAMENTO (%d/%s)\n",
           getCurrentYear(year),
           getMonthName(getCurrentMonth(getQueueMonth(year))));
    printf("_________________________________________________________\n");

    while (aux)
    {

        printf("Funcionario: %s\n", getEmployeeName(aux->employee));

        printf("\nFaltas \n");
        findAbsence(aux->absence);

        printf("\nBonus\n");
        findBonus(aux->bonus);

        printf("\nTotal de Descontos  : %.2f\n", aux->discount);
        printf("\nTotal de Bonus  : %.2f\n", aux->bonusValue);

        printf("\nSalario Bruto    : %.2f\n", aux->baseSalary);

        printf("\nSalario Liquido    : %.2f\n", aux->liquidSalary);

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
