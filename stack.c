/* Fill in your Name and GNumber in the following two comment fields
 * Name:Rushil Nandan Dubey
 * GNumber:G01203932
 */
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "stack.h"

/* (IMPLEMENT THIS FUNCTION)
 * Create a new Stack_head struct on the Heap and return a pointer to it.
 * Fol0low the Directions in the Project Documentation for this Function
 * On any malloc errors, return NULL
 */
Stack_head *stack_initialize() {
  /* Implement this function */
  
  Stack_head *new_Head = malloc(sizeof(Stack_head));//Dynamically allocated memory to a new head in order to initialize
  
  if(new_Head == NULL){//Check wether memory has been allocated to new_head in the heap or not and if not then return NULL 
  	printf("Memmory Error in stack_initialize");
  	return NULL;
  }
  
  new_Head->count=0;//Initialize the count of the new_head to 0.
  new_Head->top=NULL;//Initialize the top of the new _head to NULL.
  
  return new_Head;//return the new_head that has been initialized
}

/* (IMPLEMENT THIS FUNCTION)
 * Destroy a stack.
 * Follow the Directions in the Project Documentation for this Function
 * If head is NULL, you can just return.
 */
void stack_destroy(Stack_head *head) {
  /* Implement this function */
  
  if(head == NULL){//Check wether the head passed is NULL and if yes then just return.
  	printf("Head is NULL in the stack_destroy");
  	return;
  }
  
  Node *destroy = NULL;//Create a Node type poiter destroy to free the nodes and initiliaze it to NULL.
  Node *walker = head->top;//Create a Node type pointer walker to iterate through the stack and initialize it to top of stack.
  
  while(walker != NULL){//Iterate the walker till it reach the end of the stack that is NULL.
  	destroy=walker;
  	walker=walker->next;//Increement the walker to next node. 	
  	free(destroy);//Free the node that has been already iterated.
  	destroy=NULL;
  }
  
  return;
}

/* (IMPLEMENT THIS FUNCTION)
 * Push a new Token on to the Stack.
 * Follow the Directions in the Project Documentation for this Function
 * On any malloc errors, return -1.
 * If there are no errors, return 0.
 */
int stack_push(Stack_head *stack, Token *tok) {
  /* Implement this function */
  if(stack == NULL){
  	return -1;
  }
  Node *new_Node = node_create(tok);
   
  if(new_Node == NULL){//Check wether the new_node has been created using node_create is NULL and if yes then return NULL/
  	return NULL;
  }
  
  new_Node->next=stack->top;//Put the new_node next to top of stack. 
  stack->top=new_Node;//Point the top of the stack to the new_node.
  (stack->count)++;//Increement the count by one eveytime its been call;
  return 0;
}

/* (IMPLEMENT THIS FUNCTION)
 * Pop a Token off of the Stack.
 * Follow the Directions in the Project Documentation for this Function
 * If the stack was empty, return NULL.
 */
Token *stack_pop(Stack_head *stack) {
  /* Implement this function */
  if(stack == NULL){
  	return  NULL;
  }
  Node *new_Node = NULL;//Created a new_Node to store the value of top of the stack.
  
  if(stack->top == NULL){//Check if the top of the stack is NULL and if yes then return NULL.
  	printf("Memory  Error in stack_pop");
  	return NULL;
  }
  
  new_Node = stack->top;//Store the value of top of the stack in new_Node.
  Token *new_Token = NULL;//Created a new_Token to store the value of token of the stack top;
  new_Token = stack->top->tok;//Store the token value of the top of the stack in new_Token,
  free(new_Node);//Free the memory allocated to new_Node.
  new_Node = NULL;
  stack->top = stack->top->next;//Increementing the top of the stack to the next of the stack top.
  (stack->count)--;//Decrementing the stack count by one.
  
  return new_Token;//Returning the value of the new_Token.
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the token in the stack node on the top of the stack
 * Follow the Directions in the Project Documentation for this Function
 * If the stack is NULL, return NULL.
 * If the stack is empty, return NULL.
 */
Token *stack_peek(Stack_head *stack) {
  /* Implement this function */
  if(stack == NULL){
  	return  NULL;
  }
  if(stack->top != NULL){//Check if the top of the stack is NULL or not and if not then return token of the top of the stack.
  	return stack->top->tok;
  }
  
  else{
  	return NULL;//If top of the stack is NULL then return NULL.
  }
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the number of nodes in the stack.
 * Follow the Directions in the Project Documentation for this Function
 * If stack is NULL, return -1.
 * Return 1 if the stack is empty or 0 otherwise.
 */
int stack_is_empty(Stack_head *stack) {
  /* Implement this function */
  if(stack == NULL){//Check if the stack passed is NULL or not and if yes then return NULL.
  	return NULL;
  }
  
  if(stack->count == 0){//Check the count of the stack and if it is zero, it means the stack is empty and return 1.
  	return 1;
  }
  
  else{//If the stack is not empty then return 0.
  	return 0;
  }
  
}

/* These two functions are written for you.
 * It recurses the stack and prints out the tokens in reverse order
 * eg. top->2->4->1->8 will print at Stack: 8 1 4 2
 * eg. stack_push(5) will then print Stack: 8 1 4 2 5
 */

/* This is implemented for you.
 * Recursive print. (Local function)
 * Base Case: node == NULL, return
 * Recursive Case: call print_node(node->next, print_data), then print node.
 */
static void print_node(Node *node) {
  if(node == NULL) {
    return;
  }
  token_print(node->tok);
  print_node(node->next);
  return;
}

/* This is implemented for you.
 * Setup function for the recursive calls.  Starts printing with stack->top
 */
void stack_print(Stack_head *stack) {
  if(stack == NULL) {
    return;
  }
  printf("|-----Program Stack\n");
  printf("| ");
  print_node(stack->top);
  printf("\n");
  return;
}
