#include <stdlib.h>
#include <stdio.h>
#include "company.h"
#include "department.h"
#include <string.h>

#define size 100
#define size_char 100
#define size_char_phone 10
#define size_char_nif 14

// Funçao pra pegar o menu principal
void menuMain(Company *company, Department *department);

// Funcao pra pegar o menu do Admin
void menuAdmin(Company *company, Department *department);

// Funcao pra pegar o menu da empresa
void menuCompany(Company *company, Department *department);

// Funcao pra pegar as opcçoes do menu do Admin
void menuCompanyOp(Company *company, Department *department);

// Funcao para atualizar os dados da empresa
void updateCompanyFromMain(Company *company, Department *department);

// Funcao pra criar empresa
void createCompanyFromMain(Company *company, Department *department);

// Funcao pra verificar campos vazios
int required(char *value);

// Funcao pra mostrar dados da empresa
void showCompanyDataFromMain(Company *company, Department *department);

//-----------------DEPARTAMENTOS--------------------------
// Menu Departamento
void menuDepartment(Company *company, Department *department);

// Funcao pra criar Departamento
void createDepartmentFromMain(Company *company, Department *department);

int main()
{
    Company *myCompany = initCompany();

    Department *myDepartments = initDepartment();

    // Função para pegar dados da empresa apartir do ficheiro
    readCompany(myCompany);

    menuMain(myCompany, myDepartments);
}

// Menu Principal para escolha de Login
void menuMain(Company *company, Department *department)
{
    system("cls");

    fflush(stdin);

    char menu;

    printf("\tBEM-VINDO AO NOVA-RH\n\n");
    printf("\t\tLOGIN\n");
    printf("000000000000000000000000000000000000000000000000\n");
    printf("| 1 - ADMIN                                    |\n");
    printf("| 2 - FUNCIONARIO                              |\n");
    printf("| 0 - SAIR                                     |\n");
    printf("000000000000000000000000000000000000000000000000\n\nOpcao: ");
    fflush(stdin);
    scanf("%c", &menu);

    switch (menu)
    {
    case '1':
        menuAdmin(company, department);
        break;

    case '0':
        printf("\n\nVolte sempre!\n");
        break;
    default:
        printf("\n\nVolte sempre!\n");
        break;
    }
}

// Menu do Login do Admin
void menuAdmin(Company *company, Department *department)
{
    system("cls");

    fflush(stdin);

    char email[size_char], password[size_char],
        defaultEmail[size_char], defaultPassword[size_char];

    printf("\t\tLOGIN\n");
    printf("000000000000000000000000000000000000000000000000\n");

    printf(" Email: ");
    fflush(stdin);
    fgets(email, size_char, stdin);
    email[strcspn(email, "\n")] = '\0';

    fflush(stdin);
    printf(" Palavra-Passe: ");
    fgets(password, size_char, stdin);
    password[strcspn(password, "\n")] = '\0';
    printf("000000000000000000000000000000000000000000000000\n\n");

    FILE *file = fopen("./files/credential.txt", "r");

    if (!file)
    {
        printf("Erro ao abrir Arquivo\n");
        system("timeout -t 5");
        menuMain(company, department);
        return;
    }

    fscanf(file, "%s", defaultEmail);
    fscanf(file, "%s", defaultPassword);

    if (!(strcmp(defaultEmail, email) == 0 && strcmp(defaultPassword, password) == 0))
    {
        printf("\n\nCredencias Invalidas!\n\n");
        system("timeout -t 5");
        menuMain(company, department);
    }

    menuCompany(company, department);
}

// Menu com as Funcionalidades do Admin
void menuCompany(Company *company, Department *department)
{
    system("cls");

    fflush(stdin);

    char menu;

    printf("\t Gerencie a sua Empresa com a NOVA-RH\n\n");
    printf("000000000000000000000000000000000000000000000000\n");
    printf("| 1 - EMPRESA                                    |\n");
    printf("| 2 - FUNCIONARIOS                               |\n");
    printf("| 3 - DEPARTAMENTOS                              |\n");
    printf("| 4 - FERIAS                                     |\n");
    printf("| 5 - FALTAS                                     |\n");
    printf("| 6 - FOLHAS DE PAGAMENTO                        |\n");
    printf("| 0 - SAIR                                       |\n");
    printf("000000000000000000000000000000000000000000000000\n\nOpcao: ");

    fflush(stdin);

    scanf("%c", &menu);

    switch (menu)
    {
    case '1':
        menuCompanyOp(company, department);
        break;
    case '0':
        menuMain(company, department);
        break;
    case '3':
        menuDepartment(company,department);
        break;
    default:
        menuCompany(company, department);
        break;
    }
}

void menuCompanyOp(Company *company, Department *department)
{

    system("cls");

    fflush(stdin);

    char menu;

    FILE *file;

    file = fopen("./files/empresa.txt", "r");

    fclose(file);

    fflush(stdin);

    printf("\t Gerencie a sua Empresa com a NOVA-RH\n\n");
    printf("000000000000000000000000000000000000000000000000\n");

    if (!file)
    {
        printf("| 1 - REGISTAR DADOS DA EMPRESA                  |\n");
    }
    else
    {
        printf("| 1 - ACTUALIZAR DADOS DA EMPRESA                |\n");
        printf("| 2 - VER DADOS DA EMPRESA                       |\n");
    }

    printf("| 0 - SAIR                                       |\n");
    printf("000000000000000000000000000000000000000000000000\n\nOpcao: ");

    fflush(stdin);

    scanf("%c", &menu);

    switch (menu)
    {
    case '1':
        !file ? createCompanyFromMain(company, department) : updateCompanyFromMain(company, department);
        break;
    case '2':
        !required(getName(company)) ? showCompanyDataFromMain(company, department) : menuCompany(company, department);
        break;
    default:
        menuCompany(company, department);
        break;
    }

    return;
}

void updateCompanyFromMain(Company *company, Department *department)
{

    system("cls");

    fflush(stdin);

    char *email = (char *)malloc(sizeof(size)), *name = (char *)malloc(sizeof(size)), *address = (char *)malloc(sizeof(size));
    char *phone = (char *)malloc(sizeof(size_char_phone)), *nif = (char *)malloc(sizeof(size_char_nif));

    fflush(stdin);

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|                  Dados Atuais                \n");
    printf("| Nome     - %s                                \n", getName(company));
    printf("| Email    - %s                                \n", getEmail(company));
    printf("| Endereco - %s                                \n", getAddress(company));
    printf("| Telefone - %s                                \n", getPhone(company));
    printf("| NIF      - %s                                \n", getNIF(company));
    printf("000000000000000000000000000000000000000000000000\n\n");
    printf("Clique Enter caso nao deseja atualizar o campo!\n\n");

    fflush(stdin);

    printf("Nome: ");
    fgets(name, size_char, stdin);
    name[strcspn(name, "\n")] = '\0';

    fflush(stdin);

    printf("Email: ");
    fgets(email, size_char, stdin);
    email[strcspn(email, "\n")] = '\0';
    fflush(stdin);

    printf("Endereco: ");
    fgets(address, size_char, stdin);
    address[strcspn(address, "\n")] = '\0';

    fflush(stdin);

    printf("Telefone: ");
    fgets(phone, size_char_phone, stdin);
    phone[strcspn(phone, "\n")] = '\0';

    fflush(stdin);

    printf("NIF: ");
    fgets(nif, size_char_nif, stdin);
    nif[strcspn(nif, "\n")] = '\0';

    fflush(stdin);

    company = updateCompany(company, name, email, address, phone, nif);

    printf("\n\nDados atualizados com sucesso!\n\n");

    system("timeout -t 5\n\n");

    return menuCompanyOp(company, department);
}

void createCompanyFromMain(Company *company, Department *department)
{

    system("cls");

    fflush(stdin);

    char *email = (char *)malloc(sizeof(size)), *name = (char *)malloc(sizeof(size)), *address = (char *)malloc(sizeof(size));
    char *phone = (char *)malloc(sizeof(size_char_phone)), *nif = (char *)malloc(sizeof(size_char_nif));

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|              Dados Necessarios               |\n");
    printf("| Nome                                         |\n");
    printf("| Email                                        |\n");
    printf("| Endereco                                     |\n");
    printf("| Telefone                                     |\n");
    printf("| NIF                                          |\n");
    printf("000000000000000000000000000000000000000000000000\n\n");

    fflush(stdin);

    printf("Nome: ");
    fgets(name, size_char, stdin);
    name[strcspn(name, "\n")] = '\0';

    fflush(stdin);

    printf("Email: ");
    fgets(email, size_char, stdin);
    email[strcspn(email, "\n")] = '\0';
    fflush(stdin);

    printf("Endereco: ");
    fgets(address, size_char, stdin);
    address[strcspn(address, "\n")] = '\0';

    fflush(stdin);

    printf("Telefone: ");
    fgets(phone, size_char_phone, stdin);
    phone[strcspn(phone, "\n")] = '\0';

    fflush(stdin);

    printf("NIF: ");
    fgets(nif, size_char_nif, stdin);
    nif[strcspn(nif, "\n")] = '\0';

    if (required(name) || required(email) || required(address) || required(phone) || required(nif))
    {

        system("timeout -t 5\n\n");
        return createCompanyFromMain(company, department);
    }

    fflush(stdin);

    company = createCompany(company, name, email, address, phone, nif);

    printf("\n\nEmpresa criada com sucesso!\n\n");

    system("timeout -t 5\n\n");

    return menuCompanyOp(company, department);
}

void showCompanyDataFromMain(Company *company, Department *department)
{

    system("cls");

    fflush(stdin);

    char menu;

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|                  Dados Atuais                \n");
    printf("| Nome     - %s                                \n", getName(company));
    printf("| Email    - %s                                \n", getEmail(company));
    printf("| Endereco - %s                                \n", getAddress(company));
    printf("| Telefone - %s                                \n", getPhone(company));
    printf("| NIF      - %s                                \n", getNIF(company));
    printf("000000000000000000000000000000000000000000000000\n\n");
    printf("0 - Sair \n\n");

    printf("Opcao: ");

    fflush(stdin);

    scanf("%c", &menu);

    switch (menu)
    {
    default:
        menuCompanyOp(company, department);
        break;
    }
}

void menuDepartment(Company *company, Department *department)
{
    system("cls");

    fflush(stdin);

    char menu;

    printf("\t Gerencie a sua Empresa com a NOVA-RH\n\n");
    printf("000000000000000000000000000000000000000000000000\n");
    printf("| 1 - REGISTAR DEPARTAMENTO                      |\n");
    printf("| 2 - ACTUALIZAR DEPARTMENTO                     |\n");
    printf("| 3 - LISTAR DEPARTAMENTOS                       |\n");
    printf("| 4 - VER DEPARTAMENTO                           |\n");
    printf("| 5 - ELIMINAR DEPARTAMENTOS                     |\n");
    printf("| 0 - SAIR                                       |\n");
    printf("000000000000000000000000000000000000000000000000\n\nOpcao: ");

    fflush(stdin);

    scanf("%c", &menu);

    switch (menu)
    {
    case '1':
        createDepartmentFromMain(company, department);
        break;
    case '0':
        menuMain(company, department);
        break;
    case '3':
        findAllDepartments(department);
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuDepartment(company,department);
    break;
    default:
        menuCompany(company, department);
        break;
    }
}

void createDepartmentFromMain(Company *company, Department *department)
{
    system("cls");

    fflush(stdin);

    char  *name = (char *)malloc(sizeof(size));

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|              Dados Necessarios               |\n");
    printf("| Nome                                         |\n\n");
    printf("000000000000000000000000000000000000000000000000\n\n");

    fflush(stdin);

    printf("Nome: ");
    fgets(name, size_char, stdin);
    name[strcspn(name, "\n")] = '\0';

    fflush(stdin);

    if (required(name))
    {
        system("timeout -t 5\n\n");
        return createDepartmentFromMain(company, department);
    }

    department = createDepartment(department, name);

    printf("\n\nDepartamento criada com sucesso!\n\n");

    system("timeout -t 5\n\n");

    return menuDepartment(company, department);
}

int required(char *value)
{

    if (!(strlen(value) > 1))
    {
        printf("\nCampos invalidos!: [%s]!");

        return !(strlen(value) > 1);
    }

    return 0;
}
