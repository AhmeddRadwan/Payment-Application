// to skip warning 
#pragma warning(disable : 4996)

//lib used
#include"app.h"
#include<stdio.h>
#include<string.h>

// appstart function it's a root of a project 
void appStart(void) {
	int num = 0, state;
	EN_cardError_t length_name;
	init_accountDB();
	ST_cardData_t name;
	ST_terminalData_t atm;
	char ch = 'y';
	do {
		length_name = getCardHolderName(&name);
		getCardPAN(&name);
		getCardExpiryDate(&name);
		getTransactionDate(&atm);
		if (isCardExpired(name, atm)) {
			printf("Decline Expired card\n");
			return;
		}
		getTransactionAmount(&atm);
		if (isBelowMaxAmount(&atm)) {
			printf("Decline amount excedding limit\n");
			return;
		}

		transaction_DB(name, atm, num);
		state = recieveTransactionData(&tran[num]);
		if (state == 2 || length_name == WRONG_NAME) {
			printf("Declined Invalid account\n");
			return;
		}
		else if (state == 1) {
			printf("Declined insuffecient funds\n");
			return;
		}
		system("cls");
		printf("---------------- The recive ----------------\n");
		printf("%s\n", tran[num].cardHolderData.cardHolderName);
		printf("%s\n", tran[num].cardHolderData.primaryAccountNumber);
		printf("The new balance = %2f\n\n", accounts[i].balance);
		printf("--------------------------------------------\n");
		printf("do you want to do another transaction (y,n): ");
		scanf(" %c%*c", &ch);
		system("cls");
		num++;
	} while (ch == 'y');
}

// function to fill global array of accounts
void init_accountDB() {
	accounts[0].balance = 8000;
	strcpy((char*)accounts[0].primaryAccountNumber, "4117394577826109");
	accounts[1].balance = 10000;
	strcpy((char*)accounts[1].primaryAccountNumber, "4117394577826901");
}

// function to assign data to transaction
void transaction_DB(ST_cardData_t cardData, ST_terminalData_t termData, uint32_t sequence) {
	tran[sequence].cardHolderData = cardData;
	tran[sequence].terminalData = termData;
}