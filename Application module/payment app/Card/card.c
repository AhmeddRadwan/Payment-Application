#pragma warning(disable : 4996)
#include "card.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

    printf("Please, Enter the Card name\n");
    gets((char*)cardData->cardHolderName);
    fflush(stdin);
    if (cardData->cardHolderName==NULL ||strlen((char*)cardData->cardHolderName) < 20 || strlen((char*)cardData->cardHolderName) > 24)
        return WRONG_NAME;
    else {
        return OK;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    printf("Please, Enter the Card Expire date in format 'MM/YY'\n");

    gets((char*)cardData->cardExpirationDate);
    fflush(stdin);
    int manth = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';
    if (strlen((char*)cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate[2] != '/' || manth > 12)
        return WRONG_EXP_DATE;
    else {
        return OK;
    }
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
    int i ;
    printf("Please, Enter the Card PAN \n");
    gets((char*)cardData->primaryAccountNumber);
    
    if (cardData->primaryAccountNumber==NULL || strlen((char*)cardData->primaryAccountNumber) > 19 || strlen((char*)cardData->primaryAccountNumber) < 16) {
        return WRONG_PAN;
    }
    for (i = 0; i < strlen((char*)cardData->primaryAccountNumber) - 1; i++) {
        if (isalnum(cardData->primaryAccountNumber[i]) == 0) {
            return WRONG_PAN;
        }
    }
        return OK;
}