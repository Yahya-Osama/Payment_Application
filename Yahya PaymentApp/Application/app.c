#include"../Server/server.h"
#include"app.h"
#include <stdio.h>
#include <string.h>
ST_accountsDB_t accountsdb;
ST_cardData_t CardData_Test,CARDDATA;
ST_terminalData_t TerminalData_Test, TERMINALDATA;
ST_transaction_t Transactiondb;
EN_terminalError_t TerminalR;
EN_cardError_t CardR;
EN_transState_t State;
uint8_t TransactionSeq = 1;
int main(void)
{
	
	while (1) {
		appStart();
		//getCardHolderNameTest();
		//getCardExpiryDateTest();
		//getCardPANTest();
		//getTransactionDateTest();
		//isCardExpriedTest();
		//getTransactionAmountTest();
		//setMaxAmountTest();
		//isBelowMaxAmountTest();
		//listSavedTransactions();
	}
}


void appStart(void)
{
	
	/**************************************************Card Holder name*****************************************************************/
	printf("\nPlease enter card holder name: -[20-24] characters: ");
	fseek(stdin, 0, SEEK_END);
	CardR = getCardHolderName(&CARDDATA);
	
	if (CardR == WRONG_NAME) {
		printf("\nInvalid input\n");
		return;
	}
	else if (CardR == CARD_OK)
		printf("\nName saved successfuly\n");
	/**************************************************Card Expiry date****************************************************************/
	printf("\nEnter card expiry date in format MM/YY eg.05/25: ");
	CardR = getCardExpiryDate(&CARDDATA);
	if (CardR == WRONG_EXP_DATE) {
		printf("\nWrong Format!\n");
		return;
	}
	else if (CardR == CARD_OK)
		printf("\nExpiry date saved successfuly\n");
	/**************************************************PAN Number**********************************************************************/
	printf("\nPlease enter primary account number -[16-19] characters: ");
	CardR = getCardPAN(&CARDDATA);
	if ( CardR== WRONG_PAN) {
		printf("\nWrong PAN number!\n");
		return;
	}
	else if (CardR == CARD_OK)
		printf("\nPAN saved successfuly\n");
	/*************************************************Transaction date*****************************************************************/
	printf("\nPlease enter transaction date in format DD/MM/YY eg.25/06/2022: ");
	TerminalR = getTransactionDate(&TERMINALDATA);
	if (TerminalR == WRONG_DATE) {
		printf("\nWrong date!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK)
		printf("\nTransaction date saved successfully\n");
	/***********************************************Is Card Expired?*******************************************************************/
	TerminalR = isCardExpired(&CARDDATA, &TERMINALDATA);
	if (TerminalR == EXPIRED_CARD) {
		printf("\nExpired Card!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK)
		printf("\nCard is valid\n");
	/*********************************************Transaction amount****************************************************************/
	printf("\nEnter transaction amount: ");
	TerminalR = getTransactionAmount(&TERMINALDATA);
	if (TerminalR == INVALID_AMOUNT) {
		printf("\nInvalid amount!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK)
		printf("\nTransaction amount = %f\n", TERMINALDATA.transAmount);
	/***********************************************Set max amount*********************************************************************/
	printf("\nEnter the value of the maximum amount withdrwal allowed: ");
	float max;
	scanf_s("%f", &max);
	TerminalR = setMaxAmount(&TERMINALDATA, max);
	if (TerminalR == INVALID_MAX_AMOUNT) {
		printf("\nInvalid amount!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK) {
		printf("\nMax amount = %f \n", TERMINALDATA.maxTransAmount);
		Transactiondb.terminalData.maxTransAmount = max;
	}
	
	/**********************************************Is Bellow Max amount**************************************************************/
	TerminalR = isBelowMaxAmount(&TERMINALDATA);
	if (TerminalR == EXCEED_MAX_AMOUNT) {
		printf("\nExceeded max amount!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK)
		printf("\nValid amount\n");
	/*******************************************************************************************************************************/
	Transactiondb.cardHolderData = CARDDATA;
	Transactiondb.terminalData = TERMINALDATA;
	saveTransaction(&Transactiondb);
	listSavedTransactions();
}

void getCardHolderNameTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name : getCardHolderName\n");
	printf("\nPlease enter card holder name: -[20-24] characters:\n");
	TerminalR = getCardHolderName(&CardData_Test);
	printf("\nTest Case 1:Input less than 20 characters\n");
	printf("\nInput Data:Yahya Osama\n");
	printf("\nExpected Result:Wrong Format!\n");
	if (TerminalR == WRONG_NAME)
		printf("\nActual Result:Wrong Format!\n");
	else if (TerminalR == CARD_OK)
		printf("\nActual Result:Name saved successfuly\n");

	printf("\nPlease enter card holder name: -[20-24] characters:\n");
	TerminalR = getCardHolderName(&CardData_Test);
	printf("\nTest Case 2:Input more than 24 characters\n");
	printf("\nInput Data:Yahya Osama Mohamed Rashad\n");
	printf("\nExpected Result:Wrong Format!\n");
	if (TerminalR == WRONG_NAME)
		printf("\nActual Result:Wrong Format!\n");
	else if (TerminalR == CARD_OK)
		printf("\nActual Result:Name saved successfuly\n");

	printf("\nPlease enter card holder name: -[20-24] characters:\n");
	TerminalR = getCardHolderName(&CardData_Test);
	printf("\nTest Case 3:Input  23 characters\n");
	printf("\nInput Data:Yahya Osama Mohamed aly\n");
	printf("\nExpected Result:Name saved successfuly\n");
	if (TerminalR == WRONG_NAME)
		printf("\nActual Result:Wrong Format!\n");
	else if (TerminalR == CARD_OK)
		printf("\nActual Result:Name saved successfuly\n");
}

void getCardExpiryDateTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name : getCardExpiryDate\n");
	printf("\nEnter card expiry date in format MM/YY eg.05/25: ");
	CardR = getCardExpiryDate(&CardData_Test);
	printf("\nTest Case 1:Input valid card expiry date\n");
	printf("\nInput Data:11/22\n");
	printf("\nExpected Result:Date saved successfuly \n");
	if (CardR == WRONG_EXP_DATE)
		printf("\nActual Result:Wrong Format!\n");
	else if (CardR == CARD_OK)
		printf("\nActual Result:Date saved successfuly\n");
	printf("\nEnter card expiry date in format MM/YY eg.05/25: ");
	CardR = getCardExpiryDate(&CardData_Test);
	printf("\nTest Case 2:Exceed 12 month in card expiry date\n");
	printf("\nInput Data:13/22\n");
	printf("\nExpected Result:Wrong Format! \n");
	if (CardR == WRONG_EXP_DATE)
		printf("\nActual Result:Wrong Format!\n");
	else if (CardR == CARD_OK)
		printf("\nActual Result:Date saved successfuly\n");
	printf("\nEnter card expiry date in format MM/YY eg.05/25: ");
	CardR = getCardExpiryDate(&CardData_Test);
	printf("\nTest Case 3:Entering NULL character\n");
	printf("\nInput Data: \n");
	printf("\nExpected Result:Wrong Format! \n");
	if (CardR == WRONG_EXP_DATE)
		printf("\nActual Result:Wrong Format!\n");
	else if (CardR == CARD_OK)
		printf("\nActual Result:Date saved successfuly\n");

}

void getCardPANTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name : getCardPANTest\n");
	printf("Enter card primary account number - note: [16 - 19] characters - :");
	CardR = getCardPAN(&CardData_Test);
	printf("\nTest Case 1:Input less than 16 characters\n");
	printf("\nInput Data:4096155244\n");
	printf("\nExpected Result:Wrong PAN number!\n");
	if (CardR == WRONG_PAN)
		printf("\nActual Result:Wrong PAN number!\n");
	else if (CardR == CARD_OK)
		printf("\nActual Result:PAN saved successfuly\n");
	printf("Enter card primary account number - note: [16 - 19] characters - :");
	CardR = getCardPAN(&CardData_Test);
	printf("\nTest Case 2:Input more than 19 characters\n");
	printf("\nInput Data:1254789214096155244551\n");
	printf("\nExpected Result:Wrong PAN number!\n");
	if (CardR == WRONG_PAN)
		printf("\nActual Result:Wrong PAN number!\n");
	else if (CardR == CARD_OK)
		printf("\nActual Result:PAN saved successfuly\n");
	printf("Enter card primary account number - note: [16 - 19] characters - :");
	CardR = getCardPAN(&CardData_Test);
	printf("\nTest Case 3:Input  17 characters\n");
	printf("\nInput Data:50175015326865476\n");
	printf("\nExpected Result:PAN saved successfuly\n");
	if (CardR == WRONG_PAN)
		printf("\nActual Result:Wrong PAN number!\n");
	else if (CardR == CARD_OK)
		printf("\nActual Result:PAN saved successfuly\n");

}

void getTransactionDateTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name: getTransactionDate\n");
	printf("\nTest Case 1:Enter Valid transaction date\n");
	printf("\nPlease enter transaction date in format DD/MM/YY eg.25/06/2022:\n");
	TerminalR = getTransactionDate(&TerminalData_Test);
	//TEST CASE #1
	printf("\nInput Data:25/06/2022\n");
	printf("\nExpected Result:Transaction date saved successfully\n");
	if (TerminalR == WRONG_DATE)
		printf("\nActual Result:Wrong date!\n");
	else if (TerminalR == TERMINAL_OK)
		printf("\nActual Result:Transaction date saved successfully\n");
	//TEST CASE #2
	printf("\nTest Case 2:Enter Wrong format transaction date\n");
	printf("\nPlease enter transaction date in format DD/MM/YY eg.25/06/2022:\n");
	TerminalR = getTransactionDate(&TerminalData_Test);
	printf("\nInput Data:40/06/2022\n");
	printf("\nExpected Result:Wrong date!\n");
	if (TerminalR == WRONG_DATE)
		printf("\nActual Result:Wrong date!\n");
	else if (TerminalR == TERMINAL_OK)
		printf("\nActual Result:Transaction date saved successfully\n");
	//TEST CASE #3
	printf("\nTest Case 3:Enter null\n");
	printf("\nPlease enter transaction date in format DD/MM/YY eg.25/06/2022:\n");
	TerminalR = getTransactionDate(&TerminalData_Test);
	printf("\nInput Data: \n");
	printf("\nExpected Result:Wrong date!\n");
	if (TerminalR == WRONG_DATE)
		printf("\nActual Result:Wrong date!\n");
	else if (TerminalR == TERMINAL_OK)
		printf("\nActual Result:Transaction date saved successfully\n");
}

void isCardExpriedTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name: isCardExpried\n");
	//TEST CASE #1
	printf("\nTest Case 1:Enter unexpired card\n");
	printf("\nEnter card expiry date in format MM/YY eg.05/25: ");
	getCardExpiryDate(&CardData_Test);
	printf("\nPlease enter transaction date in format DD/MM/YY eg.25/06/2022:\n");
	TerminalR = getTransactionDate(&TerminalData_Test);
	if (isCardExpired(&CardData_Test, &TerminalData_Test) == EXPIRED_CARD) {
		printf("\nExpired Card!\n");
		return;
	}
	else if (isCardExpired(&CardData_Test, &TerminalData_Test) == TERMINAL_OK)
		printf("\nCard is valid\n");
	//TEST CASE #2
	printf("\nTest Case 1:Enter expired card\n");
	printf("\nEnter card expiry date in format MM/YY eg.05/25: ");
	getCardExpiryDate(&CardData_Test);
	printf("\nPlease enter transaction date in format DD/MM/YY eg.25/06/2022:\n");
	TerminalR = getTransactionDate(&TerminalData_Test);
	if (TerminalR == EXPIRED_CARD) {
		printf("\nExpired Card!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK)
		printf("\nCard is valid\n");

}

void getTransactionAmountTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name: getTransactionAmountTest\n");
	//TEST CASE #1
	printf("\nTest Case 1:Enter Valid transaction amount\n");
	printf("\nEnter transaction amount: ");
	TerminalR = getTransactionAmount(&TerminalData_Test);
	if (TerminalR == INVALID_AMOUNT)
		printf("Invalid amount!");
	else if (TerminalR == TERMINAL_OK)
		printf("Transaction recieved");
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name: getTransactionAmountTest\n");
	//TEST CASE #2
	printf("\nTest Case 2:Enter invalid transaction amount\n");
	printf("\nEnter transaction amount: ");
	TerminalR = getTransactionAmount(&TerminalData_Test);
	if (TerminalR == INVALID_AMOUNT)
		printf("Invalid amount!");
	else if (TerminalR == TERMINAL_OK)
		printf("Transaction recieved");
}

void setMaxAmountTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name: setMaxAmountTest\n");
	//TEST CASE #1
	printf("\nTest Case 1:Enter Valid max transaction amount\n");
	printf("\nEnter the value of the maximum amount withdrwal allowed: \n");
	printf("\nExpected Result: Transaction recieved\n");
	printf("\nInput Data: ");
	float max;
	scanf_s("%f", &max);
	TerminalR = setMaxAmount(&TerminalData_Test, max);
	
	printf("\nActual Result: ");
	if (TerminalR == INVALID_MAX_AMOUNT) {
		printf("Invalid amount!\n");
	}
	else if (TerminalR == TERMINAL_OK)
		printf("Transaction recieved\n");
	//TEST CASE #2
	printf("\nTest Case 1:Enter invalid max transaction amount\n");
	printf("\nEnter the value of the maximum amount withdrwal allowed: \n");
	printf("\nExpected Result: Invalid amount!\n");
	printf("\nInput Data: ");
	scanf_s("%f", &max);
	TerminalR = setMaxAmount(&TerminalData_Test, max);

	printf("\nActual Result: ");
	if (TerminalR == INVALID_MAX_AMOUNT) {
		printf("Invalid amount!\n");
	}
	else if (TerminalR == TERMINAL_OK)
		printf("Transaction recieved\n");

}

void isBelowMaxAmountTest(void)
{
	printf("Tester Name : Yahya Osama Mohamed Rashad\n");
	printf("\nFunction Name: isBellowMaxAmountTest\n");
	//TEST CASE #1
	printf("\nTest Case 1:Enter Valid transaction amount\n");
	printf("\nEnter Transaction amount\n");
	printf("\nExpected Result: Valid amount\n");
	printf("\nInput Data: ");
	setMaxAmount(&TerminalData_Test, 20000.0);
	getTransactionAmount(&TerminalData_Test);
	TerminalR = isBelowMaxAmount(&TerminalData_Test);
	printf("\nActual Result: ");
	if (TerminalR == EXCEED_MAX_AMOUNT) {
		printf("Exceeded max amount!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK) {
		printf("Valid amount\n");
	}
	//TEST CASE #2
	printf("\nTest Case 2:Enter value more than max amount\n");
	printf("\nEnter Transaction amount\n");
	printf("\nExpected Result: Exceeded max amount!\n");
	printf("\nInput Data: ");
	setMaxAmount(&TerminalData_Test, 20000.0);
	getTransactionAmount(&TerminalData_Test);
	TerminalR = isBelowMaxAmount(&TerminalData_Test);
	printf("\nActual Result: ");
	if (TerminalR == EXCEED_MAX_AMOUNT) {
		printf("Exceeded max amount!\n");
		return;
	}
	else if (TerminalR == TERMINAL_OK) {
		printf("Valid amount\n");
	}


}

void listSavedTransactions(void)
{
	printf("\n#########################\n");
	printf("\nTransaction Sequence Number: %d\n", TransactionSeq++);
	printf("\nTransaction Date: %s\n", Transactiondb.terminalData.transactionDate);
	printf("\nTransaction Amount: %f\n", Transactiondb.terminalData.transAmount);
	printf("\nTransaction State: ");
	State = recieveTransactionData(&Transactiondb);
	if (State == FRAUD_CARD)
		printf("Fraud Card!\n");
	else if (State == DECLINED_INSUFFECIENT_FUND)
		printf("Insuffecient fund!\n");
	else if (State == DECLINED_STOLEN_CARD)
		printf("Stolen card!\n");
	else if (State == APPROVED)
		printf("Approved\n");
	printf("\nTerminal Max Amount: %f\n", TERMINALDATA.maxTransAmount);
	printf("\nCardholder Name: %s\n", Transactiondb.cardHolderData.cardHolderName);
	printf("\nPAN: %s\n", Transactiondb.cardHolderData.primaryAccountNumber);
	printf("\nCard Expiration Date : %s\n", Transactiondb.cardHolderData.cardExpirationDate);
	printf("\n#########################\n");
}