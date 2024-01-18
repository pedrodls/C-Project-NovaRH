typedef struct absence Absence;
typedef struct stackAbsence StackAbsence;

// Inicialização do absence
StackAbsence *initAbsence();

// Criar um Absence
StackAbsence *pushAbsence(StackAbsence *head, char *desc);

//elimina um Absence
StackAbsence *popAbsence(StackAbsence *head);

//retorna o topo de uma pilha de absence
Absence *getTopAbsence(StackAbsence *head);

//retorna a descrição do absence
char* getAbsenceDesc(Absence *absence);

int getAbsenceQtd(Absence *absence);

//retorna o proximo absence da lista
Absence *getNextAbsence(Absence *absence);

