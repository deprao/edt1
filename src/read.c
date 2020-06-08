#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"figures.h"
#include"figlist.h"
#include"geo.h"
#include"qryinspect.h"
#include"qrycustom.h"

char *getfile(char *pathname){
    char *aux = strrchr(pathname,'/');
    if(aux==NULL){
        return strtok(pathname,".");
    }
    return strtok(&aux[1],".");
}

node *geo(char *geofile){
    int n=0,i,size=1000;
    double x,y,w,h,r;
    char *comm = NULL,*cb = NULL,*cp = NULL,*t = NULL;
    node *list=makelist();
    FILE *geo=fopen(geofile,"r");
    if(geo==NULL){
        perror("falha ao abrir arquivo");
        exit(1);
    }

    while(fscanf(geo,"%s",comm)!=EOF){
          if(strcmp(comm,"nx")==0){
              fscanf(geo," %d\n",&size);
          }
          else if(strcmp(comm,"c")==0 && n<size){
              fscanf(geo,"%d %lf %lf %lf %s %s",&i,&r,&x,&y,cb,cp);
              addnode(list,'c',i);
              circle(list,x,y,r,cb,cp);
              n++;
          }
          else if(strcmp(comm,"r")==0 && n<size){
              fscanf(geo,"%d %lf %lf %lf %lf %s %s",&i,&w,&h,&x,&y,cb,cp);
              addnode(list,'r',i);
              rectangle(list,x,y,w,h,cb,cp);
              n++;
          }
          else if(strcmp(comm,"t")==0){
              fscanf(geo,"%d %lf %lf %s %s %s",&i,&x,&y,cb,cp,t);
              addnode(list,'t',i);
              texto(list,x,y,t,cb,cp);
          }
    }
    fclose(geo);
    return list;
}

void qry(node *list,char *qryfile,char *outname){
    char *txtpath=malloc(strlen(outname)+4);
    char *svgpath=malloc(strlen(outname)+4);
    int i,j;
    double x,y;
    char *comm = NULL, *cb = NULL, *cp = NULL;

    sprintf(txtpath,"%s.txt",outname);
    sprintf(svgpath,"%s.svg",outname);
    FILE *qry=fopen(qryfile,"r");
    FILE *out=fopen(txtpath,"w");
    if(qry==NULL || out==NULL){
        perror("falha ao abrir arquivo");
        exit(1);
    }

    while(fscanf(qry,"%s",comm)!=EOF){
        if(strcmp(comm,"o?")==0){
            fscanf(qry,"%d %d",&i,&j);
            intersect(i,j,list,out);
        }
        if(strcmp(comm,"i?")==0){
            fscanf(qry,"%d %lf %lf",&i,&x,&y);
            intern(i,x,y,list,out);
        }
        if(strcmp(comm,"pnt")==0){
            fscanf(qry,"%d %s %s",&i,cb,cp);
            fprintf(out,"pnt %d %s %s\n",i,cb,cp);
            paint(i,cb,cp,list,out);
        }
        if(strcmp(comm,"pnt*")==0){
            fscanf(qry,"%d %d %s %s",&i,&j,cb,cp);
            fprintf(out,"pnt* %d %d %s %s\n",i,j,cb,cp);
            for(int k=i;k<=j;k++)
                paint(k,cb,cp,list,out);
        }
        if(strcmp(comm,"delf")==0){
            fscanf(qry,"%d",&i);
            fprintf(out,"delf %d\n",i);
            list=delete(i,list,out);
        }
        if(strcmp(comm,"delf*")==0){
            fscanf(qry,"%d %d",&i,&j);
            fprintf(out,"delf* %d %d\n",i,j);
            for(int k=i;k<=j;i++)
                list=delete(k,list,out);
        }
    }
    svgen(svgpath,list);
    fclose(qry);
    fclose(out);
}