#include <stdio.h>                      /* printf */
#include <stdlib.h>                     /* exit */
#include <getopt.h>                     /* getopt */
#include <stdbool.h>                    /* Booleans */

extern char *optarg;
extern int  opterr;
//extern int optind, opterr, optopt;

#define OP_ARG_R        'r'
#define OP_ARG_R_LONG   "reverse"

#define OP_ARG_S        's'
#define OP_ARG_S_LONG   "shuffle"

#define OP_ARG_I        'i'
#define OP_ARG_I_LONG   "input"

#define OP_ARG_O        'o'
#define OP_ARG_O_LONG   "output"

#define OP_ARG_C        'c'
#define OP_ARG_C_LONG   "count"

#define OP_HLP          'h'
#define OP_HLP_LONG     "help"

#define DEFAULT_OPT_ARG_R  "UNO"
#define DEFAULT_OPT_ARG_S  "UNO"
#define DEFAULT_OPT_ARG_I  "UNO"
#define DEFAULT_OPT_ARG_O  "UNO"
#define DEFAULT_OPT_ARG_C  "UNO"

#define OPTION_STRING "r::s::i::o::c::h"

static struct option long_options[] = 
              {
              {OP_ARG_R_LONG, optional_argument, 0, (int) OP_ARG_R },
              {OP_ARG_S_LONG, optional_argument, 0, (int) OP_ARG_S },
              {OP_ARG_I_LONG, optional_argument, 0, (int) OP_ARG_I },
              {OP_ARG_O_LONG, optional_argument, 0, (int) OP_ARG_O },
              {OP_ARG_C_LONG, optional_argument, 0, (int) OP_ARG_C },
              {OP_HLP_LONG,   no_argument,       0, (int) OP_HLP },
              {0, 0, 0, 0}
              };

static void usage(char *argv[], int code)
{
 printf("usage: %s {--reverse|-r} <archivo> | [{--shuffle|-s} <archivo>] | [--input|-i] <archivo> | [--output|-o] <archivo> | [--count|-c] <archivo>\n",argv[0]);
 exit(code);
}

/**
 * Parse Common arguments
 */
static int parse_args(/*@ in @*/  int  argc, 
	 	      /*@ in @*/  char *argv[],
		      /*@ out @*/ char **arg_r,
		      /*@ out @*/ char **arg_s,
		      /*@ out @*/ char **arg_i,
		      /*@ out @*/ char **arg_o,
		      /*@ out @*/ char **arg_c,
						   int *op)
{
     int  res;
     int arg_r_count  = 0;
     int arg_s_count  = 0;
     int arg_i_count = 0;
     int arg_o_count = 0;
     int arg_c_count = 0;

     opterr = 0; // Supress getopt errors
     *arg_r      = DEFAULT_OPT_ARG_R; 
     *arg_s      = DEFAULT_OPT_ARG_S;
     *arg_i      = DEFAULT_OPT_ARG_I;
     *arg_o      = DEFAULT_OPT_ARG_O;
     *arg_c      = DEFAULT_OPT_ARG_C;
          
     while ( (res = getopt_long(argc, argv, OPTION_STRING, long_options, NULL)) != -1 )
     //while ( (res = getopt(argc, argv, OPTION_STRING)) != -1 )
     {
      if  (res == (int) OP_ARG_R)
	{
          // Take care, RO
	  *arg_r = optarg;
          arg_r_count++; 
	}
      else if  (res == (int) OP_ARG_S)
	{
	  *arg_s = optarg;
	  arg_s_count++;
	}
      else if  (res == (int) OP_ARG_I)
	{
	  *arg_i = optarg;
	  arg_i_count++;
	}
	  else if  (res == (int) OP_ARG_O)
	{
	  *arg_o = optarg;
	  arg_o_count++;
	}
	else if  (res == (int) OP_ARG_C)
	{
	  *arg_c = optarg;
	  arg_c_count++;
	}
      else if  (res == (int) OP_HLP)
	{
	  return (int) false;
	}
      else 
	{ 
          // Invalid Option, res ==  '?' 
	  return (int) false;
	}
     }
     
     if ((arg_r_count>1) || (arg_s_count>1) || (arg_i_count>1) || (arg_o_count>1) || (arg_c_count>1))
       {
	 return (int) false;	  
       }
       
     if ((arg_r_count==1) && (arg_s_count==1)){
		 *op=1;
		return (int) true;
	 }
		
	if ((arg_c_count==1) && ((arg_r_count==1) || (arg_s_count==1) || (arg_i_count==1) || (arg_o_count==1))){
		puts("Se ignoraran todos los argumentos que no sean -c");
		}
		
     return (int) ( (arg_r_count==1) || (arg_s_count==1) || (arg_i_count==1) || (arg_o_count==1) || (arg_c_count==1));
}

int main(int argc, char *argv[])
{
 char *arg_r;
 char *arg_s;
 char *arg_i;
 char *arg_o;
 char *arg_c;
 int op=0;

 if (!parse_args(argc, argv, &arg_r, &arg_s, &arg_i, &arg_o, &arg_c, &op))
  {
    usage(argv, EXIT_FAILURE);
  }
  switch(op){
	  case 1:
			puts("CASO 1");
			break;
	  case 2:
			
			break;
	  case 3:
			break;
	  }
 //printf("%s %s %s %s %s\n",arg_r, arg_s, arg_i, arg_o, arg_c);
 return (0);
}

