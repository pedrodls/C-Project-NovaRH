

#include "./employee.h"
#include "./year.h"

// Criar uma folha de pagamento
void createPayroll(Employee *employee, QueueYear *year);

Payroll *getNextPayroll(Payroll *payroll);

Absence *getAbsenceFromPayroll(Payroll *payroll);

void describePayroll(Payroll *payroll, QueueYear *year);

float getBonusTotalValue(Bonus *bonus, Employee *employee, Payroll *newPayroll);

float getDiscountTotalValue(Absence *absence, Employee *employee, Payroll *newPayroll);
