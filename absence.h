typedef struct absence Absence;
typedef struct stackAbsence StackAbsence;

// Inicialização do absence
StackAbsence *initAbsence();

// Criar um absence
StackAbsence *pushAbsence(StackAbsence *head, char *desc);

//elimina um absence
Absence *popAbsence(StackAbsence *head);

// Encontra todos absences
void *findAllAbsence(StackAbsence *head);
