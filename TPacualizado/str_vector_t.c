#include <stdio.h>
#include "str_vector_t.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void str_vector_new(vector_t *v){
	v->dimL=0;
	v->dimF=0;
	v->elements=NULL;
	}
	
void str_vector_append (vector_t *v,char *string){
	if (v->dimF==v->dimL)
		v->elements=realloc(v->elements,(++v->dimF)*sizeof(char*));
	v->elements[(v->dimL)++]=string;
	}
	
int strcmpa(const void *a,const void *b){
		return strcmp(*(char * const*)a,*(char * const *)b);
	}
	
int strcmpd(const void *a,const void *b){
		return strcmp(*(char * const*)b,*(char * const *)a);
	}
	
int aleatorio_en_rango(int minimo,int maximo){
	srand(time(NULL));
	return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) +1);
	}
	
void str_vector_append_sorted(vector_t *v,char *string,sort_mode_t mode){
	int j=0;
	vector_t vTemp=*v;
	switch(mode){
		case s_asc:
			   while(strcmp(string,vTemp.elements[j])>0)
				   j++;
				str_vector_set(vTemp,j,string)
		break;
		case s_desc:
				while(strcmp(string,vTemp.elements[j])<0)
				   j++;
				str_vector_set(vTemp,j,string)
		break;
		case s_ran:;
				int indiceAleatorio=aleatorio_en_rango(0,vTemp.dimL-1);
				str_vector_set(vTemp,indiceAleatorio,string)
		}
		*v=vTemp;
	}
	
void ordenarAleatorio(vector_t *v){
	for (int i=0;i<v->dimL;i++){
		int indiceAleatorio=aleatorio_en_rango(0,v->dimL-1);
		char *temporal=v->elements[i];
		v->elements[i]=v->elements[indiceAleatorio];
		v->elements[indiceAleatorio]=temporal;
		}
	}
	

void str_vector_sort(vector_t *v,sort_mode_t mode){
		switch(mode){
		case s_asc:
				qsort(v->elements,v->dimL,sizeof(char*),(__compar_fn_t) strcmpa);
			break;
		case s_desc:
				qsort(v->elements,v->dimL,sizeof(char*),(__compar_fn_t) strcmpd);
			break;
		case s_ran:
				ordenarAleatorio(v);
			break;
		}
	}
	
void str_vector_resize(vector_t *v,unsigned elements){
	v->elements=realloc(v->elements,elements*sizeof(char*));
	v->dimF=elements;
	if (v->dimL>elements)
		v->dimL=elements;
	}
	
void str_vector_free(vector_t v){
	v.dimF=0;
	v.dimL=0;
	free(v.elements);
	}

int main(){
    vector_t v;
    str_vector_new(&v);
    str_vector_append(&v,"boca");
    str_vector_append(&v,"wits");
    str_vector_append(&v,"arbol");
    str_vector_append(&v,"zorr");
    str_vector_append(&v,"celular");
    //str_vector_set(&v,4,"arbo");
    char *recuperar=str_vector_get(v,0);
    if (recuperar!=NULL)
		printf("dato recuperado: %s\n",recuperar);
	str_vector_set(v,2,"probando");
	str_vector_sort(&v,s_asc);
	str_vector_append_sorted(&v,"cartera",s_asc);
	//str_vector_resize(&v,2);
	for (int i=0;i<v.dimL;i++){
		puts(v.elements[i]);
	}
		
	str_vector_free(v);
	}
