#pragma warning(default:4716)
#include"server.h"
#include<stdio.h>
#include<string.h>
uint8_t AccountIndexRef, TransacIndexRef = 0;
uint32_t TransacSeq = 0;
EN_transState_t TransStat;
ST_accountsDB_t server_account;
ST_accountsDB_t AccountsDB[255] = { {1000.0,RUNNING,"02235476118212872"},
									 {5000.0,RUNNING,"34467109133023154"},
									 {6000.0,BLOCKED,"11534548137026894"},
									 {2000.0,RUNNING,"85545859273812414"},
									 {1200.0,BLOCKED,"57200553809824010"},
									 {1500.0,BLOCKED,"35692514603872481"},
									 {2500.0,RUNNING,"64265520218585381"},
									 {3000.0,RUNNING,"74230952741243678"},
									 {3500.0,RUNNING,"93597242818196414"},
									 {500.0,BLOCKED,"63395079770211303"},
									 {1250.0,RUNNING,"46034525722172102"},
};
ST_transaction_t TransactionDB[255] = { 0 };
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint32_t i;
	EN_bool_t flag=FALSE;
	for (i = 0; i < 255; i++)
	{
		if (strcmp(cardData->primaryAccountNumber, AccountsDB[i].primaryAccountNumber) == 0)
		{
			accountRefrence->balance = AccountsDB[i].balance;
			accountRefrence->state = AccountsDB[i].state;
			AccountIndexRef = i;
			flag = TRUE;
			break;
		}
	}
	if (flag == TRUE)
		return SERVER_OK;
	else
		return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > server_account.balance)
		return LOW_BALANCE;
	else
		return SERVER_OK;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == RUNNING)
		return SERVER_OK;
	else
		return BLOCKED_ACCOUNT;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	TransacIndexRef++;
	TransacSeq++;
	TransactionDB[TransacIndexRef].cardHolderData = transData->cardHolderData;
	TransactionDB[TransacIndexRef].terminalData = transData->terminalData;
	TransactionDB[TransacIndexRef].transactionSequenceNumber = TransacIndexRef;
	TransactionDB[TransacIndexRef].transState = TransStat;
	
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t ValidAcc = isValidAccount(&transData->cardHolderData, &server_account);
	if (ValidAcc == ACCOUNT_NOT_FOUND)
		TransStat = FRAUD_CARD;
	else
	{
		EN_serverError_t AmountAvailble = isAmountAvailable(&transData->terminalData);
		if (AmountAvailble == LOW_BALANCE)
			TransStat = DECLINED_INSUFFECIENT_FUND;
		else
		{
			EN_serverError_t BlockedAcc = isBlockedAccount(&server_account);
			if (BlockedAcc == BLOCKED_ACCOUNT)
				TransStat = DECLINED_STOLEN_CARD;
			else
			{
				AccountsDB[AccountIndexRef].balance = AccountsDB[AccountIndexRef].balance - transData->terminalData.transAmount;
				TransStat = APPROVED;
			}
		}
	}
	return TransStat;
}

