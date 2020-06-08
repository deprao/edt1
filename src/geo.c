#include<stdio.h>
#include<stdlib.h>
#include"figures.h"

void drawc(double r, double x, double y, char *corp, char *corb,FILE *g){
    fprintf(g,"<circle cx='%lf' cy='%lf' r='%lf' fill='%s' stroke='%s'/>",x,y,r,corp,corb);
}
void drawr(double w,double h, double x, double y, char *corp, char *corb,FILE *g){
    fprintf(g,"<rect x='%lf' y='%lf' width='%lf' height='%lf' fill='%s' stroke='%s'/>",x,y,w,h,corp,corb);
}
void wtext(double x, double y, char *corp, char *corb, char *txto,FILE *g){
    fprintf(g,"<text x='%lf' y='%lf' fill='%s' stroke='%s' >%s</>",x,y,corp,corb,txto);
}
void drawl(double x1,double x2,double y1,double y2,char *corl,FILE *g){
    fprintf(g,"<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' stroke-width='2' stroke='%s'/>",x1,y1,x2,y2,corl);
}
void drawarrayr(double w,double h, double x, double y, char *corb, FILE *g){
    fprintf(g,"<rect x='%lf' y='%lf' width='%lf' height='%lf' fill='none' stroke='%s' stroke-dasharray='4'/>",x,y,w,h,corb);
}

void svgen(char *out,node *list){
    
    FILE *svg;
    svg=fopen(out,"w");
    if(svg==NULL){
      perror("nao foi possivel operar o arquivo");
      exit(1);
    }
    fprintf(svg,"<svg>\n");
    while(list!=NULL){
      switch(list->figtype){
        case 'c':
          drawc(list->figure->c.r,list->figure->c.x,list->figure->c.y,list->figure->c.cp,list->figure->c.cb,svg);
          break;
        case 'r':
          drawr(list->figure->r.w,list->figure->r.h,list->figure->r.x,list->figure->r.y,list->figure->r.cp,list->figure->r.cb,svg);
          break;
        case 't':
          wtext(list->figure->t.x,list->figure->t.y,list->figure->t.cp,list->figure->t.cb,list->figure->t.txt,svg);
          break;
        case 'l':
          drawl(list->figure->l.x1,list->figure->l.x2,list->figure->l.y1,list->figure->l.y2,list->figure->l.cor,svg);
          break;
        case 's':
          drawarrayr(list->figure->r.w,list->figure->r.h,list->figure->r.x,list->figure->r.y,list->figure->r.cb,svg);
          break;
    }
      list=list->next;
  }

    fprintf(svg,"</svg>");
    fclose(svg);
}