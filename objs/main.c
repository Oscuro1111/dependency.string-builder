#include<stdio.h>
#include "../includes/string_builder.h"


int main(int argc,char **argv){

	String *str  = allocate_string(0);

	insert_string(&str,"OK this is string");
	fprintf(stderr,"%s\n%d\n%d\n",str->str,str->length,str->current);
	
	return 0;
}
