
/*
 * License:
 *
 * This file has been released under "unlicense" license
 * (https://unlicense.org).
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute
 * this software, either in source code form or as a compiled binary, for any
 * purpose, commercial or non-commercial, and by any means.
 *
 * For more information about this license, please visit - https://unlicense.org
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#include "str_split.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Change this value to process more characters.
#define MAX_STR_SIZE_ALLOWED 8192 // including null terminating character

#define MIN_STR_SIZE_ALLOWED 2 // including null terminating character

#define ARRAY_SIZE 256 // including null terminating character

static char *get_input_from_stdin_and_discard_extra_characters(char *str,
                                                               int size);
static void discard_all_characters_from_stdin(void);

int main(void)
{

    char str[ARRAY_SIZE] = {0};
    char delim[ARRAY_SIZE] = {0};
    long max_splits = 0;
    char **tokens_array = NULL;
    char *arg_str = NULL;
    char *arg_delim = NULL;

    while (1) {

        arg_str = str;
        arg_delim = delim;

        printf("\n");

        printf("Please input a string to split (max %d characters) (To enter"
               " NULL string, type NULL (in capital letters) and press ENTER):"
               " ", ARRAY_SIZE - 1);

        get_input_from_stdin_and_discard_extra_characters(str, ARRAY_SIZE);

        if (strncmp(str, "NULL", (strlen("NULL") + 1)) == 0) {
            arg_str = NULL;
        }

        printf("\nPlease input a delimiter for splitting the string (max %d"
               " characters) (To enter NULL delimiter, type NULL (in capital"
               " letters) and press ENTER): ", ARRAY_SIZE - 1);

        get_input_from_stdin_and_discard_extra_characters(delim, ARRAY_SIZE);

        if (strncmp(delim, "NULL", (strlen("NULL") + 1)) == 0) {
            arg_delim = NULL;
        }

        printf("\nPlease input maximum number of splits (a negative value means"
               " to split the string as many times as possible): ");

        scanf("%ld", &max_splits);

        // now clear the stdin input buffer
        discard_all_characters_from_stdin();

        printf("\n------\n");
        printf("Output\n");
        printf("------\n\n");
        printf("Input parameters: str=\"%s\", delim=\"%s\", max_splits=%ld\n\n",
               arg_str ? arg_str: "(null string)",
               arg_delim ? arg_delim: "(null delimiter)", max_splits);

        tokens_array = str_split(arg_str, arg_delim, max_splits);

        if (tokens_array == NULL) {
            printf("\n**Function str_split() returned NULL. The input string"
                   " was not split.**\n");
        }

        if (tokens_array) {
            printf("Number of tokens = %ld\n",
                   get_total_number_of_tokens_in_tokens_array(tokens_array));
            print_tokens_array(tokens_array);
            free_tokens_array(tokens_array);
        }

        printf("\nPlease press ENTER to continue..");

        // now clear the stdin input buffer
        discard_all_characters_from_stdin();

    } // end of while(1) loop

} // end of function main()

/*
 * static char *get_input_from_stdin_and_discard_extra_characters(char *str,
 *                                                                int size):
 *
 * Function get_input_from_stdin_and_discard_extra_characters() reads at most
 * (size - 1) characters from stdin and stores them in 'str'. One character is
 * used to null terminate 'str'. The rest of the remaining characters in stdin
 * are read and discarded, they are not stored in 'str'. So, when this function
 * returns then there is no input/characters left in stdin.
 *
 * If 'str' is NULL then it is an error and nothing is read from stdin and NULL
 * is returned.
 *
 * If 'size' is greater than 'MAX_STR_SIZE_ALLOWED' or less than
 * 'MIN_STR_SIZE_ALLOWED' then it is an error and nothing is read from stdin
 * and NULL is returned.
 */
static char *get_input_from_stdin_and_discard_extra_characters(char *str,
                                                               int size)
{

    int c = 0;
    int i = 0;

    if (str == NULL) {
        return NULL;
    }

    if ((size < MIN_STR_SIZE_ALLOWED) || (size > MAX_STR_SIZE_ALLOWED)) {
        return NULL;
    }

    for (i = 0; i < (size - 1); i = i + 1) {

        c = getchar();

        if ((c == '\n') || (c == EOF)) {
            str[i] = 0;
            return str;
        }

        str[i] = (char)(c);

    } // end of for loop

    str[i] = 0;

    // discard the rest of the input
    while ((c = getchar()) && (c != '\n') && (c != EOF));

    return str;

} // end of function get_input_from_stdin_and_discard_extra_characters()

static void discard_all_characters_from_stdin(void)
{

    int c = 0;

    // discard all characters from stdin
    while ((c = getchar()) && (c != '\n') && (c != EOF));

    return;

} // end of function discard_all_characters_from_stdin()

