#ifndef SERVER_H
#define SERVER_H

// ***** typedefs ****
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
// ***** macros ****
#define MAX_AVILABLE 255
// ***** header files ****
#include "../Card/card.h"
#include "../Terminal/terminal.h"
// ***** enums and struct ****
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef enum EN_serverError_t
{
	oK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

// ***** function ****
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_transState_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);

// ***** global variable ****

// accounts data base
 ST_accountsDB_t accounts[MAX_AVILABLE];
 // transaction data base
 ST_transaction_t tran[MAX_AVILABLE];

 int i, seq;


#endif