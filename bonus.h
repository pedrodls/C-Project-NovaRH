typedef struct bonus Bonus;
typedef struct stackBonus StackBonus;

// Inicialização do bonus
StackBonus *initBonus();

// Criar um Bonus
StackBonus *pushBonus(StackBonus *head, char *desc, float perc);

//elimina um Bonus
Bonus *popBonus(StackBonus *head);

// Encontra todos Bonuss
void *findAllBonus(StackBonus *head);
