typedef struct department Department;

//Inicialização do departamento da empresa
Department *initDepartment();

// Criar um departamento
Department *createDepartment(Department *head, char *name);

// Descreve um departamento
void *describeDepartment(Department *data);

// Encontra um departamento
void *findOneDepartment(Department *data, int code);

// Encontra todos departamentos
void *findAllDepartments(Department *data);

// Atualiza um departamento
void *updateDepartment(Department *data, int code);

// Busca de Informações da Empresa apartid dos arquivos
Department *readDepartment();
