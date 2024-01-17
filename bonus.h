typedef struct bonus Bonus;
typedef struct stackBonus StackBonus;

// Inicialização do bonus
StackBonus *initBonus();

// Criar um Bonus
StackBonus *pushBonus(StackBonus *head, char *desc, float perc);

//elimina um Bonus
StackBonus *popBonus(StackBonus *head);

//retorna o topo de uma pilha de bonus
Bonus *getTopBonus(StackBonus *head);

//retorna a descrição do bonus
char* getBonusDesc(Bonus *bonus);
//retorna a percentagem do bonus
float getBonusPerc(Bonus *bonus);
//retorna o proximo bonus da lista
Bonus *getNextBonus(Bonus *bonus);
