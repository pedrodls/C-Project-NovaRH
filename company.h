typedef struct company Company;

//Inicialização da Empresa
Company *initCompany();
//Busca de Informações da Empresa apartir dos arquivos
Company *readCompany();
//Criação de Uma Empresa retorna 1 se sucesso 0 se falha
int createCompany(char *name, char *email, char *address, char *phone, char *nif);
//Actualização dos dados da Empresa
Company *updateCompany(char *name, char *email, char *address, char *phone, char *nif);
//Métodos Getters - usado para retornar os valores da variável
char *getName(Company *company);
char *getEmail(Company *company);
char *getAddress(Company *company);
char *getPhone(Company *company);
char *getNIF(Company *company);

//Métodos Setter - usados para actualizar os valores das variáveis
void setName(Company *company, char *value);
void setEmail(Company *company, char *value);
void setAddress(Company *company, char *value);
void setPhone(Company *company, char *value);
void setNIF(Company *company, char *value);




