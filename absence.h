//definição das struct das faltas
typedef struct absence Absence;
typedef struct stackAbsence StackAbsence;

// Inicialização do absence
StackAbsence *initAbsence();

// Criar um Absence
StackAbsence *pushAbsence(StackAbsence *head, char *desc);

//elimina um Absence
Absence *popAbsence(StackAbsence *head);

//Métodos Getters

//retorna o topo de uma pilha de falta
Absence *getTopAbsence(StackAbsence *head);

//retorna a descrição da falta de um nó
char* getAbsenceDesc(Absence *absence);

//retorna a quantidade de faltas de um nó
int getAbsenceQtd(Absence *absence);

//retorna o proximo absence da lista
Absence *getNextAbsence(Absence *absence);

//Métodos Setters

//actualiza a descrição de uma falta
void setAbsenceDesc(Absence *absence, char *desc);
//actualiza a qtd de falta de um nó
void setAbsenceQtd(Absence *absence, int qtd);
//actualiza o next de um nó
void setAbsenceNext(Absence *oldAbsence, Absence *newAbsence);
//apresenta todas as faltas de uma lista de faltas
void findAbsence(Absence *absence);

