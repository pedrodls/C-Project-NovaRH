#include "./department.h"

typedef struct employee Employee;

Employee *initEmployee();

// Descreve um colaborador
void describeColaborator(Employee *data);

//Descreve colaborador de forma simples
void simpleDescribeColaborator(Employee *data);

// Criar um Funcionario
Employee *createEmployee(Employee *data, int code, char *name, float salary);

// Encontra um Funcionario
Employee *findOneEmployee(Employee *data, int code);

// Encontra todos departamentos
void findAllEmployees(Employee *data, int type);

// Atualiza o dado de um funcionário
Employee *updateEmployee(Employee *employee, int code);

Employee *deleteEmployee(Employee *data, int code);

Employee *employeeDepartment(Employee *data, Department *data_department);

//cria um bonus para o funcionario
Employee *createBonus(Employee *employee, int code, char *desc, float perc);
//elimina o bonus do funcionario
Employee *deleteBonus(Employee *employee, int code);

//Encontra todos bonus
void findAllBonus(Employee *data);

//cria uma falta para o funcionario
Employee *createAbsence(Employee *employee, int code, char *desc);

//elimina uma falta do funcionario
Employee *deleteAbsence(Employee *employee, int code);

//Encontra todas as faltas
void findAllAbsence(Employee *data);

// retorna o nome do funcionário
char *getEmployeeName(Employee *employee);
// retorna o código do funcionário
int getEmployeeCode(Employee *employee);
// retorna o estado do funcionário
int getEmployeeStatus(Employee *employee);
// retorna o nif da empresa
float getEmployeeSalary(Employee *employee);


//apresenta todos os funcionarios de um departamento específico
Department *findEmployeeByDepartment(Department *department, Employee *employee ,int code);
//retorna o proximo funcionario da lista

// Mètodos Setters
void setEmployeeName(Employee *employee, char *value);
void setEmployeeDepartment(Employee *employee, char *value);
void setEmployeeCode(Employee *employee, int value);
void setEmployeeStatus(Employee *employee, int value);
void setEmployeeSalary(Employee *employee, float value);