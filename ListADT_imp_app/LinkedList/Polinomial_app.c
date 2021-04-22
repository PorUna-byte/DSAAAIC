//
//  Polinomial_app.c
//  ListADT_imp_app
//
//  Created by PorUnaCabeza on 2021/3/11.
//  Copyright © 2021 PorUnaCabeza. All rights reserved.
//

#include "LinkedList_ADT.h"
PtrToPoly_element Create_Polyelement(float coff,int exp){
    PtrToPoly_element new_Polyelement=(PtrToPoly_element)malloc(sizeof(struct Poly_element));
    new_Polyelement->coff=coff;
    new_Polyelement->exp=exp;
    return new_Polyelement;
}
Listptr Poly_Addition(Listptr A,Listptr B)//Add two polynomials ,the answer is saved in A,O(|A|+|B|)
{
    if(A->Head==NULL)  //if there is an empty list,then return the other one.
        return B;
    if(B->Head==NULL)
        return A;
    Position P=A->Head;//Current pointer in List A
    Position PP=NULL; //The previous pointer of P in List A
    Position Q=B->Head;//Current pointer in List B
    Position QQ=NULL;//An auxiliary Pointer in List B
    while (P!=NULL&&Q!=NULL) {  //when List A and List B are both unfinished,loop,O(|A|+|B|)
         if(P->element->exp>Q->element->exp)
         {
             PP=P;
             P=P->next;
         }
        else if(P->element->exp<Q->element->exp)
        {
            if(PP==NULL)
            {
                A->Head=Q;
            }
            else{
                PP->next=Q;
            }
            QQ=Q->next;
            Q->next=P;
            PP=Q;
            Q=QQ;
        }
        else{
            P->element->coff+=Q->element->coff;
            if((P->element->coff)==0)
            {
                P=P->next;
                QQ=Q;
                Q=Q->next;
                if(PP!=NULL)
                    Delete_by_pos(A, PP);
                else
                {
                    Position tmp=A->Head;
                    A->Head=P;
                    free(tmp);
                }
            }
            else{
                PP=P;
                P=P->next;
                QQ=Q;
                Q=Q->next;
            }
            free(QQ);
        }
    }
    if(P==NULL)  //when PP points to the last element of List A,we can just concatenate List B and return A
    {
        if(PP==NULL)
        A->Head=Q;
        else
        PP->next=Q;
    }
    return A;
}
Listptr Poly_Mult(Listptr A,Listptr B)//Multiply two Polynomials,O(|A|^2*|B|)
{
    Listptr C=MakeEmpty();
    Listptr temp_C=NULL;
    Position P=A->Head;
    Position Q=NULL;
    while(P!=NULL)
    {
        Q=B->Head;
        temp_C=MakeEmpty();
        while(Q!=NULL)//O(|B|)
        {
            if(temp_C->Head==NULL)
               Insert_first_element( Create_Polyelement(P->element->coff*Q->element->coff, P->element->exp+Q->element->exp),temp_C);
            else
                Insert(Create_Polyelement(P->element->coff*Q->element->coff, P->element->exp+Q->element->exp), temp_C, temp_C->Last);
            Q=Q->next;
        }
        C=Poly_Addition(C, temp_C);//O(|A||B|)
        P=P->next;
    }
    return C;
}
Listptr Poly_Divide(Listptr A,Listptr B)//Divide A by B,assume A has a higher order than B initially.
{
    Listptr Quotient=MakeEmpty();
    Listptr Quotient_poly=MakeEmpty();
    Listptr tmp=MakeEmpty();
    Position P=A->Head;
    Position Q=B->Head;
    while(P->element->exp>=Q->element->exp)
    {
        PtrToPoly_element Quotient_single=
        Create_Polyelement(P->element->coff/Q->element->coff, P->element->exp-Q->element->exp);
        if(Quotient->Head==NULL) //Get an item of the resulting Quotient
        Insert_first_element(Quotient_single, Quotient);
        else
        Insert(Quotient_single, Quotient,Quotient->Last);
        Quotient_poly=MakeEmpty();
        Insert_first_element(Quotient_single, Quotient_poly);
        tmp=Poly_Mult(Quotient_poly, B);
        Negative(tmp);
        A=Poly_Addition(A, tmp);
        P=A->Head;
    }
    return Quotient;
}
int main(){
    Listptr A=MakeEmpty();
    Listptr B=MakeEmpty();
    Listptr C;
    printf("Now test begin:\n");
    Insert_first_element(Create_Polyelement(10, 10), A);
    Insert(Create_Polyelement(7, 9), A, A->Last);
    Insert(Create_Polyelement(6, 7), A, A->Last);
    Insert(Create_Polyelement(4, 2), A, A->Last);
    Insert_first_element(Create_Polyelement(-10, 10), B);
    Insert(Create_Polyelement(8, 8), B, B->Last);
    Insert(Create_Polyelement(2, 7), B, B->Last);
    Insert(Create_Polyelement(-4, 2), B, B->Last);
    Insert(Create_Polyelement(5, 1), B, B->Last);
    printf("Add the following two polynomials:\n");
    printf("10x^10+7x^9+6x^7+4x^2\n");
    printf("-10x^10+8x^8+2x^7-4x^2+5x\n");
    printf("The result is:\n");
    C=Poly_Addition(A, B);
    PrintLink(C);
    printf("--------------------\n");
    Listptr D=MakeEmpty();
    Listptr E=MakeEmpty();
    Listptr F;
    Insert_first_element(Create_Polyelement(8, 3), D);
    Insert(Create_Polyelement(4, 2), D, D->Last);
    Insert_first_element(Create_Polyelement(1, 7), E);
    Insert(Create_Polyelement(-2, 1), E, E->Last);
    Insert(Create_Polyelement(1, 0), E, E->Last);
    printf("Multiply the following two polynomials:\n");
    printf("8x^3+4x^2\n");
    printf("x^7-2x+1\n");
    printf("The result is:\n");
    F=Poly_Mult(D, E);
    PrintLink(F);
    Listptr G=MakeEmpty();
    Insert_first_element(Create_Polyelement(8, 6), G);
    Insert(Create_Polyelement(4, 4), G, G->Last);
    Listptr H=MakeEmpty();
    Insert_first_element(Create_Polyelement(2, 2), H);
    Insert(Create_Polyelement(1, 1), H, H->Last);
    Insert(Create_Polyelement(1, 0), H, H->Last);
    Listptr Quotient=MakeEmpty();
    printf("Divide the following two polynomials:\n");
    printf("8x^6+4x^4\n");
    printf("2x^2+x+1\n");
    printf("The result is:\n");
    Quotient=Poly_Divide(G, H);
    printf("Quotient: ");
    PrintLink(Quotient);
    printf("Remainder: ");
    PrintLink(G);
}
