
typedef struct department Department;

//Inicialização do departamento da empresa
Department *initDepartment();

// Criar um departamento
Department *createDepartment(Department *head, char *name);

// Descreve um departamento
void *describeDepartment(Department *data);

// Encontra um departamento
Department *findOneDepartment(Department *data, int code);

// Encontra todos departamentos
void *findAllDepartments(Department *data);

// Atualiza um departamento
Department *updateDepartment(Department *data, int code);

//Elimina um departamento
Department *deleteDepartment(Department *data, int code);

//Manda o proximo departamento
Department *nextDepartment(Department *data);

// retorna o nome do funcionário
char *getDepartmentName(Department *data);
// retorna o código do funcionário
int getDepartmentCode(Department *data);

// Incrementar colaborador num departamento
Department *incrementEmployeeDepartment(Department *data);

