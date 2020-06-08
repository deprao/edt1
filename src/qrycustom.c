#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"figures.h"
#include"figlist.h"

void paint(int i,char *cb,char *cp,node *list,FILE *out){
    list=searchfig(list,i);
    switch(list->figtype){
       case 'c':
         fprintf(out,"%d: %lf %lf\n",i,list->figure->c.x,list->figure->c.y);
         strcpy(list->figure->c.cb,cb);
         strcpy(list->figure->c.cp,cp);
         break;
       case 'r':
         fprintf(out,"%d: %lf %lf\n",i,list->figure->r.x,list->figure->r.y);
         strcpy(list->figure->r.cb,cb);
         strcpy(list->figure->r.cp,cp);
         break;
       case 't':
          fprintf(out,"%d: %lf %lf\n",i,list->figure->t.x,list->figure->t.y);
          strcpy(list->figure->t.cb,cb);
          strcpy(list->figure->t.cp,cp);
          break;
    }
         
}

node *delete(int i,node *list,FILE *out){
      node *aux;

     aux=searchfig(list,i);
     switch(aux->figtype){
        case 'c':
         fprintf(out,"%d: %lf %lf %lf %s %s\n",i,aux->figure->c.x,aux->figure->c.y,aux->figure->c.r,aux->figure->c.cb,aux->figure->c.cp);
         break;
        case 'r':
         fprintf(out,"%d: %lf %lf %lf %lf %s %s\n",i,aux->figure->r.x,aux->figure->r.y,aux->figure->r.w,aux->figure->r.h,aux->figure->r.cb,aux->figure->r.cp);
         break;
        case 't':
          fprintf(out,"%d: %lf %lf %s %s %s\n",i,aux->figure->t.x,aux->figure->t.y,aux->figure->t.txt,aux->figure->t.cb,aux->figure->t.cp);
          break;
     }
     list=deletefig(list,i);
     return list;
}