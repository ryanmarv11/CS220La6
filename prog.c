#include <stdio.h>

void bad()
{
	char *new_name = "Quick brown fox jumped over the lazy dog";
	unsigned char *temp;
	unsigned long offset_name = 0x28;
	unsigned long offset_age = 0x30;
	*((char **) (temp + offset_name)) = new_name;
	*((int *) (temp + offset_age)) = 1000;
	unsigned long ret_orig = 0x000055555555476a;
	unsigned long ret_new =  0x0000555555554785;
	unsigned long ret_offset = ret_orig - ret_new;
	unsigned long addr_ret_orig = 0x7fffffffdf90;
	unsigned long stack_offset_ret_addr = addr_ret_orig - ret_orig;
	temp = (unsigned char *) (&new_name);
	*((unsigned long *) (temp + stack_offset_ret_addr)) += ret_offset;
}

int main()
{
	struct
	{
		char * name;
		int age;
	} student = {.name = "John", .age = 22};
	bad();
	printf("student.name = %s\nstudent.age = %d\n", student.name, student.age);
	return 0;
}