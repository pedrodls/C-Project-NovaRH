//inclusão de bibliotecas -relacionamento
#include "./department.h"
#include "./absence.h"
#include "./bonus.h"
//definição da estrutura funcionário
typedef struct employee Employee;

//inicializa a entidade funcionàrio
Employee *initEmployee();

// Descreve um colaborador
void describeColaborator(Employee *data);

// Descreve colaborador de forma simples
void simpleDescribeColaborator(Employee *data);

// Criar um Funcionario
Employee *createEmployee(Employee *data, int code, char IBAN[], char name[], float salary, int age);

// Encontra um Funcionario
Employee *findOneEmployee(Employee *data, int code);

// Encontra todos os funcionários por departamentos
void findAllEmployees(Employee *data, int type);

// Encontra todos os funcionários desativados
void findAllDisabledEmployees(Employee *data);

// Encontra os funcionarios na reforma
void findAllOldEmployees(Employee *data);

// Atualiza o dado de um funcionário
void updateEmployee(Employee *employeeData, int code, char *IBAN, char *newName, float newSalary, int newState, int age);

// Atualiza a idade de todos funcionários
void updateEmployeeAge(Employee *employees);
//Elimina um funcionário da lista
Employee *deleteEmployee(Employee *data, int code);
//vincula o funcionáro ao departamento
Employee *employeeDepartment(Employee *data, Department *data_department);

// cria um bonus para o funcionario
Employee *createBonus(Employee *employee, int code, char *desc, float perc);
// elimina o bonus do funcionario
Employee *deleteBonus(Employee *employee, int code);

// Encontra todos bonus
void findAllBonus(Employee *data);

// cria uma falta para o funcionario
Employee *createAbsence(Employee *employee, int code, char *desc);

// elimina uma falta do funcionario
Employee *deleteAbsence(Employee *employee, int code);
//retorna o Next (próximo Employee da lista)
Employee *getNextEmployee(Employee *employee);

// Encontra todas as faltas
void findAllAbsence(Employee *data);
//encontra todas as faltas de uma lista de faltas do payroll
void findAllAbsenceFromPayroll(Absence *absence);
//Métodos Getters
// retorna o nome do funcionário
char *getEmployeeName(Employee *employee);
// retorna o código do funcionário
int getEmployeeCode(Employee *employee);
// retorna o estado do funcionário
int getEmployeeStatus(Employee *employee);
// retorna o nif da empresa
float getEmployeeSalary(Employee *employee);
// retorna IBAN do funcionário
char *getEmployeeIBAN(Employee *employee);
// Pega a idade de um colaborador
int getEmployeeAge(Employee *employee);
//retorna a pilha de falta de um funcionário
StackAbsence *getStackAbsence(Employee *employee);
//retorna a pilha de bônus de um funcionário
StackBonus *getStackBonus(Employee *employee);
// apresenta todos os funcionarios de um departamento específico
Department *findEmployeeByDepartment(Department *department, Employee *employee, int code);
// retorna o proximo funcionario da lista

// Mètodos Setters
//actualiza o nome do funcionário
void setEmployeeName(Employee *employee, char *value);
//actualiza o departamento do funcionário
void setEmployeeDepartment(Employee *employee, char *value);
//actualiza o código do funcionário
void setEmployeeCode(Employee *employee, int value);
//actualiza o estado do funcionário
void setEmployeeStatus(Employee *employee, int value);
//actualiza o salário do funcionário
void setEmployeeSalary(Employee *employee, float value);
//actualiza o iban do funcionário
void setEmployeeIBAN(Employee *employee, char *value);
//actualiza a idade do funcionário
void setEmployeeAge(Employee *employee, int value);
