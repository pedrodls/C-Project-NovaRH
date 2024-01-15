#include "./department.h"

typedef struct employee Employee;

Employee *initEmployee();

// Descreve um colaborador
void describeColaborator(Employee *data);

// Criar um Funcionario
Employee *createEmployee(Employee *data, int code, char *name, float salary);


// Encontra um Funcionario
Employee *findOneEmployee(Employee *data, int code);

// Encontra todos departamentos
void findAllEmployees(Employee *data);

// Atualiza o dado de um funcionário
Employee *updateEmployee(Employee *employee, int code);

Employee *deleteEmployee(Employee *data, int code);

Employee *employeeDepartment(Employee *data, Department *data_department);

// retorna o nome do funcionário
char *getEmployeeName(Employee *employee);
// retorna o código do funcionário
int getEmployeeCode(Employee *employee);
// retorna o estado do funcionário
int getEmployeeStatus(Employee *employee);
// retorna o nif da empresa
float getEmployeeSalary(Employee *employee);
// Mètodos Setters
void setEmployeeName(Employee *employee, char *value);
void setEmployeeDepartment(Employee *employee, char *value);
void setEmployeeCode(Employee *employee, int value);
void setEmployeeStatus(Employee *employee, int value);
void setEmployeeSalary(Employee *employee, float value);