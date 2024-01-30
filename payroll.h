

#include "./employee.h"
#include "./year.h"

// Criar uma folha de salário
void createPayroll(Employee *employee, QueueYear *year);
// retorna o endereço da próxima folha de salário
Payroll *getNextPayroll(Payroll *payroll);
// retorna a lista de faltas do funcionário que constarâo na folha
Absence *getAbsenceFromPayroll(Payroll *payroll);
// descreve os dados da folha de salário
void describePayroll(Payroll *payroll, Year *year, int type);
// retorna o valor total do bonus
float getBonusTotalValue(Bonus *bonus, Employee *employee, Payroll *newPayroll);
// retorna o valor total dos descontos
float getDiscountTotalValue(Absence *absence, Employee *employee, Payroll *newPayroll);
// descreve a folha de salário de acordo com o ano e mês escolhido
void describeYearHistoryPayroll(Payroll *payroll, int year, Month *month);

// apresenta histórico da folha de salário de um funcionário
void describeYearHistoryPayrollOfEmployee(Payroll *payroll, int year, Month *month, Employee *employee);