#include <stdio.h>                      /* printf */
#include <stdlib.h>                     /* exit */
#include <getopt.h>                     /* getopt */
#include <stdbool.h>                    /* Booleans */

extern char *optarg;
extern int  opterr;
//extern int optind, opterr, optopt;

#define OP_ARG_A        'a'
#define OP_ARG_A_LONG   "arga"

#define OP_ARG_B        'b'
#define OP_ARG_B_LONG   "argb"

#define OP_ARG_C        'c'
#define OP_ARG_C_LONG   "flagc"

#define OP_HLP          'h'
#define OP_HLP_LONG     "help"

#define DEFAULT_OPT_ARG_A  "UNO"
#define DEFAULT_OPT_ARG_B  (65536)
#define DEFAULT_OPT_ARG_C  (false)
#define MAX_B              (65535)
#define MIN_B              (0)

#define OPTION_STRING "a:b:ch"

static struct option long_options[] = 
              {
              {OP_ARG_A_LONG, required_argument, 0, (int) OP_ARG_A },
              {OP_ARG_B_LONG, required_argument, 0, (int) OP_ARG_B },
              {OP_ARG_C_LONG, no_argument,       0, (int) OP_ARG_C },
              {OP_HLP_LONG,   no_argument,       0, (int) OP_HLP },
              {0, 0, 0, 0}
              };

static void usage(char *argv[], int code)
{
 printf("usage: %s {--argb|-b} <0..65535> [{--arga|-a} <string>] [--flagc|-c]\n",argv[0]);
 exit(code);
}

/**
 * Parse Common arguments
 */
static int parse_args(/*@ in @*/  int  argc, 
	 	      /*@ in @*/  char *argv[],
		      /*@ out @*/ char **arg_a,
		      /*@ out @*/ int  *arg_b,
		      /*@ out @*/ bool *flag_c)
{
     int  res;
     int arg_a_count  = 0;
     int arg_b_count  = 0;
     int flag_c_count = 0;

     opterr = 0; // Supress getopt errors
     *arg_a      = DEFAULT_OPT_ARG_A; 
     *arg_b      = DEFAULT_OPT_ARG_B;
     *flag_c     = DEFAULT_OPT_ARG_C;
          
     while ( (res = getopt_long(argc, argv, OPTION_STRING, long_options, NULL)) != -1 )
     //while ( (res = getopt(argc, argv, OPTION_STRING)) != -1 )
     {
      if  (res == (int) OP_ARG_A)
	{
          // Take care, RO
          printf("ENTRE %d",res);
	  *arg_a = optarg;
          arg_a_count++; 
	}
      else if  (res == (int) OP_ARG_B)
	{
	  *arg_b = atoi(optarg);
	  arg_b_count++;
	}
      else if  (res == (int) OP_ARG_C)
	{
	  *flag_c = true;
          flag_c_count++;
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
     if ((arg_a_count>1) || (arg_b_count>1) || (flag_c_count>1))
       {
	 return (int) false;	  
       }
     return (int) ( (*arg_a != NULL) && (*arg_b > MIN_B) && (*arg_b < MAX_B) );
     //return (int) ( (*arg_a != NULL));
}

int main(int argc, char *argv[])
{
 char *arg_a;
 int  arg_b;
 bool flag_c;

 if (!parse_args(argc, argv, &arg_a, &arg_b, &flag_c))
  {
    usage(argv, EXIT_FAILURE);
  }
 printf("%s %d (%d)\n",arg_a, arg_b, flag_c);
 return (0);
}

