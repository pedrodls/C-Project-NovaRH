
// definição das estruturas ano e mês - filas
typedef struct payroll Payroll;

typedef struct year Year;

typedef struct queueYear QueueYear;

typedef struct month Month;

typedef struct queueMonth QueueMonth;

// inicializa a fila do ano
QueueYear *initYear();
// inicializa a fila dos meses
QueueMonth *initMonth();
// cria um novo ano
QueueYear *enqueueYear(QueueYear *queueYear, int year);
// cria um novo meses
QueueMonth *enqueueMonth(QueueMonth *queueMonth);
// lista todos os anos existentes
void findAllYear(QueueYear *year);

// lista todos os anos existentes
void findAllYearMonth(QueueYear *year);

// recebe a fila de um ano, retorna a fila do mês do último ano
QueueMonth *getQueueMonth(QueueYear *year);
// retorna o ano corrente
Year *getCurrentYear(QueueYear *year);
// retorna o nome do mês
char *getMonthName(Month *month);
// retorna o mês corrente
Month *getCurrentMonth(QueueMonth *month);
// retorna a lista da folha de pagamento do último mês efectuado
Payroll *getLastPayroll(Month *month);

// retorna a lista da folha de pagamento do mês anterior ao último efectuado
Month *getPreviousMonth(QueueMonth *month);

// retorna folhas de pagamentos de um mês
Payroll *getMonthPayrolls(Month *month);

// retorna o código do mês
int getMonthCode(Month *month);
// retorna o ano passado
Year *getPreviousYear(QueueYear *year);
// retorna o valor do ano
int getYear(Year *year);
// retorna a fila de meses de um determinado ano
QueueMonth *getQueueMonthFromYear(Year *year);
//
void setPayrollInCurrentMonth(Payroll *payroll, Month *month);
// retorna todos os anos que já foram efectuados folha de pagamento
void getYearHistory(QueueYear *queueYear);

// retorna o 1º mês de uma fila
Month *getStartMonth(QueueMonth *month);

// Função que retorna o start year da fila do ano
Year *getQueueStartYear(QueueYear *queueYear);

// Função que retorna o próximo mês
Month *getNextMonth(Month *month);

// Função que retorna o próximo ano
Year *getNextYear(Year *year);

