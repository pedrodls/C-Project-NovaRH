#include <stdio.h>
#include "company.h"
#include <stdlib.h>

struct company{
    char *name, *email, *address;
    char phone[9], nif[12];
    int countColaborator;
};


//Inicialização da Empresa quando a mesma não possui algum registro
/*
Company *initCompany(){
    Company *newCompany = (Company *)malloc(sizeof(Company));
    if(newCompany){
        newCompany->countColaborator = 0;
        return newCompany;
    }else
        printf("Falha na Alocação de Empresa\n");  
    return NULL;
}
*/
//Busca de Informações da Empresa apartid dos arquivos
Company *readCompany(){
    Company *newCompany = (Company *)malloc(sizeof(Company));
    if(newCompany){
      /* FILE *files = fopen("./files/empresa.txt","a+");
        char *data;
        while(!feof){
            fscanf(files, "%s",data);
            printf("%s\n", data);
        }

        fclose(files);
        */
        //Lógica de Leitura de Arquivos

        return newCompany;
    }else
        //printf("Falha na Alocação de Empresa\n");  
    return NULL;
}
/*
FILE *openCompanyFile(){
    FILE *file;
    file = fopen("./files/empresa.txt","a+");
    if(!file) {
        printf("Falha ao abrir Arquivo\n\n");
        return NULL; //falha no ficheiro
    }
    return file;    
}
void closeCompanyFile(FILE *file){
    fclose(file);
}
*/