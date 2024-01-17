typedef struct payroll Payroll;
typedef struct queuePayroll QueuePayroll;

// Inicialização do payroll
Payroll *initPayroll();

// Criar um payroll
QueuePayroll *enqueuPayroll(QueuePayroll *queuePayroll, Payroll *head)
;


// Encontra todos payrolls
void *findAllPayroll(QueuePayroll *head);
