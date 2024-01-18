

#include "./employee.h"
#include "./year.h"


// Criar uma folha de pagamento
Payroll *createPayroll(Employee *employee, QueueYear *year);

Payroll *getNextPayroll(Payroll *payroll);

Absence *getAbsenceFromPayroll(Payroll *payroll);

void describePayroll(Payroll *payroll);


