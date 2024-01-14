#include "company.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define size 50
#define size_char 50
#define size_char_phone 10
#define size_char_nif 14
struct company
{
    char *name;
    char *email;
    char *address;
    char *phone;
    char *nif;
};

// Inicialização da Empresa quando a mesma não possui algum registro

Company *initCompany()
{
    Company *newCompany = (Company *)malloc(sizeof(Company));
    if (newCompany)
    {
        newCompany->address = "";
        newCompany->phone = "";
        newCompany->name = "";
        newCompany->email = "";
        newCompany->nif = "";
    }
    else
        printf("Falha na Alocação de Empresa\n");

    return newCompany;
}

// Busca de Informações da Empresa apartir dos arquivos

Company *readCompany(Company *company)
{
    FILE *file;
    file = fopen("./files/empresa.txt", "r");
    if (file == NULL)
    {
        printf("Falha ao abrir Arquivo\n\n");
        return NULL;
    }

    char *email = (char*)malloc(sizeof(size)), *name = (char*)malloc(sizeof(size)), *address = (char*)malloc(sizeof(size));
    char *phone = (char*)malloc(sizeof(size_char_phone)), *nif = (char*)malloc(sizeof(size_char_nif));

    fscanf(file, "%s", name);
    fscanf(file, "%s", email);
    fscanf(file, "%s", address);
    fscanf(file, "%s", phone);
    fscanf(file, "%s", nif);
    //fscanf(file, "%d", countColaborator);

    setName(company, name);
    setEmail(company, email);
    setAddress(company, address);
    setPhone(company, phone);
    setNIF(company, nif);
    //setCountColaborator(company, countColaborator);

    fclose(file);

    return company;
}

// Criação ou Registro dos Dados da Empresa

int createCompany(char *name, char *email, char *address, char *phone, char *nif)
{
    FILE *file;
    file = fopen("./files/empresa.txt", "w+");
    if (file == NULL)
    {
        printf("Falha ao abrir Arquivo\n\n");
        return 0;
    }

    fprintf(file, "%s%s%s%s\n%s", name, email, address, phone, nif);

    fclose(file);
    return 1;
}

// Métodos Getters
// retorna o nome da empresa
char *getName(Company *company)
{
    return company->name;
}
// retorna o email da empresa
char *getEmail(Company *company)
{
    return company->email;
}

// retorna o endereço da empresa
char *getAddress(Company *company)
{
    return company->address;
}
// retorna o telefone da empresa
char *getPhone(Company *company)
{
    return company->phone;
}
// retorna o nif da empresa
char *getNIF(Company *company)
{
    return company->nif;
}

//Mètodos Setters
void setEmail(Company *company, char *value){
    company->email = value;
}
void setName(Company *company, char *value){
    company->name = value;
}
void setAddress(Company *company, char *value){
    company->address = value;
}
void setPhone(Company *company, char *value){
    company->phone = value;
}
void setNIF(Company *company, char *value){
    company->nif = value;
}

