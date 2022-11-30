#include"terminal.h"
#include<stdio.h>
#include<string.h>
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint32_t i;
	for (i = 0; i < MAX_TRANSDATE; i++) {
		termData->transactionDate[i] = '\0';
	}
	gets(termData->transactionDate);
	uint32_t DD, MM, YY;
	DD = (termData->transactionDate[0] - '0') * 10 + (termData->transactionDate[1] - '0');
	MM = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
	YY = (termData->transactionDate[6] - '0') * 1000 + (termData->transactionDate[7] - '0') * 100 + (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');
	if (termData->transactionDate[0] == '\0' || DD < 1 || DD>31 || MM < 1 || MM > 12 || YY < 0 || strlen(termData->transactionDate) < 10)
		return WRONG_DATE;
	else
	{
		return TERMINAL_OK;
	}
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	uint32_t Exp_year, Exp_month, Transac_year, Transac_month;
	Exp_year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	Exp_month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	Transac_year = (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');
	Transac_month = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
	if (Transac_year > Exp_year)
		return EXPIRED_CARD;
	else if (Transac_year == Exp_year)
	{
		if (Transac_month > Exp_month)
			return EXPIRED_CARD;
	}
	else
		return TERMINAL_OK;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;
	else
	return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else {
		termData->maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
}