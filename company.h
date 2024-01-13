typedef struct company Company;

//Inicialização da Empresa
Company *initCompany();
//Busca de Informações da Empresa apartid dos arquivos
Company *readCompany();
//Criação de Uma Empresa
Company *createCompany(char *name, char *email, char *address, char phone[9], char nif[12], int countColaborator);
//Actualização dos dados da Empresa
Company *updateCompany(char *name, char *email, char *address, char phone[9], char nif[12], int countColaborator);

FILE *openCompanyFile();
void closeCompanyFile(FILE *file);