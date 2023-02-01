#ifndef STR_VECTOR_T_H
#define STR_VECTOR_T_H
#define str_vector_get(v,index) ((index>=0 && index<v.dimL && v.elements[index]!=NULL)? v.elements[index]: NULL)
#define str_vector_set(v,index,elemento)  if (v.dimF==v.dimL) v.elements=realloc(v.elements,++(v.dimF)*sizeof(char*));\
		for (int i=v.dimL;i>index;i--) v.elements[i]=v.elements[i-1];\
		v.elements[index]=elemento; (v.dimL)++;\
		
	
struct str_vector_t{
	int dimF;
	int dimL;
	char **elements;
	};
	
typedef struct str_vector_t vector_t;

typedef enum sort_mode{s_asc,s_desc,s_ran} sort_mode_t;

void str_vector_new(vector_t *v);

void str_vector_append (vector_t *v,char *string);

void str_vector_append_sorted(vector_t *v,char *string,sort_mode_t mode);

void str_vector_sort(vector_t *v,sort_mode_t mode);

void str_vector_resize(vector_t *v,unsigned elements);

void str_vector_free(vector_t v);

#endif
