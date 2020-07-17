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
    char comm[3],cb[20],cp[20],t[40];
    node *list=makelist();
    FILE *geoarq=fopen(geofile,"r");
    if(geoarq==NULL){
        perror("falha ao abrir arquivo");
        exit(1);
    }

    while(fscanf(geoarq,"%s",comm)!=EOF){
          if(strcmp(comm,"nx")==0){
              fscanf(geoarq," %d\n",&size);
          }
          else if(strcmp(comm,"c")==0 && n<size){
              fscanf(geoarq,"%d %lf %lf %lf %s %s",&i,&r,&x,&y,cb,cp);
              list=addnode(list,'c',i);
              circle(list,x,y,r,cb,cp);
              n++;
          }
          else if(strcmp(comm,"r")==0 && n<size){
              fscanf(geoarq,"%d %lf %lf %lf %lf %s %s",&i,&w,&h,&x,&y,cb,cp);
              list=addnode(list,'r',i);
              rectangle(list,x,y,w,h,cb,cp);
              n++;
          }
          else if(strcmp(comm,"t")==0){
              fscanf(geoarq,"%d %lf %lf %s %s",&i,&x,&y,cb,cp);
              fgets(t,40,geoarq);
              list=addnode(list,'t',i);
              texto(list,x,y,t,cb,cp);
          }
    }
    fclose(geoarq);
    return list;
}

void qry(node *list,char *qryfile,char *outname){
    char *txtpath=malloc(strlen(outname)+5);
    char *svgpath=malloc(strlen(outname)+5);
    int i,j;
    double x,y;
    char comm[6], cb[20], cp[20];

    sprintf(txtpath,"%s.txt",outname);
    sprintf(svgpath,"%s.svg",outname);
    FILE *qryarq=fopen(qryfile,"r");
    FILE *out=fopen(txtpath,"w");
    if(qryarq==NULL || out==NULL){
        perror("falha ao abrir arquivo");
        exit(1);
    }

    while(fscanf(qryarq,"%s",comm)!=EOF){
        if(strcmp(comm,"o?")==0){
            fscanf(qryarq,"%d %d",&i,&j);
            intersect(i,j,list,out);
        }
        if(strcmp(comm,"i?")==0){
            fscanf(qryarq,"%d %lf %lf",&i,&x,&y);
            intern(i,x,y,list,out);
        }
        if(strcmp(comm,"pnt")==0){
            fscanf(qryarq,"%d %s %s",&i,cb,cp);
            fprintf(out,"pnt %d %s %s\n",i,cb,cp);
            paint(i,cb,cp,list,out);
        }
        if(strcmp(comm,"pnt*")==0){
            fscanf(qryarq,"%d %d %s %s",&i,&j,cb,cp);
            fprintf(out,"pnt* %d %d %s %s\n",i,j,cb,cp);
            for(int k=i;k<=j;k++)
                paint(k,cb,cp,list,out);
        }
        if(strcmp(comm,"delf")==0){
            fscanf(qryarq,"%d",&i);
              list=delf(i,list,out);
        }
        if(strcmp(comm,"delf*")==0){
            fscanf(qryarq,"%d %d",&i,&j);
            fprintf(out,"delf* %d %d\n",i,j);
            for(int k=i;k<=j;k++)
                list=delf(k,list,out);
        }
    }
    svgen(svgpath,list);
    fclose(qryarq);
    fclose(out);
    free(txtpath);
    free(svgpath);
}