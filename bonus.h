//definição das estruturas de bonus
typedef struct bonus Bonus;
typedef struct stackBonus StackBonus;

// Inicialização do bonus
StackBonus *initBonus();

// Criar um Bonus
StackBonus *pushBonus(StackBonus *head, char *desc, float perc);

// elimina um Bonus
Bonus *popBonus(StackBonus *head);
//apresenta todos os bonus de uma lista
void findBonus(Bonus *bonus);

//Métodos Getters
// retorna o topo de uma pilha de bonus
Bonus *getTopBonus(StackBonus *head);

// retorna a descrição do bonus
char *getBonusDesc(Bonus *bonus);
// retorna a percentagem do bonus
float getBonusPerc(Bonus *bonus);
// retorna o proximo bonus da lista
Bonus *getNextBonus(Bonus *bonus);

//Métodos Setters
//actualiza a descrição 
void setBonusDesc(Bonus *bonus, char *desc);
//actualiza a percentagem 
void setBonusPerc(Bonus *bonus, float perc);
//actualiza o next
void setBonusNext(Bonus *oldBonus, Bonus *newBonus);
