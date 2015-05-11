/* 
 *
 *	stock.h
 *
 *	Jack Flaherty
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dlinkedlist.h"
#include <string.h>

typedef  struct stock{
	char * stockSymbol;

    float closingSharePrice;

    float openingSharePrice;

    int numberOfShares;

    float (* getPrice) (void * S);

    float (* getTotalDollarAmount)(void * S);

    float (* getPercentChange)(void * S);

    void (* toString)(void * S);

}stock_t;

typedef stock_t * stock;

stock_t * makeStock(char * symbol, float closingSharePrice, float openingSharePrice, int numberofShares);

float getPrice (void * S);

float getTotalDollarAmount(void * S);

float getPercentChange(void * S);

void toStringStock(void * S);

int menu();

void printAll(float amt, void * item);

void iterPrint(dlist dList, float amt, void (*evalPrint)(float amt, void *item));

void PCPrint(float amt, void *item);

void gtClosePrint(float amt, void *item);
