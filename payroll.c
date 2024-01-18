#include "./year.h"
#include "./payroll.h"
#include "./employee.h"
#include "./bonus.h"
#include "./absence.h"
#include <stdio.h>
#include <stdlib.h>

#define size_char 100

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

// Cria folha de pagamento

Payroll *createPayroll(Employee *employee, QueueYear *year)
{

    Employee *aux_employee = employee;

    Payroll *newPayroll = (Payroll *)malloc(sizeof(Payroll));

    if (!newPayroll)
    {
        printf("Falha na Alocacao da folha de Pagamento\n");
        return NULL;
    }

    while (aux_employee)
    {

        if (getStackAbsence(aux_employee))
        {

            Absence *absence = getTopAbsence(getStackAbsence(aux_employee));

            do
            {

                if (absence)
                {
                    Absence *newAbsence = (Absence *)malloc(sizeof(absence));
                    setAbsenceDesc(newAbsence, getAbsenceDesc(absence));
                    setAbsenceQtd(newAbsence, getAbsenceQtd(absence));

                    if (!newPayroll->absence)
                    { // se é a primeira iteração
                        newPayroll->absence = newAbsence;
                        setAbsenceNext(newPayroll->absence, NULL);
                    }
                    else
                    {
                        setAbsenceNext(newAbsence, newPayroll->absence);
                        newPayroll->absence = newAbsence;
                    };

                    popAbsence(getStackAbsence(aux_employee));

                    absence = getNextAbsence(absence);
                }

            } while (absence);
        }

        aux_employee = getNextEmployee(aux_employee);
    }

    Month *auxMonth = getCurrentMonth(getQueueMonth(year));

    setPayrollInCurrentMonth(getLastPayroll(auxMonth), auxMonth);

    describePayroll(getLastPayroll(auxMonth));

    printf("Folha de Pagamento criada com sucesso!\n");

    return newPayroll;
}

void describePayroll(Payroll *payroll)
{
    Payroll *aux = payroll;

    while (aux)
    {
        printf("%s", getEmployeeName(aux->employee));

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
