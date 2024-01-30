//drfinição da estrutura da empresa
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
//retorna o nome da empresa
char *getCompanyName(Company *company);
//retorna o email da empresa
char *getCompanyEmail(Company *company);
//retorna o endereço da empresa
char *getCompanyAddress(Company *company);
//retorna o telefone da empresa
char *getCompanyPhone(Company *company);
//retorna o nif da empresa
char *getCompanyNIF(Company *company);

// Métodos Setter - usados para actualizar os valores das variáveis
//actualiza o nome da empresa
void setCompanyName(Company *company, char *value);
//actualiza o email da empresa
void setCompanyEmail(Company *company, char *value);
//actualiza o endereço da empresa
void setCompanyAddress(Company *company, char *value);
//actualiza o telefone da empresa
void setCompanyPhone(Company *company, char *value);
//actualiza o nif da empresa
void setCompanyNIF(Company *company, char *value);
