#ifndef DATA2INT_H
#define DATA2INT_H
#include <stdio.h>


void read_data(FILE *file, int **tables, int noof_rows, int noof_attr);
void print_table(int **tables, int noofrows, int noofattrs);

#endif // DATA2INT_H
