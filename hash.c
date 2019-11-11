/* Fill in your Name and GNumber in the following two comment fields
 * Name:Rushil Nandan Dubey
 * GNumber:G01203932
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "hash.h"

/* (IMPLEMENT THIS FUNCTION)
 * In this function, you will create a new Symtab struct.
 * Follow the Directions in the Project Documentation for this Function
 * Return the pointer to the new symtab.
 * On any memory errors, return NULL
 */
Symtab *hash_initialize() {
  /* Implement this function */
    /* Implement this function */
    
	Symtab *new_symtab = malloc(sizeof(Symtab));//Create a new_symtab and dynamically allocate memory to it in the heap.
	
	if(new_symtab == NULL){//If there is any memory error return NULL.
		printf("Memory Error in hash_initialize");
		return NULL;
	}
	
	Symbol ** new_symbol = malloc(sizeof(Symbol *)*HASH_TABLE_INITIAL);//Create a new table named new_symbol with capacity of size of Symbol pointer multiplied with HASH_TABLE_INITIAL 
	
	if(new_symbol == NULL){
		printf("Memory Error in hahs_initialize");
		return NULL;
	}
	
	int i=0;
	
	for(i=0; i<HASH_TABLE_INITIAL; i++)//Iterarte through each and every index of the table and initialize its each index with NULL.
	{
		new_symbol[i] = NULL;
	}
	new_symtab->table = new_symbol;//Put the pointer value of new table 
	new_symtab->capacity = HASH_TABLE_INITIAL;// Put the capacity of the new_symtab to HASH_TABLE_INITIAl
	new_symtab->size = 0;//Put the size of the new_symtab to zero. 

    return new_symtab;//return the pointer to new_symtab
}

/* (IMPLEMENT THIS FUNCTION)
 * Destroy your Symbol Table.
 * Follow the Directions in the Project Documentation for this Function
 * Return on any memory errors.
 */
void hash_destroy(Symtab *symtab) {
  	int i = 0;
	Symbol * walker = malloc(sizeof(Symbol));//Make a walker to iterarte through the linked list and dynamically allocate the memory to the heap.
	
	if(walker == NULL)//If thereis any memory error just return.
  {
    printf("Memory Error in hash_destroy");
    return;
  }
  
	Symbol * destroy = malloc(sizeof(Symbol));// Make a Symbol pointer to destroy the Symbol in the table one by one.
	if(destroy == NULL)// if no memory has been allocate dto it then just return.
  {
    printf("Memory Error in hah_destroy");
    return;
  }
  
	for(i=0; i<symtab->capacity; i++)//Iterate through each of the index of the table 
	{
		walker=(symtab->table)[i];//initialize the walker every time it the index of the table
		while(walker != NULL)//Iterarte through each Node of the linked list till the walker reaches NULL.
		{
			destroy = walker;
			walker = walker->next;
			free(destroy);
		}
	}
	
	free(walker);//free the memory allocate dto the walker
	free(symtab->table);//free the memory allocated to the table in symtab
	free(symtab);//free the memory allocated to the symtab
    return;
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the capacity of the table inside of symtab.
 * If symtab is NULL, return -1;
 */
int hash_get_capacity(Symtab *symtab) {
  /* Implement this function */
	return symtab->capacity;//return the capacity of the table.
	
	if(symtab == NULL){//if the symtab is NULL then return -1.
  		return -1;
  	}
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the number of used indexes in the table (size) inside of symtab.
 * If symtab is NULL, return -1;
 */
int hash_get_size(Symtab *symtab) {
  /* Implement this function */
  return symtab->size;//return the number of used indexes in the table
}

/* (IMPLEMENT THIS FUNCTION)
 * Adds a new Symbol to the symtab via Hashing.
 * Follow the Directions in the Project Documentation for this Function
 * If symtab is NULL, there are any malloc errors, or if any rehash fails, return -1;
 * Otherwise, return 0;
 */
int hash_put(Symtab *symtab, char *var, int val) {
  /* Implement this function */
 	int flag=0;
	int hash_Index=hash_code(var) % (symtab->capacity);//get the index of the variable by taking modulus of the hash code of the variable with capacity of symtab
	Symbol * walker=malloc(sizeof(Symbol));//dynamically allocating memory to the walker
	Symbol * recent=malloc(sizeof(Symbol));//making a new symbol pointer and dynamically allocating memory in the heap
	
	if(walker==NULL || recent==NULL){//If there is any memory error return -1.
		printf("Memory Error in hash_put");
  		return -1;
  	}
  	
	walker=(symtab->table)[hash_Index];//initializing walker with the symtab table index
		while(walker!=NULL)//iterarting through each index of the table.
		{
			if(strcmp( walker->variable,var)==0)//if variable are equal update walker value.
			{
				walker->val=val;
				flag=1;
			}
		walker=walker->next;
		}
	if(flag==0)//Variables are not equal
	{
		if( ((double)(symtab->size)/(double)(symtab->capacity)) >2.0 )//checking the condition size by capacity
		{
			hash_rehash(symtab,(symtab->capacity)*2 );//Increasing the capacity by factor of two times
		}
		
		Symbol * node = symbol_create(var,val);//Creating a symbol
		
		if(node==NULL){
			printf("Memory Error in hash_put");
    		return -1;
    	}	
		Symbol * head= (symtab->table)[hash_Index];//Pointing the table index to our head node.
		if(head==NULL)//if head is equal to NULL inserting at the head
		{
			head=node;
		}
		else
		{
			recent = head;
			while(recent->next!=NULL)//iterating till NULL encounters.
			{
				recent =recent->next;
			}
			recent->next=node;//Insert at the end
		
		}
		(symtab->table)[hash_Index]=head;
		
		free(walker);
	
		symtab->size=(symtab->size)+1;//Increementing size by one

}
return 0;
}

/* (IMPLEMENT THIS FUNCTION)
 * Gets the Symbol for a variable in the Hash Table.
 * Follow the Directions in the Project Documentation for this Function
 * On any NULL symtab or memory errors, return NULL
 */
Symbol *hash_get(Symtab *symtab, char *var) {
  /* Implement this function */
  int hash_index = (int) (hash_code(var) % HASH_TABLE_INITIAL);//Calculating Index

  Symbol *new_symbol = symtab ->table[hash_index];//Pointing the table at our calculated index to temp
  while(new_symbol)
  {
    if(!strcmp(new_symbol->variable,var))//Checking if our value equals to the Index value
    {
      return symbol_create(new_symbol->variable, new_symbol->val);//return the symbol

    }
    new_symbol = new_symbol->next;
  }
  return NULL;
}

/* (IMPLEMENT THIS FUNCTION)
 * Doubles the size of the Array in symtab and rehashes.
 * Follow the Directions in the Project Documentation for this Function
 * If there were any memory errors, set symtab->array to NULL
 * If symtab is NULL, return immediately.
 */
void hash_rehash(Symtab *symtab, int new_capacity) {
  /* Implement this function */
  Symbol **new_symbol = (Symbol**)malloc(new_capacity*sizeof(Symbol*));//Creating our new table
  if(new_symbol == NULL)
  {
    return;
  }
  for(int i = 0; i < new_capacity; i++)//Iterarting through each and every index of the table
  {
    new_symbol[i] = NULL;
  }

  int old_capacity = symtab -> capacity;

  Symbol **old_symbol = symtab->table;

  symtab->table = new_symbol;//Assigning the table elements
  symtab->size =  0;
  symtab->capacity = new_capacity;

  for(int i=0; i < old_capacity; i++)//assigning our old table values to new table using hash_put
  {
    Symbol *symbol_ptr = old_symbol[i];
    Symbol *reaper = NULL;
    while(symbol_ptr)
    {
      hash_put(symtab,symbol_ptr->variable,symbol_ptr->val);
      reaper = symbol_ptr;
      symbol_ptr = symbol_ptr->next;
      free(reaper);
      reaper = NULL;
    }
  }
  free(old_symbol);//Freeingb previous table
  old_symbol = NULL;
}

/* Implemented for you.
 * Provided function to print the symbol table */
void hash_print_symtab(Symtab *symtab) {
  if(symtab == NULL) {
    return;
  }
  printf("|-----Symbol Table [%d size/%d cap]\n", symtab->size, symtab->capacity);

  int i = 0;
  Symbol *walker = NULL;

  /* Iterate every index, looking for symbols to print */
  for(i = 0; i < symtab->capacity; i++) {
    walker = symtab->table[i];
    /* For each found linked list, print every symbol therein */
    while(walker != NULL) {
      printf("| %10s: %d \n", walker->variable, walker->val);
      walker = walker->next;
    }
  }
  return;
}

/* This function is written for you.
 * This computes the hash function for a String
 */
long hash_code(char *var) {
  long code = 0;
  int i;
  int size = strlen(var);

  for(i = 0; i < size; i++) {
    code = (code + var[i]);
    if(size == 1 || i < (size - 1)) {
      code *= 128;
    }
  }

  return code;
}
