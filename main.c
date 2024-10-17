#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct rack {
    	int count;
	int capacity;
    	char ** arrayItems;
}rack_t;

typedef struct shop {
	int count;
	int capacity;
	rack_t * arrayRacks;
}shop_t;

typedef struct item {
	int qsortIndex;
	int rackNumber;
	int rackPosition;
    	char * name;
}item_t;

typedef struct list {
	int count;
	int capacity;
	item_t * item;
} list_t;

typedef struct listOfLists {
    	int count;
	int capacity;
	list_t * arrayLists;
} lol_t;

void allocNewItem(shop_t * shop)
{
	shop -> arrayRacks[shop -> count].capacity = shop -> arrayRacks[shop -> count].capacity * 2 + 1;
	shop -> arrayRacks[shop -> count].arrayItems = (char **)realloc(shop -> arrayRacks[shop -> count].arrayItems,shop -> arrayRacks[shop -> count].capacity * sizeof(char *));
	for (int i = shop -> arrayRacks[shop -> count].count; i < shop -> arrayRacks[shop -> count].capacity; i++) {        //set newly allocated pointers to items to NULL
		shop -> arrayRacks[shop -> count].arrayItems[i] = NULL;
	}
}

void inicializeNewlyAllocatedRacks(shop_t * shop)
{
	for (int i = shop -> count; i < shop -> capacity; i++) {                //set newly allocated pointers to items to NULL
		shop -> arrayRacks[i].capacity = 0;
		shop -> arrayRacks[i].count = 0;
		shop -> arrayRacks[i].arrayItems = NULL;
	}
}

void allocNewRack(shop_t * shop, long unsigned int * size)
{
	shop -> capacity = shop -> capacity * 2 + 1;
	shop -> arrayRacks = (rack_t *) realloc(shop -> arrayRacks, shop -> capacity * sizeof(rack_t));
	inicializeNewlyAllocatedRacks(shop);
}
int isNewLine(shop_t * shop)
{
	if (shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count - 1][0] == '\n')
		return 1;
	return 0;
}

int isHash(shop_t * shop)
{
	if (strchr(shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count - 1], '#') != NULL)
		return 1;
	return 0;
}

void allocateFirstItem(shop_t * shop)
{
	shop -> arrayRacks[shop -> count].capacity = 1;
	shop -> arrayRacks[shop -> count].arrayItems = (char **)realloc(shop -> arrayRacks[shop -> count].arrayItems, shop -> arrayRacks[shop -> count].capacity * sizeof(char *));
	shop -> arrayRacks[shop -> count].count = 0;
}

int firstRead(shop_t * shop, int fR)
{
	if (shop -> count == 0 && shop -> arrayRacks[0].count == 1 && fR)
		return 1;
	return 0;
}

void deleteHash(shop_t * shop)
{
	strcpy(shop -> arrayRacks[0].arrayItems[0], "");		//keep in mind
	shop -> arrayRacks[shop -> count].count = 0;
}

int checkHashInt0(shop_t * shop)
{
	if (strcmp(shop -> arrayRacks[0].arrayItems[0], "#0") != 0)
		return 0;
	return 1;
}

int checkHashInt(shop_t * shop)
{
	char tmp[3];
	sprintf(tmp, "#%d", shop -> count);
	if (strcmp(shop -> arrayRacks[shop -> count - 1].arrayItems[shop -> arrayRacks[shop -> count - 1].count - 1], tmp) != 0)
		return 0;
	return 1;
}



int scanShop(shop_t * shop)
{
	int a;
	int fR = 1;			//first read
	long unsigned int size = 10;
	shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count] = (char*)malloc (size * sizeof(char));
	while ((a = getline(&(shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count]), &size, stdin ) ) != -1) {
		shop -> arrayRacks[shop -> count].count += 1;
		if (shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count - 1][a - 1] == '\n' && a != 1) {
			shop->arrayRacks[shop->count].arrayItems[shop->arrayRacks[shop->count].count - 1][a - 1] = '\0';
		}
		if (firstRead(shop, fR) == 1) {			//actual first read
			fR = 0;
			if (!isHash(shop))
				return 0;

			if (checkHashInt0(shop) == 0)
				return 0;
			deleteHash(shop);
			size = 10;
			shop->arrayRacks[shop->count].arrayItems[shop->arrayRacks[shop->count].count] = (char *) realloc(shop->arrayRacks[shop->count].arrayItems[shop->arrayRacks[shop->count].count], size * sizeof(char));
			continue;
		}

		if (isNewLine(shop)) {
			break;
		}

		if (isHash(shop)) {
			shop -> count += 1;
			if (checkHashInt(shop) == 0)
				return 0;
			if (shop -> count == shop -> capacity) {
				allocNewRack(shop, &size);
			}
			allocateFirstItem(shop);
		}
		if (shop -> arrayRacks[shop -> count].count == shop -> arrayRacks[shop -> count].capacity ) {
			allocNewItem(shop);
		}

		size = 10;
		shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count] = (char*)malloc (size * sizeof(char));	//alloc new item for getline

		//printf("\n posl r. shop count %d, shop -> arrayRacks[shop -> count].count %d \n\n",shop -> count, shop -> arrayRacks[shop -> count].count);
		//shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count] = NULL;
		//printf("predpredposledni \n\n");
		//printf("\n posl r. shop count %d, shop -> arrayRacks[shop -> count].count %d \n\n",shop -> count, shop -> arrayRacks[shop -> count].count);
		//shop -> arrayRacks[shop -> count].arrayItems[shop -> arrayRacks[shop -> count].count] = NULL;
	}

	if (a == -1)
		return 0;

	//printf("\n\n\na: %d \n\n\n", a);
	//printf("a: %d shop -> count: %d shop -> arrayRacks[shop -> count] %d", a, shop -> count, shop -> arrayRacks[shop -> count].count);
	/*shop -> arrayRacks = (rack_t *) realloc (shop -> arrayRacks, shop -> capacity * sizeof(rack_t)); 	//jednotlive regaly
	shop -> arrayRacks[0].capacity = 10;
	shop -> arrayRacks[0].arrayItems = (char **)malloc(shop -> arrayRacks[0].capacity * sizeof(char *));
	shop -> arrayRacks[0].arrayItems[0] = (char*)malloc (size * sizeof(char));					//v jednom regalu jeden konkretni item
	getline(&(shop -> arrayRacks[0].arrayItems[0]), &size, stdin );*/					//zapisu nazev jednoho itemu

	return 1;
}

void firstAlloc(shop_t * shop)
{
	shop -> arrayRacks = (rack_t *) realloc (shop -> arrayRacks, shop -> capacity * sizeof(rack_t));
	shop -> arrayRacks[0].capacity = 1;
	shop -> arrayRacks[0].count = 0;
	shop -> arrayRacks[0].arrayItems = (char **)malloc(shop -> arrayRacks[0].capacity * sizeof(char *));
}

void printShop(shop_t * shop)
{
	for (int i = 0; i <= shop -> count; i++) {
		printf("Regál %d:\n", i);
		for (int j = 0; j < shop -> arrayRacks[i].count - 1; j++) {
			printf("%s", shop -> arrayRacks[i].arrayItems[j]);
		}
	}
}

void freeShop(shop_t * shop)
{

	for (int i = 0; i < shop -> capacity; i++) {
		for (int j = 0; j < shop -> arrayRacks[i].capacity; j++) {
			free(shop -> arrayRacks[i].arrayItems[j]);
		}
		free(shop -> arrayRacks[i].arrayItems);
	}
	free(shop -> arrayRacks);
}

void allocNewItemL(lol_t * lists)
{
	lists -> arrayLists[lists -> count].capacity = lists -> arrayLists[lists -> count].capacity * 2 + 1;
	lists -> arrayLists[lists -> count].item  = (item_t *)realloc(lists -> arrayLists[lists -> count].item,lists -> arrayLists[lists -> count].capacity * sizeof(item_t));
	for (int i = lists -> arrayLists[lists -> count].count; i < lists -> arrayLists[lists -> count].capacity; i++) {        //set newly allocated pointers to items to NULL
		lists -> arrayLists[lists -> count].item[i].name = NULL;
	}
}

void firstAllocL(lol_t * lists)
{
	lists -> arrayLists = (list_t *) realloc (lists -> arrayLists, lists -> capacity * sizeof(list_t));
	lists -> arrayLists[0].capacity = 1;
	lists -> arrayLists[0].count = 0;
	lists -> arrayLists[0].item = (item_t *)malloc(lists -> arrayLists[0].capacity * sizeof(item_t));
}

int isNewLineL(lol_t * lists)
{
	if (lists -> arrayLists[lists -> count].item[lists -> arrayLists[lists -> count].count - 1].name[0] == '\n')
		return 1;
	return 0;
}

void inicializeNewlyAllocatedLists(lol_t * lists)
{
	for (int i = lists -> count; i < lists -> capacity; i++) {                //set newly allocated pointers to lists to NULL
		lists -> arrayLists[i].capacity = 0;
		lists -> arrayLists[i].count = 0;
		lists -> arrayLists[i].item = NULL;
	}
}

void allocNewList(lol_t * lists, long unsigned int * size)
{
	lists -> capacity = lists -> capacity * 2 + 1;
	lists -> arrayLists = (list_t *) realloc(lists -> arrayLists, lists -> capacity * sizeof(list_t));
	inicializeNewlyAllocatedLists(lists);
}

void allocateFirstList(lol_t * lists)
{
	lists -> arrayLists[lists -> count].capacity = 1;
	lists -> arrayLists[lists -> count].item  = (item_t *)realloc(lists -> arrayLists[lists -> count].item, lists -> arrayLists[lists -> count].capacity * sizeof(item_t));
	lists -> arrayLists[lists -> count].count = 0;
}

void deleteNewLine(lol_t * lists)
{
	//printf("AAAAAAAAAAAAA\n\n\n");


	strcpy(lists -> arrayLists[lists -> count - 1].item[lists -> arrayLists[lists -> count - 1].count - 1].name, "");
	lists -> arrayLists[lists -> count - 1].count += -1;
}

int scanLists(lol_t * lists)
{
	int a;
	long unsigned int size = 10;
	lists -> arrayLists[lists -> count].item[lists -> arrayLists[lists -> count].count].name = (char*)malloc (size * sizeof(char));
	while ((a = getline(&(lists -> arrayLists[lists -> count].item[lists -> arrayLists[lists -> count].count].name), &size, stdin ) ) != -1){
		lists -> arrayLists[lists -> count].item[lists -> arrayLists[lists -> count].count].qsortIndex = lists -> arrayLists[lists -> count].count;
		lists -> arrayLists[lists -> count].count += 1;
		if (lists -> arrayLists[lists -> count].item[lists -> arrayLists[lists -> count].count - 1].name[a-1] == '\n' && a != 1)
			lists -> arrayLists[lists -> count].item[lists -> arrayLists[lists -> count].count - 1].name[a-1] = '\0';
		if (lists -> arrayLists[lists -> count].count == lists -> arrayLists[lists -> count].capacity ) {
			allocNewItemL(lists);
		}

		if (isNewLineL(lists)) {
			lists -> count += 1;
			//printf("AAAAAAAAAAAAA\n\n\n");

			deleteNewLine(lists);

			if (lists -> count == lists -> capacity) {
				allocNewList(lists, &size);
			}
			allocateFirstList(lists);
		}
		size = 10;
		lists -> arrayLists[lists -> count].item[lists -> arrayLists[lists -> count].count].name = (char*)malloc (size * sizeof(char));	//alloc new item for getline
	}

	return 1;
}

void freeLists(lol_t * lists)
{
	for (int i = 0; i < lists -> capacity; i++) {
		for (int j = 0; j < lists -> arrayLists[i].capacity; j++) {
			free(lists -> arrayLists[i].item[j].name);
		}
		free(lists -> arrayLists[i].item);
	}
	free(lists -> arrayLists);
}

void printLists(lol_t * lists)
{
	for (int i = 0; i <= lists -> count; i++) {
		printf("List %d:\n", i);
		for (int j = 0; j < lists -> arrayLists[i].count; j++) {
			printf("rack number: %d rack position: %d qsort number: %d %s\n", lists -> arrayLists[i].item[j].rackNumber, lists -> arrayLists[i].item[j].rackPosition, lists -> arrayLists[i].item[j].qsortIndex, lists -> arrayLists[i].item[j].name);
		}
	}
}

int lookForItem(int a, int b, lol_t * lists, shop_t * shop)
{
	if (strcmp(lists -> arrayLists[a].item[b].name, "\n") == 0)				//condition for new lines from separating lists
		return -1;

	for (int i = 0; i <= shop -> count; i++) {
		for (int j = 0; j < shop -> arrayRacks[i].count - 1; j++) {
			//printf("\nporovnani se item\n%s%s", lists -> arrayLists[a].item[b].name, shop -> arrayRacks[i].arrayItems[j] );
			if (strcasecmp(lists -> arrayLists[a].item[b].name, shop -> arrayRacks[i].arrayItems[j]) == 0) {
				lists->arrayLists[a].item[b].rackNumber = i;
				lists->arrayLists[a].item[b].rackPosition = j;
				return 1;
			}
		}
	}
	return 0;

}

void convertToLower(char * string)
{
	//printf("convert to lower\n");
	int j = 0;
	while(string[j]){					//valgrind warning, I think it is false
		string[j] = tolower(string[j]);
		j++;
	}
}

int lookForItemBigger(int a, int b, lol_t * lists, shop_t * shop)
{
	//printf("tmp2: %s sizeof: %lu realloc +1 \n", lists -> arrayLists[a].item[b].name, sizeof(lists -> arrayLists[a].item[b].name));
	char * tmp2 = strdup( lists -> arrayLists[a].item[b].name );
	convertToLower(tmp2);
	for (int i = 0; i <= shop -> count; i++) {
		for (int j = 0; j < shop -> arrayRacks[i].count - 1; j++) {
			//printf("tmp1 lfib \n");
			//printf("\nporovnani nenitmp '%s'\n'%s'\n\n", lists -> arrayLists[a].item[b].name,shop -> arrayRacks[i].arrayItems[j] );
			//printf("kopiruje se string delky %d %s do stringu delky %d\n", (int)strlen(shop -> arrayRacks[i].arrayItems[j]), shop -> arrayRacks[i].arrayItems[j], (int)strlen(shop -> arrayRacks[i].arrayItems[j]) );
			//printf("tmp1: %s strlen: %lu realloc +1 \n", shop -> arrayRacks[i].arrayItems[j], strlen(shop -> arrayRacks[i].arrayItems[j]));
			char * tmp1 = strdup ( shop -> arrayRacks[i].arrayItems[j] );
			convertToLower(tmp1);

			//printf("\nporovnani se itembigger '%s'\n'%s'", tmp2, tmp1 );
			if (strstr( tmp1, tmp2) != NULL) {
				//printf("\nKONEC---------------------\n");
				lists->arrayLists[a].item[b].rackNumber = i;
				lists->arrayLists[a].item[b].rackPosition = j;
				free (tmp1);
				free(tmp2);
				return 1;
			}
			free (tmp1);
		}
	}
	free(tmp2);
	lists->arrayLists[a].item[b].rackNumber = -1;
	return 0;
}

void getRackNumbers(shop_t * shop, lol_t * lists)
{
	for (int i = 0; i <= lists -> count; i++) {
		for (int j = 0; j < lists -> arrayLists[i].count; j++) {
			//printf("\ntohle posilas do lookForItem\n %s", lists -> arrayLists[i].item[j].name);
			if (lookForItem(i, j, lists, shop) == 0)
				lookForItemBigger(i, j, lists, shop);
		}
	}
}

int compareInts(const item_t * a, const item_t * b)
{

	if (a -> rackNumber == -1 && b -> rackNumber != -1)
		return 1;
	if (b -> rackNumber == -1 && a -> rackNumber != -1)
		return -1;
	if (b -> rackNumber == -1 && a -> rackNumber == -1) {
		if (a -> qsortIndex > b -> qsortIndex)
			return 1;
		if (a -> qsortIndex < b -> qsortIndex)
			return -1;
	}

	if (a -> rackNumber > b -> rackNumber) {
		return 1;
	}
	if (b -> rackNumber > a -> rackNumber)
		return -1;
	if (b -> rackNumber == a -> rackNumber) {
		if (a->qsortIndex > b->qsortIndex)
			return 1;
		if (a->qsortIndex < b->qsortIndex)
			return -1;

	}
	return 0;
}

void qsortSort(lol_t * lists)
{
	//printf("%d ve qsortu", lists -> count);
	for (int i = 0; i <= lists -> count; i++){
		qsort(lists -> arrayLists[i].item, lists -> arrayLists[i].count, sizeof(item_t), (int (*)(const void *, const void *)) compareInts);
	}
}

void lastPrint(shop_t * shop, lol_t * lists)
{
	for (int i = 0; i <= lists -> count; i++) {
		printf("Optimalizovany seznam:\n");
		for (int j = 0; j < lists -> arrayLists[i].count; j++) {
			if (lists -> arrayLists[i].item[j].rackNumber == -1){
				printf(" %d. %s -> N/A\n", j, lists -> arrayLists[i].item[j].name);

			}
			else
				printf(" %d. %s -> #%d %s\n", j, lists -> arrayLists[i].item[j].name, lists -> arrayLists[i].item[j].rackNumber, shop -> arrayRacks[lists -> arrayLists[i].item[j].rackNumber].arrayItems[lists -> arrayLists[i].item[j].rackPosition]);
		}

	}

}

int main(void) {
	shop_t shop = {0,0,NULL};
	lol_t lists = {0,0,NULL};
	shop.capacity = 1;
	firstAlloc(&shop);

	if (scanShop(&shop) == 0) {
		freeShop(&shop);
		printf("Nespravny vstup.\n");
		return 1;
	}

	lists.capacity = 1;
	firstAllocL(&lists);
	scanLists(&lists);
	//printShop(&shop);
	//printLists(&lists);

	getRackNumbers(&shop, &lists);

	//printf("%d %d\n", lists.arrayLists[0].item[0].rackNumber, lists.arrayLists[0].item[1].rackNumber);
	//printLists(&lists);


	qsortSort( &lists);
	//printf("\n\n\n------------------------------------------\n\n\n");
	//printLists(&lists);

	lastPrint(&shop, &lists);
	freeLists(&lists);
	freeShop(&shop);

	return 0;
}
