#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"figures.h"
#include"figlist.h"



void intcircrect(node *list,circ c,rect r,FILE *out){
      double dx,dy,x,y,w,h;
      
      if(c.x > r.x)
          dx=pow(r.x+r.w-c.x,2);
      else
          dx=pow(r.x-c.x,2);
      
      if(c.y>r.y)
          dy=pow(r.y+r.h-c.y,2);
      else
          dy=pow(r.y-c.y,2);
      
      x=fmin(r.x,c.x-c.r);
      y=fmin(r.y,c.y-c.r);
      h=fmax(r.y+r.h,c.y+c.r)-y;
      w=fmax(r.x+r.w,c.x+c.r)-x;

      if(c.r>=sqrt(dx+dy)){
          fprintf(out,"SIM");
          addnode(list,'r',0);
          rectangle(list,x,y,w,h,"black","none");
      }else{
          fprintf(out,"NAO");
          addnode(list,'s',0);
          rectangle(list,x,y,w,h,"black","none");
      }  
}
void intcircle(node *list,circ c1,circ c2,FILE *out){
    double x,y,h,w,d;

    d=sqrt(pow(c1.x-c2.x,2)+pow(c1.y-c2.y,2));
    
    y=fmin(c1.y-c1.r,c2.y-c2.r);
    x=fmin(c1.x-c1.r,c2.x-c2.r);
    h=fmax(c1.y+c1.r,c2.y+c2.r)-y;
    w=fmax(c1.x+c1.r,c2.x+c2.r)-x;

    if(d<=c1.r+c2.r){
        fprintf(out,"SIM");
        addnode(list,'r',0);
        rectangle(list,x,y,w,h,"black","none");
    }else{
        fprintf(out,"NAO");
        addnode(list,'s',0);
        rectangle(list,x,y,w,h,"black","none");
    }
    
}
void intrectangle(node *list,rect r1,rect r2,FILE *out){
    double x,y,w,h;

    x=fmin(r1.x,r2.x);
    y=fmin(r1.y,r2.y);
    w=fmax(r1.x+r2.w,r1.x+r2.w)-x;
    h=fmax(r1.y+r2.h,r1.y+r2.h)-y;

    if(w<=r1.w+r2.w && h<=r1.h+r2.h){
        fprintf(out,"SIM");
        addnode(list,'r',0);
        rectangle(list,x,y,w,h,"black","none");
    }else{
        fprintf(out,"NAO");
        addnode(list,'s',0);
        rectangle(list,x,y,w,h,"black","none");
    }
    
}
void intersect(int i,int j,node *list,FILE *out){
    node *root=list,*list2;

    fprintf(out,"o? %d %d\n",i,j);
    list=searchfig(root,i);
        switch(list->figtype){
         case 'c':
           fprintf(out,"%d: círculo ",i);
           break;
         case 'r':
           fprintf(out,"%d: retângulo ",i);
           break;
         default:
            perror("consulta nao manipulavel");
            return;
        }
    list2=searchfig(root,j);
       switch(list2->figtype){
        case 'c':
          fprintf(out,"%d: círculo ",j);
          break;
        case 'r':
          fprintf(out,"%d: retângulo ",j);
          break;
        default:
          perror("consulta nao manipulavel");
          return;
       }

    if(list->figtype!=list2->figtype){
        if(list->figtype=='c')
            intcircrect(root,list->figure->c,list2->figure->r,out);
        else if(list->figtype=='r')
            intcircrect(root,list2->figure->c,list->figure->r,out);
    }else{
        if(list->figtype=='c' && list2->figtype=='c')
            intcircle(root,list->figure->c,list2->figure->c,out);
        else
            intrectangle(root,list->figure->r,list2->figure->r,out);
    }   
}

void intpointcircle(double x,double y,node *list,circ c,FILE *out){
    double d;
    char *cpt = NULL;

    d=sqrt(pow(x-c.x,2)+pow(y-c.y,2));
    if(d<=c.r){
        fprintf(out,"INTERNO");
        strcpy(cpt,"blue");
    }else{
        fprintf(out,"NAO INTERNO");
        strcpy(cpt,"magenta");
    }
    addnode(list,'c',0);
    circle(list,x,y,2.5,"none",cpt);
    addnode(list,'l',0);
    linha(list,c.x,x,c.y,y,cpt);
}
void intpointrect(double x,double y,node *list,rect r,FILE *out){
    char *cpt = NULL;
    
    if(fdim(x,r.x)<=r.w && fdim(x,r.x)!=0 && fdim(y,r.y)<=r.h && fdim(y,r.y)!=0){
        fprintf(out,"INTERNO");
        strcpy(cpt,"blue");
    }else{
        fprintf(out,"NAO INTERNO");
        strcpy(cpt,"magenta");
    }
    addnode(list,'c',0);
    circle(list,x,y,2.5,"none",cpt);
    addnode(list,'l',0);
    linha(list,r.x,x,r.y,y,cpt);
}
void intern(int i,double x,double y,node *list,FILE *out){
    node *root=list;

    fprintf(out,"i? %d %lf %lf\n",i,x,y);
    list=searchfig(list,i);
    switch(list->figtype){
        case 'c':
         fprintf(out,"%d: círculo ",i);
         intpointcircle(x,y,root,list->figure->c,out);
         break;
        case 'r':
         fprintf(out,"%d: retângulo ",i);
         intpointrect(x,y,root,list->figure->r,out);
         break;
        default: 
         perror("consulta nao manipulavel");
         return;
         }

}