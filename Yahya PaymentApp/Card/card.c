#include<stdio.h>
#include<string.h>
#include"card.h"

/*##############################################################################################################################
1-This function will ask for the cardholder's name and store it into card data.
2-Cardholder name is 24 alphabetic characters string max and 20 min.
3-If the cardholder name is NULL, less than 20 characters or more than 24 will return a WRONG_NAME error, else return CARD_OK.
################################################################################################################################*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint32_t i;
	for (i = 0; i < MAX_NAMESIZE; i++)
	{
		cardData->cardHolderName[i] = '\0';
	}
	gets(cardData->cardHolderName);
	if (cardData->cardHolderName[0] == '\0' || strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > MAX_NAMESIZE)
		return WRONG_NAME;
	else
		return CARD_OK;
}
/*##############################################################################################################################
1-This function will ask for the card expiry date and store it in card data.
2-Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
3-If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return the WRONG_EXP_DATE error, else return CARD_OK
################################################################################################################################*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint32_t i;
	for (i = 0; i < MAX_CARD_EXP_SIZE; i++)
		cardData->cardExpirationDate[i] = '\0';
	gets(cardData->cardExpirationDate);
	if (cardData->cardExpirationDate[0] == '\0')
		return WRONG_EXP_DATE;
	uint32_t month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	uint32_t year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	if (month < 1 || month > 12 || cardData->cardExpirationDate[2] != '/' || year < 0 || year > 99)
		return WRONG_EXP_DATE;
	else
	return CARD_OK;
}
/*##############################################################################################################################
1-This function will ask for the card's Primary Account Number and store it in card data.
2-PAN is 20 numeric characters string, 19 character max, and 16 character min.
3-If the PAN is NULL, less than 16 or more than 19 characters, will return the WRONG_PAN error, else return CARD_OK.
################################################################################################################################*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint32_t i;
	for (i = 1; i < MAX_PANSIZE; i++)
		cardData->primaryAccountNumber[i] = '\0';
	
	gets(cardData->primaryAccountNumber);
	if (cardData->primaryAccountNumber[1] == '\0' || strlen(cardData->primaryAccountNumber) > MAX_PANSIZE || strlen(cardData->primaryAccountNumber) < MIN_PANSIZE)
		return WRONG_PAN;
	return CARD_OK;

}
