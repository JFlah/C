/* 
 *
 *	stock.c
 *
 *	Jack Flaherty
 *
 */
 
#include "stock.h"

#define MAXCHAR 30
 
int main(){
	int select; 
	float amt;
	FILE *fp; 
	fp = fopen("stocks", "r");
	if (fp == NULL) { 
		fprintf(stderr, "Unable to access file\n"); 
		exit(1); 
	} 
	
	char sym[13]; 
	char close[13]; 
	char num[13];
	char open[13];
	
	dlist dList = makeDList();
	stock_t * stk = NULL; 
	while (fscanf(fp, "%s %s %s %s", sym, close, open, num) != EOF) 
	{ 
		float closing = atof(close); 
		float opening = atof(open); 
		int numShares = atoi(num);
		
		stk = makeStock(sym,  closing, opening, numShares);
		addToEnd(dList, stk);
	}
	puts("Building Data");
	
	while(1)
	{
		puts("please choose from the following choices");
		puts("1. Search/print stock with closing price > some amount");
		puts("2. Search/print stock with % change  > some amount ");
		puts("3. List all the stocks using toString");
		puts("4. Quit and leave");
		scanf("%d", &select);
		switch(select)
		{
			case 1:
				printf("Enter amount: ");
				scanf("%f", &amt);
				printf("\n");
				iterPrint(dList, amt, gtClosePrint);
				break;
			case 2:
				printf("Give an amount: ");
				scanf("%f", &amt);
				printf("\n");
				iterPrint(dList, amt, PCPrint);
				break;
			case 3:
				puts("Stocks:");
				iterPrint(dList, 0.0, printAll);
				break;
			case 4:
				puts("Goodbye.");
				return 0;
			default:
				puts("Put in a valid number");
				break;
		}
		printf("\n");
	}
}

stock_t * makeStock(char * symbol, float closingSharePrice, float openingSharePrice, int numberOfShares){
	stock_t * stock;
	stock = (stock_t *)malloc(sizeof(struct stock));
	int length = strlen(symbol);
	stock->stockSymbol = (char *) malloc(length);
	strcpy(stock->stockSymbol, symbol);
	stock->numberOfShares = numberOfShares;
	stock->closingSharePrice = closingSharePrice;
	stock->openingSharePrice = openingSharePrice;
	stock->getPercentChange = getPercentChange;
	stock->getPrice = getPrice;
	stock->getTotalDollarAmount = getTotalDollarAmount;
	stock->toString = toStringStock;
	return stock;
}

float getPrice (void * S){
	stock_t * stk = (stock_t *) S;
	return stk->closingSharePrice;
}

float getTotalDollarAmount(void * S){
	stock_t * stk = (stock_t *) S;
	float price = stk->closingSharePrice;
	float numShares = stk->numberOfShares;
	float tda = price*numShares;
	return tda;
}

float getPercentChange(void * S){
	stock_t * stk = (stock_t *) S;
	float closePrice = stk->closingSharePrice;
	float openPrice = stk->openingSharePrice;
	float pctChange = (closePrice-openPrice)/openPrice;
	return pctChange;
}

void toStringStock(void * S){
	stock stk = (stock) S;
	printf("Ticker: %s\n", stk->stockSymbol);
	printf("Close price: %f\n", stk->closingSharePrice);
	printf("Open price: %f\n", stk->openingSharePrice);
	printf("Num shares: %d\n", stk->numberOfShares);
}

void gtClosePrint(float amt, void *item){
	stock_t * stk = (stock_t *) item;
	
	if(stk->closingSharePrice > amt)
		stk->toString(stk);
}

void PCPrint(float amt, void *item){
	stock_t * stk = (stock_t *) item;
	if(stk->getPercentChange(stk) > amt)
		stk->toString(stk);
}

void iterPrint(dlist dList, float amt, void (*evalPrint)(float amt, void *item)){
	node_t *currNode = dList->head;

	while (currNode!=NULL)
	{
		evalPrint(amt, currNode->item);
		currNode = currNode->next;
	}
}

void printAll(float amt, void * item){
	stock_t * stk = (stock_t *) item;
	stk->toString(stk);
}

int menu(){

  int a;
  char carriageReturn;

  puts("welcome to fun C");

  puts("please choose from the following choices");

  puts("1. Search/print stock with closing price > some amount");

  puts("2. Search/print stock with % change  > some amount ");

  puts("3. List all the stocks using toString");

  puts("4. Quit and leave");

  scanf("%d%c", &a, &carriageReturn);

  return a;

} // You may add other nice features.
