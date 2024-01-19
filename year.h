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

// recebe a fila de um ano
QueueMonth *getQueueMonth(QueueYear *year);

Year *getCurrentYear(QueueYear *year);

char *getMonthName(Month *month);

Month *getCurrentMonth(QueueMonth *month);

Payroll *getLastPayroll(Month *month);

Month *getPreviousMonth(QueueMonth *month);

int getMonthCode(Month *month);

Year *getPreviousYear(QueueYear *year);

int getYear(Year *year);

QueueMonth *getQueueMonthFromYear(Year *year);

void setPayrollInCurrentMonth(Payroll *payroll, Month *month);
