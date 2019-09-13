/*
-------------------------------------------
Student: Mohit Mamtani <mamtani@sheridan.desire2learn.com>
StudentID: 991472469
-------------------------------------------
 */

/* 
 * File:   main.c
 * Author: Mohit Mamtani <mamtani@sheridan.desire2learn.com>
 *
 * Created on October 14, 2018, 4:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int MAX_SIZE = 100;
typedef unsigned int uint;

FILE *fp;
char internal[255];

// This function will be used to swap "pointers".
void swap(char**, char**);

// Bubble sort function here.
void bubbleSort(char**, uint);

// Read quotes from quotes.txt file file and add them to array. Adjust the size as well!
// Note: size should reflect the number of quotes in the array/quotes.txt file!
void read_in(char**, uint*);

// Print the quotes using array of pointers.
void print_out(char**, uint);

// Save the sorted quotes in the output.txt file
void write_out(char**, uint);

// Free memory!
void free_memory(char**, uint);

int main() {

    // Create array of pointers. Each pointer should point to heap memory where
    // each quote is kept. I.e. arr[0] points to quote N1 saved on the heap.
    char *arr[MAX_SIZE];

    // Number of quotes in the file quotes.txt. Must be adjusted when the file is read!
    uint size = MAX_SIZE;

    read_in(arr, &size);

    printf("--- Input:\n");
    print_out(arr, size);

    bubbleSort(arr, size);

    printf("--- Output:\n");
    print_out(arr, size);
    write_out(arr, size);

    free_memory(arr, size);

    return (0);
}


// Basic Function of Swapping pointers

void swap(char** ptr1, char** ptr2) {
    char *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void bubbleSort(char** arr, uint size) {
    uint i, j, k = 0;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1; j++) {
            if (strlen(arr[j]) >= strlen(arr[j + 1])) {
                if (strlen(arr[j]) >= strlen(arr[j + 1])) {
                    while (arr[j][k] == arr[j + 1][k]) {
                        k++;
                    }
                    if (arr[j][k] > arr[j + 1][k]) {
                        swap(&arr[j], &arr[j + 1]);
                    } else {
                        swap(&arr[j], &arr[j + 1]);
                    }
                }
            }
        }
    }
}

void read_in(char** arr, uint* size) {
    uint p = 0;
    if ((fp = fopen("quotes.txt", "r")) == NULL) {
        perror("open() for quotes.txt");
        exit(1);
    }
    while (fgets(internal, 255, (FILE*) fp) && p != *size) {
        internal[strcspn(internal, "\n")] = 0;
        if (internal[1] != 0) {
            arr[p] = (char *) calloc(255, sizeof(internal));
            if (arr[p] == NULL) {
                printf("Cannot allocate memory for %u-th quote!\n", p + 1);
                exit(1);
            }
            strcpy(arr[p], internal);
            p++;
        }
    }
    fclose(fp);
}

void print_out(char** arr, uint size) {
    for (uint a = 0; a < size; a++)
        if ((arr[a] != 0))
            printf("%s\n", arr[a]);
        else
            break;
}

void write_out(char** arr, uint size) {
    fp = fopen("output.txt", "w");
    for (uint i = 0; i < size; i++) {
        fprintf(fp, "%s\n", arr[i]);
    }
    fclose(fp);
}

void free_memory(char** arr, uint size) {
    for (uint i = 0; i < size; i++)
        free(arr[i]);
}