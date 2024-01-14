#include <stdlib.h>
#include <stdio.h>
#include "company.h"
#include "department.h"
#include <string.h>

#define size_char 50
#define size_char_phone 10
#define size_char_nif 14

int main()
{

    Company *myCompany = initCompany();

    char *name = (char *)malloc(size_char);
    char *email = (char *)malloc(size_char);
    char *address = (char *)malloc(size_char);
    char *phone = (char *)malloc(size_char_phone);
    char *nif = (char *)malloc(size_char_nif);

    // Allocate memory for strings
    if (!name || !email || !address || !phone || !nif || !myCompany)
    {
        printf("Falha ao alocar Memoria\n");
        return 1;
    }

        printf("Nome: ");
        fgets(name, size_char, stdin);
        fflush(stdin);

        printf("Email: ");
        fgets(email, size_char, stdin);
        fflush(stdin);

        printf("Endereco: ");
        fgets(address, size_char, stdin);
        fflush(stdin);

        printf("Telefone: ");
        fgets(phone, size_char_phone, stdin);

        fflush(stdin);

        printf("NIF: ");
        fgets(nif, size_char_nif, stdin);
        fflush(stdin);

    if (createCompany(name, email, address, phone, nif, 0))
    {
        printf("Cadastrado com Sucesso\n");
    }
    else
    {
        printf("Falha ao Cadastrar\n");
    }
    /*
     */
    return 0;
}