#define _CRT_SECURE_NO_WARNINGS
#ifndef CARD_H
#define CARD_H
#define MAX_CARD_EXP_SIZE 5

typedef char uint8_t;
typedef int uint32_t;
typedef enum EN_Name_size_t
{
    MAX_NAMESIZE=24,MIN_NAMESIZE=20
}EN_Name_size_t;
typedef enum EN_PAN_size_t
{
    MAX_PANSIZE = 20, MIN_PANSIZE = 16
}EN_PAN_size_t;
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif // !CARD_H
