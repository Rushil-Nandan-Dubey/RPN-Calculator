/* Fill in your Name and GNumber in the following two comment fields
 * Name:Rushil Nandan Dubey
 * GNumber:G01203932
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "token.h"
#include "hash.h"

/* Local Function Declarations (that you need to finish implementing) */
static int read_file(char *filename, char *line);
static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok);

/* Pre-Written Local Function Declarations */
static void print_header(char *filename, int step);
static void print_step_header(int step);
static void print_step_footer(Symtab *symtab, Stack_head *stack);
static void print_step_output(int val);

/* Defines the largest line that can be read from a file */
#define MAX_LINE_LEN 255

/* This has been written for you.
 * Main function to run your program (written for you).
 * 1) Opens the file using the passed in filename. (your function)
 * -- If the file is not found (ie. fopen returns NULL), then exit(-1);
 * 2) Reads one line from the file.
 * -- The programs will all only be one line in size.
 * -- That line may be up to MAX_LINE_LEN long.
 * 3) Closes the file.
 * 4) Calls token_read_line(line, strlen(line))
 * -- This parses the line and prepares the tokens to be ready to get.
 * 5) While there are tokens remaining to parse: token_has_next() != 0
 * -- a) Get the next token: token_get_next()
 * 6) Parse the token (your function)
 * 7) Print out all of the relevant information
 */
int rpn(Stack_head *stack, Symtab *symtab, char *filename) {
  int step = 0; /* Used to track the program steps */
  int ret = 0;
  char line[MAX_LINE_LEN];
  Token *tok = NULL;

  /* Complete the read_file function that is defined later in this file. */
  ret = read_file(filename, line);
  if(ret != 0) {
    printf("Error: Cannot Read File %s.  Exiting\n", filename);
    exit(-1);
  }

  /* Pass the line into the tokenizer to initialize that system */
  token_read_line(line, strlen(line));

  /* Prints out the nice program output header */
  print_header(filename, step);

  /* Iterate through all tokens */
  while(token_has_next()) {
    /* Begin the next step of execution and print out the step header */
    step++; /* Begin the next step of execution */
    print_step_header(step);

    /* Get the next token */
    tok = token_get_next();
    /* Complete the implementation of this function later in this file. */
    ret = parse_token(symtab, stack, tok);
    if(ret != 0) {
      printf("Critical Error in Parsing.  Exiting Program!\n");
      exit(-1);
    }

    /* Prints out the end of step information */
    print_step_footer(symtab, stack);
  }

  return 0;
}

/* (IMPLEMENT THIS FUNCTION)
 * Local function to open a file or exit.
 * Follow the Directions in the Project Documentation for this Function
 * Open filename, read its contents (up to MAX_LINE_LEN) into line, then
 *   close the file and return 0.
 * On any file error, return -1.
 */
static int read_file(char *filename, char *line) {
  /* Implement This Function */
  
  FILE *fp = fopen(filename,"r");//Create a File type Pointer fp and open the file named filename in read mode.
   
  if(fp == NULL){//If any file error occurs return -1.
  	printf("Memory erroe in read_file");
  	return -1;
  }
  
  fgets(line,MAX_LINE_LEN,fp);//This will read in at most one less size characteters from the stream and stores them into the buffer. 
  fclose(fp);//Close the file that is being opened after reading the required data.
  
  return 0;//On successfull execution of file read funtion return 0.
}

/* (IMPLEMENT THIS FUNCTION)
 * Parses the Token to implement the rpn calculator features
 * Follow the Directions in the Project Documentation for this Function                                                                                                                                                                    
 * You may implement this how you like, but many small functions would be good!
 * If the token you are passed in is NULL, return -1.
 * If there are any memory errors, return -1.
 */
 static Token* operator_function(Token * tok, Token * element1, Token * element2);
 static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok) {
  /* Implement This Function */
  
  	if(tok == NULL){//Check if the passed token is NULL or not and if yes then return -1.
  		printf("Memory Error in parse_token");
  		return -1;
	}
	
	if(tok->type == TYPE_VARIABLE)//If the type of the token is variable then directly push it on the stack.
	{
		stack_push(stack,tok);
	}
	
	if(tok->type == TYPE_OPERATOR)//Check if the token is of operator type.
	{
		Token * element1 = malloc(sizeof(Token));//Create a new token to store the value
		
		if(element1 == NULL){//Check if the element1 is NULL and if yes then return -1.
			printf("Memory Error in parse_token");
			return -1;
		}
		
		Token * element2 = malloc(sizeof(Token));//Create a second new token to store the value
		
		if(element2 == NULL){//Check if the element2 is NULL and if yes then return -1.
			printf("Memory Error in parse_token");
			return -1;
		}
		
		Token * result = malloc(sizeof(Token));//Create token to store the result
		
		if(result == NULL){//Check if the result is NULL and if yes then return -1.
			printf("Memory Error in parse_token");
			return -1;
		}
		//pop top two values from top of the stack
		element1 = stack_pop(stack);
		element2 = stack_pop(stack);
		//if both element1 and element2 are of value type then directly perform operator function
		if( (element1->type == TYPE_VALUE) && (element2->type == TYPE_VALUE) )
		{
			result = operator_function(tok,element1,element2);
			stack_push(stack,result);
		}
		else
		{
			//if element1 is of variable type then take its value from the hash table.
			if(element1->type == TYPE_VARIABLE && element2->type == TYPE_VALUE)
			{
				Symbol * symbol1 = malloc(sizeof(Symbol));
				if(symbol1 == NULL){
					printf("Memory Error in parse_token");
					return -1;
				}
			
				symbol1 = hash_get(symtab,element1->variable);
				element1 = token_create_value(symbol1->val);
				//take the value from the operator_function and push it on the stack
				result = operator_function(tok,element1,element2);
				stack_push(stack,result);
			}
			//if element2 is of variable type then take its value from the hash table.
			if(element2->type == TYPE_VARIABLE && element1->type == TYPE_VALUE)
			{
				Symbol * symbol2 = malloc(sizeof(Symbol));
				if(symbol2 == NULL){
					printf("Memory Error in parse_token");
					return -1;
				}
						
				symbol2 = hash_get(symtab,element2->variable);
				element2 = token_create_value(symbol2->val);
				result = operator_function(tok,element1,element2);
				stack_push(stack,result);
			}
			//if element1 and element2 is of variable type then take their values from the hash table.
			if(element1->type == TYPE_VARIABLE && element2->type == TYPE_VARIABLE){
				
				Symbol * symbol1 = malloc(sizeof(Symbol));
				if(symbol1 == NULL){
					printf("Memory Error in parse_token");
					return -1;
				}
				
				Symbol * symbol2 = malloc(sizeof(Symbol));
				if(symbol2 == NULL){
					printf("Memory Error in parse_token");
					return -1;
				}
				symbol1 = hash_get(symtab,element1->variable);
				element1 = token_create_value(symbol1->val);
				symbol2 = hash_get(symtab,element2->variable);
				element2 = token_create_value(symbol2->val);
				//take the value from the operator_function and push it on the stack
				result = operator_function(tok,element1,element2);
				stack_push(stack,result);
			}
		}
	}
	
	if(tok->type == TYPE_VALUE)//if the token is of value type then directly push that value on the stack
	{
		stack_push(stack,tok);
	}
	//check if the token is of assignment type
	if(tok->type == TYPE_ASSIGNMENT)
	{
		//create a new token to store the value 
		Token * value1 = malloc(sizeof(Token));
		if(value1 == NULL){
			printf("Memory Error in parse_token");
			return -1;
		}
		//create a new token to a variable
		Token * value2 = malloc(sizeof(Token));
		if(value2 == NULL){
			printf("Memmory Error in parse_token"); 
			return -1;
		}
		
		
		//take the value1 and value2 from top of the stack 
		value1 = stack_pop(stack);
		value2 = stack_pop(stack);
		//put the value in the hash table. 
		hash_put(symtab,value2->variable,value1->value);
		token_free(value1);
		token_free(value2);
		}
		
	if(tok->type == TYPE_PRINT){//check if the token is of print type
		Token *new_token = stack_pop(stack);//create a new token to peek the value from the stack
		
		if(new_token->type == TYPE_VARIABLE){
			Symbol *new_symbol = hash_get(symtab,new_token->variable);//if the token is of variable type then get the value from hash table
			print_step_output(new_symbol->val);//print the value using print_step_output
		}
		
		if(new_token->type == TYPE_VALUE){//if the token is of print type then directly print the value using print_step_output.
			print_step_output(new_token->value);
		}
		
	}
	
      	return 0;
      	
}


static Token* operator_function(Token * tok, Token * element1, Token * element2)
{
	Token * result = malloc(sizeof(Token));//Create a new token to store the final result after operator function.
		
	if(result == NULL){//if the result is NULL return -1.
		printf("Memory Error in operator_function");
		return -1;
	}

	if(tok->oper == OPERATOR_PLUS)//if the token is of plus type then do the addition operation
	{	
		result = token_create_value( (element2->value) + (element1->value) );
	}
	
	if(tok->oper == OPERATOR_MINUS)//if the token is of minus type then do the subtraction operation
	{
		result = token_create_value( (element2->value) - (element1->value) );
	}
	
	if(tok->oper == OPERATOR_MULT)//if the token is of multiply type then do the multiplication operation
	{
		result = token_create_value( (element2->value) * (element1->value) );
	}
	
	if(tok->oper == OPERATOR_DIV)//if the token is of division type then do the division operation
	{
		result = token_create_value( (element2->value) / (element1->value) );
	}
	
	//free the token that are being used
	token_free(element1);
	token_free(element2);
	
	return result;//return the final result.
	
}
/* This has been written for you.
 * Prints out the main output header
 */
static void print_header(char *filename, int step) {
  printf("######### Beginning Program (%s) ###########\n", filename);
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step);
  token_print_remaining();
  printf("o-------------------\n");
}

/* This has been written for you.
 * Prints out the information at the top of each step
 */
static void print_step_header(int step) {
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step++);
}

/* This has been written for you.
 * Prints out the output value (print token) nicely
 */
static void print_step_output(int val) {
  printf("|-----Program Output\n");
  printf("| %d\n", val);
}

/* This has been written for you.
 * Prints out the information at the bottom of each step
 */
static void print_step_footer(Symtab *symtab, Stack_head *stack) {
  hash_print_symtab(symtab);
  stack_print(stack);
  token_print_remaining();
  printf("o-------------------\n");
}
