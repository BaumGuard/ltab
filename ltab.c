#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void printArr(int** arr, int size, char op) {

    int n_length = (int) log10(size-1)+1;

    // Printing spaces before numbering
    for (int i=0; i<n_length-1; i++)
        printf(" ");
    printf("%c | ", op); // Printing operator

    // Printing horizontal numbering
    for (int a=0; a<size; a++)
        printf("%*d ", n_length, a);
    printf("\n");

    // Printing horizontal border
    for (int a=0; a<=size; a++)
        for (int b=0; b<=n_length; b++)
            printf("-");
    printf("-");

    printf("\n");

    for (int a=0; a<size; a++) {
        printf("%*d | ", n_length, a); // Vertical numbering

        for (int b=0; b<size; b++) {

            if (arr[a][b]==0 && a!=0 && b!=0) // If number is 0 (zero divisor)
                printf("\033[34m%*d\033[0m ", n_length, arr[a][b]);
            else if (arr[a][b]==1) // If number is 1 (unit)
                printf("\033[32m%*d\033[0m ", n_length, arr[a][b]);
            else
                printf("%*d ", n_length, arr[a][b]);

        }

        printf("\n");
    }
}

int main (int argc, char** argv) {

    int n = (int) atoi(argv[1]); // Modulo divisor

    // Allocating memory for linking table
    int** table = (int**)malloc(n*sizeof(int*));
    for (int a=0; a<n; a++)
        table[a] = (int*)malloc(n*sizeof(int));

    for (int a=0; a<n; a++) {
        for (int b=0; b<n; b++) {
			if (argc > 2) {
            	if (argv[2][0] == 'm') // If operator is *
                	table[a][b] = (a*b) % n;
            	else if (argv[2][0] == 'p') // If operator is +
                	table[a][b] = (a+b) % n;
            	else {
                	fprintf(stderr, "%c : Invalid operator (Valid operators: +, *)\n", argv[2][0]);
                	return 1;
            	}
			}
			else {
				fprintf(stderr, "No arguments entered\n");
				return 1;
			}
        }
    }

	if (argv[2][0] == 'm')
    	printArr(table, n, '*');
	else
		printArr(table, n, '+');

    // Freeing linking table
    for (int i=0; i<n; i++)
        free(table[i]);
    free(table);

    return 0;

}
