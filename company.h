typedef struct company Company;

// Inicialização da Empresa
Company *initCompany();
// Busca de Informações da Empresa apartir dos arquivos
Company *readCompany();
// Criação de Uma Empresa retorna 1 se sucesso 0 se falha
Company *createCompany(Company *company, char *name, char *email, char *address, char *phone, char *nif);
// Actualização dos dados da Empresa
Company *updateCompany(Company *company, char *name, char *email, char *address, char *phone, char *nif);
// Métodos Getters - usado para retornar os valores da variável
char *getCompanyName(Company *company);
char *getCompanyEmail(Company *company);
char *getCompanyAddress(Company *company);
char *getCompanyPhone(Company *company);
char *getCompanyNIF(Company *company);

// Métodos Setter - usados para actualizar os valores das variáveis
void setCompanyName(Company *company, char *value);
void setCompanyEmail(Company *company, char *value);
void setCompanyAddress(Company *company, char *value);
void setCompanyPhone(Company *company, char *value);
void setCompanyNIF(Company *company, char *value);
