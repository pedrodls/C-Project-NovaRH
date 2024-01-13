#include "company.h";
#include <stdlib.h>

struct company{
    char *name, *email, *address;
    char phone[9], nif[12];
    int countColaborator;
};

//Inicialização da Empresa quando a mesma não possui algum registro
Company *initCompany(){
    Company *newCompany = (Company *)malloc(sizeof(Company));
    if(newCompany){
        newCompany->countColaborator = 0;
        return newCompany;
    }else
        printf("Falha na Alocação de Empresa\n");  
    return NULL;
}

//Busca de Informações da Empresa apartid dos arquivos
Company *readCompany(){
    Company *newCompany = (Company *)malloc(sizeof(Company));
    if(newCompany){

        //Lógica de Leitura de Arquivos

        return newCompany;
    }else
        printf("Falha na Alocação de Empresa\n");  
    return NULL;
}