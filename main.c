#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct
{
	double *numbs;
	char *op; // TODO: makei t dynamic
	int op_count;
}ARG;

ARG parse_arg(int argc, char **argv)
{
	ARG arg = {0};
	int i = 1;
	assert(argc > 3);
	assert(argc % 2 == 0);
	
	arg.numbs = (double*)malloc(sizeof(double) * (argc/2));
	arg.op = (char*)malloc(sizeof(double) * (argc/2-1));
	
	assert(arg.numbs);
	assert(arg.op);
	
	for(i = 1; i < argc; i++)
	{
		if(i % 2 == 1) // number
		{
			arg.numbs[(i-1)/2] = atof(argv[i]);
		}
		else // operator
		{
			arg.op[(i-2)/2] = argv[i][0]; /* +, -, x, /, ^,  */
			arg.op_count++;
		}
	}
	return arg;
}

double do_math(ARG arg)
{
	double result = arg.numbs[0];
	for(int i = 0; i < arg.op_count; i++)
	{
		switch(arg.op[i])
		{
			case 'x':
				arg.numbs[i] *= arg.numbs[i+1];
				arg.op[i] = '+'; /* + 0 */
				arg.numbs[i+1] = 0.0;
			break;
			case '/':
				arg.numbs[i] /= arg.numbs[i+1];
				arg.op[i] = '+'; /* + 0 */
				arg.numbs[i+1] = 0.0;
			break;
		}
	}
	for(int i = 0; i < arg.op_count; i++)
	{
		switch(arg.op[i])
		{
			case '+':
				result += arg.numbs[i+1];
			break;
			case '-':
				result -= arg.numbs[i+1];
			break;
		}
	}
	return result;
}

int main(int argc, char **argv)
{
	ARG arg = parse_arg(argc, argv);
	printf("%lg\n", do_math(arg));
	free(arg.numbs);
	free(arg.op);
	return 0;
}
