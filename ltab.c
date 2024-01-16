#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

bool check_number (char* nstr) {
    int it = 0;
    bool isNumber = true;

    while (nstr[it] != '\0') {
        if (nstr[it] < 48 || nstr[it] > 57) {
            isNumber = false;
            break;
        }
        it++;
    }

    return isNumber;
}

bool contains_number (int* arr, int n) {
    bool contained = false;
    int it = 0;

    while (arr[it] != 0) {
        if (arr[it] == n) {
            contained = true;
            break;
        }
        it++;
    }

    return contained;
}


size_t power(size_t base, size_t exp) {
    size_t res = 1;

    for (size_t i=0; i<exp; i++) {
        res *= base;
    }

    return res;
}


void printArr(int** arr, int size, char op, int xs, int xe, int ys, int ye) {

    int n_length = (int) log10(size-1)+1;

    // Printing spaces before numbering
    for (int i=0; i<n_length-1; i++)
        printf(" ");

    // Printing operator
    if (op == 'm')
        printf("* | ");
    else if (op == 'a')
        printf("+ | ");
    else if (op == 'p')
        printf("^ | ");

    // Printing horizontal numbering
    for (int a=xs; a<=xe; a++)
        printf("%*d ", n_length, a);
    printf("\n");

    // Printing horizontal border
    for (int a=xs; a<=xe+1; a++)
        for (int b=0; b<=n_length; b++)
            printf("-");
    printf("-");

    printf("\n");

    for (int a=ys; a<=ye; a++) {
        printf("%*d | ", n_length, a); // Vertical numbering

        for (int b=xs; b<=xe; b++) {

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

    struct args {
        int divisor;
        char op;
        int xs;
        int xe;
        int ys;
        int ye;
    };

    struct args params;

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-xs") == 0) {
            if (check_number(argv[i+1]))
                params.xs = atoi(argv[++i]);
            else {
                fprintf(stderr, "\033[31mError: Invalid or missing number after\033[0m -xs\n");
                return 1;
            }
        }

        else if (strcmp(argv[i], "-xe") == 0) {
            if (check_number(argv[i+1]))
                params.xe = atoi(argv[++i]);
            else {
                fprintf(stderr, "\033[31mError: Invalid or missing number after\033[0m -xe\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-ys") == 0) {
            if (check_number(argv[i+1]))
                params.ys = atoi(argv[++i]);
            else {
                fprintf(stderr, "\033[31mError: Invalid or missing number after\033[0m -ys\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-ye") == 0) {
            if (check_number(argv[i+1]))
                params.ye = atoi(argv[++i]);
            else {
                fprintf(stderr, "\033[31mError: Invalid or missing number after\033[0m -ye\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "m") == 0)
            params.op = 'm';
        else if (strcmp(argv[i], "a") == 0)
            params.op = 'a';
        else if (strcmp(argv[i], "p") == 0)
            params.op = 'p';
        else if (check_number(argv[i]))
            params.divisor = atoi(argv[i]);
        else {
            fprintf(stderr, "\033[31mError: Invalid argument\033[0m %s\n", argv[i]);
            return 1;
        }
    }




    if (params.divisor > 0) {
        if (params.xe == 0)
            params.xe = params.divisor-1;
        if (params.ye == 0)
            params.ye = params.divisor-1;
        if (params.op != 'p' && params.op != 'm' && params.op != 'a') {
            fprintf(stderr, "\033[31mError: Operator missing\033[0m - Valid Operators: m (multiplication), a (addition), p (potentiate)\n");
            return 1;
        }
    }

    else {
        fprintf(stderr, "\033[31mError: Missing divisor\033[0m\n");
        return 1;
    }


    if (params.xs < 0 || params.xs >= params.divisor) {
        fprintf(stderr, "\033[31mError:\033[0m -xs: \033[31mNumber out of range!\033[0m\nEnter a number between 0 and divisor-1\n");
        return 1;
    }
    if (params.xe < 0 || params.xe >= params.divisor) {
        fprintf(stderr, "\033[31mError:\033[0m -xe: \033[31mNumber out of range!\033[0m\nEnter a number between 0 and divisor-1\n");
        return 1;
    }
    if (params.ys < 0 || params.ys >= params.divisor) {
        fprintf(stderr, "\033[31mError:\033[0m -ys: \033[31mNumber out of range!\033[0m\nEnter a number between 0 and divisor-1\n");
        return 1;
    }
    if (params.ye < 0 || params.ye >= params.divisor) {
        fprintf(stderr, "\033[31mError:\033[0m -ye: \033[31mNumber out of range!\033[0m\nEnter a number between 0 and divisor-1\n");
        return 1;
    }

    if (params.op == 'p' && params.divisor > 16) {
        fprintf(stderr, "\033[31mError: Overflow\033[0m - Enter a number between 0 and 16\n");
        return 1;
    }


    // Allocating memory for linking table
    int** table = (int**)malloc(params.divisor*sizeof(int*));
    for (int a=0; a<params.divisor; a++)
        table[a] = (int*)malloc(params.divisor*sizeof(int));

    for (int a=0; a<params.divisor; a++) {
        for (int b=0; b<params.divisor; b++) {
            switch (params.op) {
                case 'm':
                    table[a][b] = (a*b) % params.divisor;
                    break;
                case 'a':
                    table[a][b] = (a+b) % params.divisor;
                    break;
                case 'p':
                    table[a][b] = (int)(power(a, b) % params.divisor);
            }
        }
    }

    int zero_dividers[params.divisor-1];
    int units[params.divisor-1];

    int zd_it = 0;
    int units_it = 0;

    for (int i=0; i<params.divisor-1; i++) {
        zero_dividers[i] = 0;
        units[i] = 0;
    }


    for (int a=1; a<params.divisor; a++) {
        for (int b=1; b<params.divisor; b++) {
            switch (table[a][b]) {
                case 0:
                    if (!contains_number(zero_dividers, a)) {
                        zero_dividers[zd_it++] = a;
                    }
                    break;
                case 1:
                    if (!contains_number(units, a)) {
                        units[units_it++] = a;
                    }
                    break;
            }
        }
    }


    printArr(table, params.divisor, params.op, params.xs, params.xe, params.ys, params.ye);


    printf("\n");

    zd_it = 0;
    units_it = 0;

    printf("Zero dividers:  ");

    while (zero_dividers[zd_it+1] != 0 && abs(zero_dividers[zd_it+1]) < params.divisor) {
        if (zero_dividers[zd_it] < params.divisor)
            printf("%d, ", zero_dividers[zd_it]);
        zd_it++;
    }


    if (zero_dividers[zd_it] != 0 && abs(zero_dividers[zd_it]) < params.divisor)
        printf("%d", zero_dividers[zd_it]);

    printf("\nUnits:          ");

    while (units[units_it+1] != 0 && abs(units[units_it+1]) < params.divisor) {
        if (units[units_it] < params.divisor)
            printf("%d, ", units[units_it]);
        units_it++;
    }


    if (units[units_it] != 0 && abs(units[units_it]) < params.divisor)
        printf("%d", units[units_it]);

    printf("\n", units[units_it]);


    if (zero_dividers[0] == 0)
        printf("Is integrity ring\n\n");


    if (params.op == 'p') {
        int nilpotent[params.divisor-1];
        int np_it = 0;

        for (int a=1; a<params.divisor; a++) {
            for (int b=1; b<params.divisor; b++) {
                if (table[a][b] == 0 && !contains_number(nilpotent, a)) {
                    nilpotent[np_it++] = a;
                }
            }
        }

        np_it = 0;

        printf("Nilpotent:      ");


        while (nilpotent[np_it+1] != 0 && abs(nilpotent[np_it+1]) < params.divisor) {
            if (nilpotent[np_it] < params.divisor)
                printf("%d, ", nilpotent[np_it]);
            np_it++;
        }


        if (nilpotent[np_it] != 0 && abs(nilpotent[np_it]) < params.divisor)
            printf("%d", nilpotent[np_it]);

        printf("\n");

    }


    // Freeing linking table
    for (int i=0; i<n; i++)
        free(table[i]);
    free(table);

    return 0;

}
