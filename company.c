#include "company.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define size 100
#define size_char 100
#define size_char_phone 10
#define size_char_nif 14
// definição struct empresa
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
    // abre o arquivo
    file = fopen("./files/empresa.txt", "r");

    if (file == NULL)
    {
        printf("Falha ao abrir Arquivo\n");
        return company;
    }

    char *email = (char *)malloc(sizeof(size)), *name = (char *)malloc(sizeof(size)), *address = (char *)malloc(sizeof(size));
    char *phone = (char *)malloc(sizeof(size_char_phone)), *nif = (char *)malloc(sizeof(size_char_nif));
    // coloca os valores dos arquivos nas variaveis, considerando espaços em branco
    fscanf(file, "%99[^\n]\n%99[^\n]\n%99[^\n]", name, email, address);
    fflush(stdin);
    fscanf(file, "%s", phone);
    fscanf(file, "%s", nif);
    // fscanf(file, "%d", countColaborator);

    // actualiza os valores nas variaveis da struct
    setCompanyName(company, name);
    setCompanyEmail(company, email);
    setCompanyAddress(company, address);
    setCompanyPhone(company, phone);
    setCompanyNIF(company, nif);

    // setCountColaborator(company, countColaborator);
    // fecha o arq
    fclose(file);

    return company;
}

// Criação ou Registro dos Dados da Empresa

Company *createCompany(Company *company, char *name, char *email, char *address, char *phone, char *nif)
{
    FILE *file;
    file = fopen("./files/empresa.txt", "w+");
    if (file == NULL)
    {
        printf("Falha ao abrir Arquivo\n\n");
        return company;
    }
    // envia os valores para o arquivo
    fprintf(file, "%s\n%s\n%s\n%s\n%s", name, email, address, phone, nif);

    fclose(file);

    readCompany(company);
    return company;
}
// actualiza os dados da empresa no arquivo e actualiza na TAD
Company *updateCompany(Company *company, char *name, char *email, char *address, char *phone, char *nif)
{
    FILE *file;
    file = fopen("./files/empresa.txt", "w");
    if (file == NULL)
    {
        printf("Falha ao abrir Arquivo\n\n");
        return company;
    }

    Company *auxCompany = company;

    name = !(strlen(name) > 1) ? auxCompany->name : name;
    email = !(strlen(email) > 1) ? auxCompany->email : email;
    nif = !(strlen(nif) > 1) ? auxCompany->nif : nif;
    address = !(strlen(address) > 1) ? auxCompany->address : address;
    phone = !(strlen(phone) > 1) ? auxCompany->phone : phone;

    setCompanyName(auxCompany, name);

    setCompanyEmail(auxCompany, email);

    setCompanyAddress(auxCompany, address);

    setCompanyPhone(auxCompany, phone);

    setCompanyNIF(auxCompany, nif);

    fprintf(file, "%s\n%s\n%s\n%s\n%s", name, email, address, phone, nif);

    fclose(file);

    return company;
}

// Métodos Getters
// retorna o nome da empresa
char *getCompanyName(Company *company)
{
    return company->name;
}
// retorna o email da empresa
char *getCompanyEmail(Company *company)
{
    return company->email;
}

// retorna o endereço da empresa
char *getCompanyAddress(Company *company)
{
    return company->address;
}
// retorna o telefone da empresa
char *getCompanyPhone(Company *company)
{
    return company->phone;
}
// retorna o nif da empresa
char *getCompanyNIF(Company *company)
{
    return company->nif;
}

// Mètodos Setters
// actualiza o email da empresa
void setCompanyEmail(Company *company, char *value)
{
    company->email = value;
}
// actualiza o nome da empresa
void setCompanyName(Company *company, char *value)
{
    company->name = value;
}
// actualiza o endereço da empresa
void setCompanyAddress(Company *company, char *value)
{
    company->address = value;
}
// actualiza o telefone da empresa
void setCompanyPhone(Company *company, char *value)
{
    company->phone = value;
}
// actualiza o nif da empresa
void setCompanyNIF(Company *company, char *value)
{
    company->nif = value;
}
