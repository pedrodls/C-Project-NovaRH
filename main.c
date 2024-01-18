#include <stdlib.h>
#include <stdio.h>
#include "company.h"
#include "department.h"
#include "employee.h"
#include "payroll.h"
#include <string.h>
#include "year.h"

#define size 100
#define size_char 100
#define size_char_phone 10
#define size_char_nif 14

char *CONST_MONTH[] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

// Funçao pra pegar o menu principal
void menuMain(Company *company, Department *department, Employee *employee, QueueYear *year);

// Funcao pra pegar o menu do Admin
void menuAdmin(Company *company, Department *department, Employee *employee, QueueYear *year);

// Funcao pra pegar o menu da empresa
void menuCompany(Company *company, Department *department, Employee *employee, QueueYear *year);

//-----------------------EMPRESA-------------------------------

// Funcao pra pegar as opcçoes do menu do Admin
void menuCompanyOp(Company *company, Department *department, Employee *employee, QueueYear *year);

// Funcao para atualizar os dados da empresa
void updateCompanyFromMain(Company *company, Department *department, Employee *employee, QueueYear *year);

// Funcao pra criar empresa
void createCompanyFromMain(Company *company, Department *department, Employee *employee, QueueYear *year);

// Funcao pra verificar campos vazios
int required(char *value);

// Funcao pra mostrar dados da empresa
void showCompanyDataFromMain(Company *company, Department *department, Employee *employee, QueueYear *year);

//-----------------DEPARTAMENTOS--------------------------
// Menu Departamento
void menuDepartment(Company *company, Department *department, Employee *employee, QueueYear *year);

// Funcao pra criar Departamento
void createDepartmentFromMain(Company *company, Department *department, Employee *employee, QueueYear *year);

// Função para actualizar Departamento
void updateDepartmentFromMain(Company *company, Department *department, Employee *employee, QueueYear *year);

//-------------------FUNCIONÁRIOS--------------------------------------
void menuEmployee(Company *company, Department *department, Employee *employee, QueueYear *year);

void createEmployeeFromMain(Company *company, Department *department, Employee *employee, QueueYear *year);

void updateEmployeeFromMain(Company *company, Department *department, Employee *employee, QueueYear *year);

void createBonusFromMain(Employee *employee);

void createAbsenceFromMain(Employee *employee);

//---------------------------FOLHA DE PAGAMENTOS------------------------------
void menuPayroll(Company *company, Department *department, Employee *employee, QueueYear *year);

int main()
{
    Company *myCompany = initCompany();

    Department *myDepartments = initDepartment();

    Employee *myEmployees = initEmployee();

    QueueYear *year = initYear();

    // Cadastro do Ano
    year = enqueueYear(year, 2024);
    // Cadastro do Primeiro Mês do Ano
    enqueueMonth(getQueueMonth(year));

    // Função para pegar dados da empresa apartir do ficheiro
    readCompany(myCompany);

    menuMain(myCompany, myDepartments, myEmployees, year);
}

// Menu Principal para escolha de Login
void menuMain(Company *company, Department *department, Employee *employee, QueueYear *year)
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
        menuAdmin(company, department, employee, year);
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
void menuAdmin(Company *company, Department *department, Employee *employee, QueueYear *year)
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
        menuMain(company, department, employee, year);
        return;
    }

    fscanf(file, "%s", defaultEmail);
    fscanf(file, "%s", defaultPassword);

    if (!(strcmp(defaultEmail, email) == 0 && strcmp(defaultPassword, password) == 0))
    {
        printf("\n\nCredencias Invalidas!\n\n");
        system("timeout -t 5");
        menuMain(company, department, employee, year);
    }

    menuCompany(company, department, employee, year);
}

// Menu com as Funcionalidades do Admin
void menuCompany(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    fflush(stdin);

    char menu;
    int code;

    printf("\t Gerencie a sua Empresa com a NOVA-RH\n\n");
    printf("0000000000000000000000000000000000000000000000000000\n");
    printf("| 1  -  EMPRESA                                    |\n");
    printf("| 2  -  FUNCIONARIOS                               |\n");
    printf("| 3  -  DEPARTAMENTOS                              |\n");
    printf("| 4  -  FOLHAS DE PAGAMENTO                        |\n");
    printf("| 5  -  ADICIONAR BONUS A UM FUNCIONARIO           |\n");
    printf("| 6  -  ELIMINAR BONUS DE UM FUNCIONARIO           |\n");
    printf("| 7  -  MARCAR FALTA A UM FUNCIONARIO              |\n");
    printf("| 8  -  ELIMINAR FALTA A UM FUNCIONARIO            |\n");
    printf("| 9  -  VER FUNCIONARIOS NA APOSENTADORIA          |\n");
    printf("| 0  -  SAIR                                       |\n");
    printf("0000000000000000000000000000000000000000000000000000\n\nOpcao: ");

    fflush(stdin);

    scanf("%c", &menu);

    switch (menu)
    {
    case '1':
        menuCompanyOp(company, department, employee, year);
        break;
    case '2':
        menuEmployee(company, department, employee, year);
        break;
    case '3':
        menuDepartment(company, department, employee, year);
        break;

    case '4':
        menuPayroll(company, department, employee, year);
        break;

    case '5':
        createBonusFromMain(employee);
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuCompany(company, department, employee, year);
        break;
    case '6':

        system("cls");

        findAllEmployees(employee, 1);

        if (!employee)
        {
            printf("\nClique <Enter> para Continuar\n");
            system("pause>nul");
            menuCompany(company, department, employee, year);
        }

        printf("Codigo do Funcionario: ");
        scanf("%d", &code);

        employee = deleteBonus(employee, code);

        system("timeout -t 5");
        menuCompany(company, department, employee, year);

        break;

    case '7':

        createAbsenceFromMain(employee);
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuCompany(company, department, employee, year);
        break;

    case '8':

        system("cls");

        findAllEmployees(employee, 1);

        if (!employee)
        {
            printf("\nClique <Enter> para Continuar\n");
            system("pause>nul");
            menuCompany(company, department, employee, year);
        }

        printf("Codigo do Funcionario: ");
        scanf("%d", &code);

        employee = deleteAbsence(employee, code);

        system("timeout -t 5");
        menuCompany(company, department, employee, year);

        break;

    case '9':
        menuCompany(company, department, employee, year);
        break;

    case '0':
        menuMain(company, department, employee, year);
        break;
    default:
        menuCompany(company, department, employee, year);
        break;
    }
}
// Opç~oes da Empresa
void menuCompanyOp(Company *company, Department *department, Employee *employee, QueueYear *year)
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
        !file ? createCompanyFromMain(company, department, employee, year) : updateCompanyFromMain(company, department, employee, year);
        break;
    case '2':
        !required(getCompanyName(company)) ? showCompanyDataFromMain(company, department, employee, year) : menuCompany(company, department, employee, year);
        break;
    default:
        menuCompany(company, department, employee, year);
        break;
    }

    return;
}
// Actualização dos Dados da Empresa
void updateCompanyFromMain(Company *company, Department *department, Employee *employee, QueueYear *year)
{

    system("cls");

    fflush(stdin);

    char *email = (char *)malloc(sizeof(size)), *name = (char *)malloc(sizeof(size)), *address = (char *)malloc(sizeof(size));
    char *phone = (char *)malloc(sizeof(size_char_phone)), *nif = (char *)malloc(sizeof(size_char_nif));

    fflush(stdin);

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|                  Dados Atuais                \n");
    printf("| Nome     - %s                                \n", getCompanyName(company));
    printf("| Email    - %s                                \n", getCompanyEmail(company));
    printf("| Endereco - %s                                \n", getCompanyAddress(company));
    printf("| Telefone - %s                                \n", getCompanyPhone(company));
    printf("| NIF      - %s                                \n", getCompanyNIF(company));
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

    return menuCompanyOp(company, department, employee, year);
}
// Criação da Empresa
void createCompanyFromMain(Company *company, Department *department, Employee *employee, QueueYear *year)
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
        return createCompanyFromMain(company, department, employee, year);
    }

    fflush(stdin);

    company = createCompany(company, name, email, address, phone, nif);

    printf("\n\nEmpresa criada com sucesso!\n\n");

    system("timeout -t 5\n\n");

    return menuCompanyOp(company, department, employee, year);
}
// Apresentação dos Dados da Empresa
void showCompanyDataFromMain(Company *company, Department *department, Employee *employee, QueueYear *year)
{

    system("cls");

    fflush(stdin);

    char menu;

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|                  Dados Atuais                \n");
    printf("| Nome     - %s                                \n", getCompanyName(company));
    printf("| Email    - %s                                \n", getCompanyEmail(company));
    printf("| Endereco - %s                                \n", getCompanyAddress(company));
    printf("| Telefone - %s                                \n", getCompanyPhone(company));
    printf("| NIF      - %s                                \n", getCompanyNIF(company));
    printf("000000000000000000000000000000000000000000000000\n\n");
    printf("0 - Sair \n\n");

    printf("Opcao: ");

    fflush(stdin);

    scanf("%c", &menu);

    switch (menu)
    {
    default:
        menuCompanyOp(company, department, employee, year);
        break;
    }
}
// Menu do Departamento
void menuDepartment(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    fflush(stdin);

    char menu;

    printf("\t Gerencie a sua Empresa com a NOVA-RH\n\n");
    printf("000000000000000000000000000000000000000000000000\n");
    printf("| 1 - REGISTAR DEPARTAMENTO                      |\n");
    printf("| 2 - ACTUALIZAR DEPARTMENTO                     |\n");
    printf("| 3 - LISTAR DEPARTAMENTOS                       |\n");
    printf("| 4 - LISTAR FUNCIONARIOS POR DEPARTAMENTO       |\n");
    printf("| 5 - ELIMINAR DEPARTAMENTOS                     |\n");
    printf("| 0 - SAIR                                       |\n");
    printf("000000000000000000000000000000000000000000000000\n\nOpcao: ");

    fflush(stdin);

    scanf("%c", &menu);
    int code;
    switch (menu)
    {
    case '1':
        createDepartmentFromMain(company, department, employee, year);
        break;
    case '2':
        updateDepartmentFromMain(company, department, employee, year);
        break;
    case '0':
        menuCompany(company, department, employee, year);
        break;
    case '3':
        findAllDepartments(department);
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuDepartment(company, department, employee, year);
        break;
    case '4':
        findAllDepartments(department);
        if (getDepartmentCode(department) > 0)
        {
            printf("Codigo do Departamento: ");
            scanf("%d", &code);
            department = findEmployeeByDepartment(department, employee, code);
        }
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuDepartment(company, department, employee, year);
        break;
    case '5':
        findAllDepartments(department);
        printf("Codigo do Departamento: ");
        scanf("%d", &code);
        department = deleteDepartment(department, code);
        system("timeout -t 5");
        menuDepartment(company, department, employee, year);
        break;
    default:
        menuDepartment(company, department, employee, year);
        break;
    }
}
// Criação do Departamento
void createDepartmentFromMain(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    char *name = (char *)malloc(sizeof(size));

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
        return createDepartmentFromMain(company, department, employee, year);
    }

    department = createDepartment(department, name);

    printf("\n\nDepartamento criada com sucesso!\n\n");

    system("timeout -t 5\n\n");

    return menuDepartment(company, department, employee, year);
}
// Actualização do Departamento
void updateDepartmentFromMain(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    int code;

    printf("000000000000000000000000000000000000000000000000\n");
    printf("              Actualizar Departmento               \n");
    findAllDepartments(department);
    printf("000000000000000000000000000000000000000000000000\n\n");

    printf("Codigo do Departmento: ");
    scanf("%d", &code);

    department = updateDepartment(department, code);

    system("timeout -t 5\n\n");

    return menuDepartment(company, department, employee, year);
}

void menuEmployee(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    fflush(stdin);

    char menu;

    printf("\t Gerencie a sua Empresa com a NOVA-RH\n\n");
    printf("000000000000000000000000000000000000000000000000\n");
    printf("| 1 - REGISTAR FUNCIONARIO                       |\n");
    printf("| 2 - ACTUALIZAR FUNCIONARIO                     |\n");
    printf("| 3 - LISTAR FUNCIONARIOS                        |\n");
    printf("| 4 - VINCULAR FUNCIONARIO A DEPARTAMENTO        |\n");
    printf("| 5 - ELIMINAR FUNCIONARIO                       |\n");
    printf("| 0 - SAIR                                       |\n");
    printf("000000000000000000000000000000000000000000000000\n\nOpcao: ");

    fflush(stdin);

    scanf("%c", &menu);
    int code;
    switch (menu)
    {
    case '1':
        createEmployeeFromMain(company, department, employee, year);
        break;
    case '2':
        updateEmployeeFromMain(company, department, employee, year);
        break;
    case '3':
        findAllEmployees(employee, 0);
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuEmployee(company, department, employee, year);
        break;
    case '4':
        employeeDepartment(employee, department);
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuEmployee(company, department, employee, year);
        break;
    case '0':
        menuCompany(company, department, employee, year);
        break;
    default:
        menuEmployee(company, department, employee, year);
        break;
    }
}

// Registro de um novo funcionário
void createEmployeeFromMain(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    char *name = (char *)malloc(sizeof(size));
    float salary;

    fflush(stdin);

    // myEmployee = createEmployee(myEmployee,1,1,"bruno mateus", 5000);

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|              Dados Necessarios               |\n");
    printf("| Nome                                         |\n");
    printf("| Salario                                      |\n\n");
    printf("000000000000000000000000000000000000000000000000\n\n");

    printf("Nome: ");
    fgets(name, size_char, stdin);
    name[strcspn(name, "\n")] = '\0';

    fflush(stdin);

    printf("Salario: ");
    scanf("%f", &salary);

    if (required(name))
    {
        system("timeout -t 5\n\n");
        return createEmployeeFromMain(company, department, employee, year);
    }

    employee = createEmployee(employee, getEmployeeCode(employee) + 1, name, salary);

    system("timeout -t 5\n\n");

    return menuEmployee(company, department, employee, year);
}

// Adicionar bonus a um funcionario
void createBonusFromMain(Employee *employee)
{

    system("cls");

    char *desc = (char *)malloc(sizeof(size));
    float perc;
    int code;

    findAllEmployees(employee, 1);

    if (!employee)
        return;

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|              Dados Necessarios               |\n");
    printf("| Descricao                                    |\n\n");
    printf("| Percentagem                                  |\n\n");
    printf("| Codigo do Funcionario                        |\n\n");
    printf("000000000000000000000000000000000000000000000000\n\n");

    fflush(stdin);

    printf("Descricao: ");
    fgets(desc, size_char, stdin);
    desc[strcspn(desc, "\n")] = '\0';

    fflush(stdin);

    printf("Percentagem: ");
    scanf("%f", &perc);
    fflush(stdin);

    printf("Codigo do funcionario: ");
    scanf("%d", &code);

    fflush(stdin);

    if (required(desc) || !(perc >= 0.0 && perc <= 100.0))
    {
        printf("Por favor, verifique bem os campos preenchidos!");
    }
    else
    {
        createBonus(employee, code, desc, perc);
    }
}

// Adicionar falta a um funcionario
void createAbsenceFromMain(Employee *employee)
{

    system("cls");

    char *desc = (char *)malloc(sizeof(size));
    float perc;
    int code;

    findAllEmployees(employee, 1);

    if (!employee)
        return;

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|              Dados Necessarios               |\n");
    printf("| Descricao                                    |\n\n");
    printf("| Codigo do Funcionario                        |\n\n");
    printf("000000000000000000000000000000000000000000000000\n\n");

    fflush(stdin);

    printf("Descricao: ");
    fgets(desc, size_char, stdin);
    desc[strcspn(desc, "\n")] = '\0';

    fflush(stdin);

    printf("Codigo do funcionario: ");
    scanf("%d", &code);

    fflush(stdin);

    if (required(desc) || !(perc >= 0.0 && perc <= 100.0))
    {
        printf("Por favor, verifique bem os campos preenchidos!");
    }
    else
    {
        createAbsence(employee, code, desc);
    }
}
// Actualização dos dadods de um funcionário
void updateEmployeeFromMain(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    int code;

    fflush(stdin);

    findAllEmployees(employee, 1);

    if (!employee)
        return;

    printf("000000000000000000000000000000000000000000000000\n");
    printf("|              Dados Necessarios               |\n");
    printf("| Nome                                         |\n");
    printf("| Estado                                       |\n");
    printf("| Salario                                      |\n\n");
    printf("000000000000000000000000000000000000000000000000\n\n");

    printf("\nCodigo do Funcionario: ");
    scanf("%d", &code);

    employee = updateEmployee(employee, code);

    system("timeout -t 5\n\n");

    return menuEmployee(company, department, employee, year);
}

int required(char *value)
{

    if (!(strlen(value) > 1))
    {
        printf("\nCampos invalidos! ");

        return !(strlen(value) > 1);
    }

    return 0;
}

void menuPayroll(Company *company, Department *department, Employee *employee, QueueYear *year)
{
    system("cls");

    fflush(stdin);

    char menu;
    int code;

    printf("\t Gerencie a sua Empresa com a NOVA-RH\n\n");
    printf("0000000000000000000000000000000000000000000000000000\n");
    printf(" 1  -  EXECUTAR FOLHA PAGAMENTO (%d/%s)           \n", getCurrentYear(year), getMonthName(getCurrentMonth(getQueueMonth(year))));
    printf(" 2  -  CONSULTAR ULTIMA FOLHA DE PAGAMENTO        \n");
    printf(" 3  -  CONSULTAR HISTORICO DE FOLHA PAGAMENTO     \n");
    printf(" 4  -  EDITAR FOLHA PAGAMENTO                     \n");
    printf(" 0  -  SAIR                                       \n");
    printf("0000000000000000000000000000000000000000000000000000\n\nOpcao: ");

    fflush(stdin);

    scanf("%c", &menu);

    switch (menu)
    {
    case '1':
        if (!employee)
            printf("NAO EXISTE FUNCIONARIOS\n");
        else
        {
            createPayroll(employee, year);
        }
        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuPayroll(company, department, employee, year);
        break;
    case '2':
        describePayroll(getLastPayroll(getCurrentMonth(getQueueMonth(year))));

        printf("\nClique <Enter> para Continuar\n");
        system("pause>nul");
        menuPayroll(company, department, employee, year);
        break;

    case '0':
        menuCompany(company, department, employee, year);
        break;
    default:
        menuPayroll(company, department, employee, year);
        break;
    }
}