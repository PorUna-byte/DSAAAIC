//
//  Evaluate_expression.c
//  Stack_imp_app
//
//  Created by PorUnaCabeza on 2021/3/15.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "StackADT.h"
//#define MAXStack_Size 20
int IsDigit(char ch)
{
    if('0'<=ch&&ch<='9')
        return 1;
    else
        return 0;
}
int IsSpace(char ch)
{
    return ch==' ';
}
int IsEnd(char ch)
{
    return ch=='\0';
}
//Judge wheater a character is an operator or not
//if it is ,assign an order for it.
int IsOperator(char ch)
{
    switch (ch) {
        case '*':
            return 2;
        case '/':
            return 2;
        case '+':
            return 1;
        case '-':
            return 1;
        default:
            return 0;
    }
}
//Evaluate the value for a number consists of multiple sequential digits.
int Eval_number(char ** expression)
{
    int sum=0;
    while(IsDigit(**expression))
    {
        sum=sum*10+(**expression-'0');
        (*expression)++;
    }
    (*expression)--;
    return sum;
}
//Pop out two operants from the operants_stack
//Pop out an operator from the operator_stack
//Calculate the result via applying the operator on the two operants
//Push the result into operants_stack
void Calculator(Stack operants,Stack operators)
{
    int operant_b=TOPandPOP(operants);
    int operant_a=TOPandPOP(operants);
    int ans=0;
    switch (TOPandPOP(operators)) {
        case '+':
            ans=operant_a+operant_b;
            break;
        case '-':
            ans=operant_a-operant_b;
            break;
        case '*':
            ans=operant_a*operant_b;
            break;
        case '/':
            ans=operant_a/operant_b;
            break;
        default:
            break;
 }
       PUSH(operants, ans);
}
//Evaluate the inverse polish notation
int Eval_inversepolish(char* expression)
{
    int order=0;
    Stack numbers=CreateStack();
    for(;!IsEnd(*expression);expression++){ //scan over the expression
     if(IsSpace(*expression))
         continue;
     if(IsDigit(*expression))
     {
         PUSH(numbers, Eval_number(&expression));
         continue;
     }
     if((order=IsOperator(*expression)))
     {
         int operant_b=TOPandPOP(numbers);
         int operant_a=TOPandPOP(numbers);
         int ans=0;
         switch (*expression) {
             case '+':
                 ans=operant_a+operant_b;
                 break;
             case '-':
                 ans=operant_a-operant_b;
                 break;
             case '*':
                 ans=operant_a*operant_b;
                 break;
             case '/':
                 ans=operant_a/operant_b;
                 break;
             default:
                 break;
         }
         PUSH(numbers, ans);
         continue;
     }
    }
    return TOPandPOP(numbers);
}
//Evaluate the infix notation
int Eval_infix(char* expression)
{
    Stack operants=CreateStack();
    Stack operators=CreateStack();
    int order=0;
    for(;!IsEnd(*expression);expression++){
        if(IsSpace(*expression))
            continue;
        if(IsDigit(*expression))
        {
            PUSH(operants, Eval_number(&expression));
            continue;
        }
        if((order=IsOperator(*expression)))
        {
            if(IsEmpty(operators))
            {
                PUSH(operators, *expression);
                continue;
            }
            int inner_order=IsOperator(TOP(operators));
                while (order<=inner_order)  // call Calculator to evaluate until the operator_stack is empty or
                    //the order of this operator is greater than the order of the operator at the top of the operator_stack
                {
                Calculator(operants, operators);
                if(IsEmpty(operators))
                    break;
                inner_order=IsOperator(TOP(operators));//get the order of the new operator at the top of stack
                }
            }
        if(*expression=='(')
        {
            PUSH(operators, *expression);
            continue;
        }
        if(*expression==')')
        {
            while(TOP(operators)!='(')  //When we see a ')' we call Calculator until we see a '(' at the top of operator_stack
                Calculator(operants, operators);
            POP(operators);
        }
            if(*expression!=')')
            PUSH(operators, *expression);
        }
    
    while(!IsEmpty(operators))
        Calculator(operants, operators);
    
    return TOPandPOP(operants);
    }

int main(){
    char *exp1="6 5 3 2 - 8 * + 3 + *";
    printf("Eval %s is:%d\n",exp1,Eval_inversepolish(exp1));
    char *exp2="5 3 2 + 8 * + 3 + 6";
    printf("Eval %s is:%d\n",exp2,Eval_inversepolish(exp2));
    char *exp3="60 5 3 2 - 8 * + 3 + *";
    printf("Eval %s is:%d\n",exp3,Eval_inversepolish(exp3));
    char *exp4="33*(8-2)+3-4/2+5";
    printf("Eval %s is:%d\n",exp4,Eval_infix(exp4));
}
