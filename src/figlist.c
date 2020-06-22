#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"figures.h"

node *makelist(){
    return NULL;
}

node *addnode(node *list,char type,int index){
    node *aux;

    if(list==NULL){
        list=malloc(sizeof(node));
        list->figtype=type;
        list->i=index;
        list->figure=NULL;
        list->next=NULL;
    }else{
        aux=list;
        while(aux->next!=NULL)
            aux=aux->next;
        
        aux->next=malloc(sizeof(node));
        aux->next->figtype=type;
        aux->next->i=index;
        aux->next->figure=NULL;
        aux->next->next=NULL;
    }
    return list;
}

node *searchfig(node *list,int index){
    while(list!=NULL){
        if(list->i==index)
           return list;
        list=list->next;
    }
    return NULL;
}

node *deletefig(node *list,int index){
    node *aux2,*aux=list;

    while(aux!=NULL){
        if(aux->i==index){
            if(aux==list){
            list=list->next;
            free(aux->figure);
            free(aux);
            }else{
                aux2->next=aux->next;
                free(aux->figure);
                free(aux);
            }
            return list;
        }
        aux2=aux;
        aux=aux->next;
    }
    return list;
}

void deletelist(node *list){
    node *aux;

    while(list!=NULL){
        aux=list;
        list=list->next;
        free(aux->figure);
        free(aux);
    }
}

void circle(node *list,double x,double y,double r,char *cb,char *cp){
    while(list->figure!=NULL)
       list=list->next;
    list->figure=malloc(sizeof(double)*3 + sizeof(char)*40);
    list->figure->c.x=x;
    list->figure->c.y=y;
    list->figure->c.r=r;
    strcpy(list->figure->c.cb,cb);
    strcpy(list->figure->c.cp,cp);
     
}
void rectangle(node *list,double x,double y,double w,double h,char *cb,char *cp){
     while(list->figure!=NULL)
       list=list->next;
    list->figure=malloc(sizeof(double)*4+sizeof(char)*40);
    list->figure->r.x=x;
    list->figure->r.y=y;
    list->figure->r.w=w;
    list->figure->r.h=h;
    strcpy(list->figure->r.cb,cb);
    strcpy(list->figure->r.cp,cp);
}
void texto(node *list,double x,double y,char *t,char *cb,char *cp){
    while(list->figure!=NULL)
       list=list->next;
    list->figure=malloc(sizeof(double)*2+sizeof(char)*80);
    list->figure->t.x=x;
    list->figure->t.y=y;
    strcpy(list->figure->t.txt,t);
    strcpy(list->figure->t.cb,cb);
    strcpy(list->figure->t.cp,cp);
}
void linha(node *list,double x1,double x2,double y1,double y2,char *c){
    while(list->figure!=NULL)
       list=list->next;
    list->figure=malloc(sizeof(double)*4+sizeof(char)*20);
    list->figure->l.x1=x1;
    list->figure->l.y1=y1;
    list->figure->l.x2=x2;
    list->figure->l.y2=y2;
    strcpy(list->figure->l.cor,c);
}