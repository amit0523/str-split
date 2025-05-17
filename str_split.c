
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

static void free_all_allocated_memory(char **tokens_array, long n);

char **str_split(const char *str, const char *delim, long max_splits)
{

    char **output_tokens_array = NULL;
    char *temp = NULL;
    char *prev_temp = NULL;
    long num_tokens = 0;
    size_t delim_len = 0;
    size_t len = 0;
    long i = 0;

    if ((str == NULL) || (str[0] == '\0') ||
        (delim == NULL) || (delim[0] == '\0')) {
        return NULL;
    }

    if (strnlen(str, MAX_STR_SIZE_ALLOWED) == MAX_STR_SIZE_ALLOWED) {
        return NULL;
    }

    if (strnlen(delim, MAX_STR_SIZE_ALLOWED) == MAX_STR_SIZE_ALLOWED) {
        return NULL;
    }

    // At this point, it is guaranteed that both 'str' and 'delim' are null
    // terminated. If either or both of them were not null terminated then
    // strnlen() above would have returned 'MAX_STR_SIZE_ALLOWED' and this
    // function would have returned from there.
    //
    // So, from here onwards, using all string functions is safe.
 
    // Handle the cases where either 'max_splits' is 0 or 'delim' does not occur
    // in 'str'.
    if ((max_splits == 0) || (strstr(str, delim) == NULL)) {

        output_tokens_array = calloc(2, (sizeof(*output_tokens_array)));

        if (output_tokens_array == NULL) {
            return NULL;
        }

        len = strlen(str);

        // allocate 1 extra byte for null terminator
        output_tokens_array[0] = calloc(1, (len + 1));

        if (output_tokens_array[0] == NULL) {
            free(output_tokens_array);
            return NULL;
        }

        memmove(output_tokens_array[0], str, len);
        (output_tokens_array[0])[len] = '\0';

        output_tokens_array[1] = NULL;

        return output_tokens_array;

    }

    delim_len = strlen(delim);

    temp = (char *)(str);
    prev_temp = (char *)(str);

    while (1) {

        temp = strstr(temp, delim);

        num_tokens = num_tokens + 1;

        if (temp == NULL) {
            break;
        }

        temp = temp + delim_len;
        prev_temp = temp;

    } // end of while (1) loop

    if ((max_splits > 0) && (max_splits < num_tokens)) {
        num_tokens = max_splits + 1;
    }

    // allocate 1 extra character pointer to terminate output_tokens_array with
    // a NULL pointer.
    output_tokens_array = calloc((size_t)(num_tokens) + 1,
                                  (sizeof(*output_tokens_array)));

    if (output_tokens_array == NULL) {
        return NULL;
    }

    temp = (char *)(str);
    prev_temp = (char *)(str);
    i = 0;

    while (1) {

        temp = strstr(temp, delim);

        len = (size_t)(temp - prev_temp);

        // allocate 1 extra byte for null terminator
        output_tokens_array[i] = calloc(1, (len + 1));

        if (output_tokens_array[i] == NULL) {
            free_all_allocated_memory(output_tokens_array, i);
            return NULL;
        }

        memmove(output_tokens_array[i], prev_temp, len);
        (output_tokens_array[i])[len] = '\0';

        i = i + 1;

        temp = temp + delim_len;
        prev_temp = temp;

        if ((num_tokens - i) == 1) { // last token

            len = (size_t)(str + strlen(str) - prev_temp);

            // allocate 1 extra byte for null terminator
            output_tokens_array[i] = calloc(1, (len + 1));

            if (output_tokens_array[i] == NULL) {
                free_all_allocated_memory(output_tokens_array, i);
                return NULL;
            }

            memmove(output_tokens_array[i], prev_temp, len);
            (output_tokens_array[i])[len] = '\0';

            i = i + 1;

            break;

        } // end of if ((num_tokens - i) == 1)

    } // end of while (1) loop

    output_tokens_array[i] = NULL;

    return output_tokens_array;

} // end of function str_split()

void print_tokens_array(char **tokens_array)
{

    long i = 0;

    printf("\n");

    if (tokens_array == NULL) {
        printf("Error: Argument 'tokens_array' is NULL.\n\n");
        return;
    }

    printf("Tokens are printed below (within single quotes):\n\n");
    printf("---- Start of Tokens ----\n");

    while (tokens_array[i]) {
        printf("'%s'\n", tokens_array[i]);
        i = i + 1;
    }

    printf("---- End of Tokens ----\n\n");

    return;

} // end of function print_tokens_array()

long get_total_number_of_tokens_in_tokens_array(char **tokens_array)
{

    long i = 0;

    if (tokens_array == NULL) {
        return 0;
    }

    while (tokens_array[i]) {
        i = i + 1;
    }

    return i;

} // end of function get_total_number_of_tokens_in_tokens_array()

void free_tokens_array(char **tokens_array)
{

    long i = 0;

    if (tokens_array == NULL) {
        return;
    }

    while (tokens_array[i]) {
        free(tokens_array[i]);
        i = i + 1;
    }

    free(tokens_array);

    return;

} // end of function free_tokens_array()

/*
 * static void free_all_allocated_memory(char **tokens_array, long n):
 *
 * Function free_all_allocated_memory() frees the tokens in the array of
 * tokens ('tokens_array') from index '0' to 'n - 1'. It also frees
 * 'tokens_array'.
 */
static void free_all_allocated_memory(char **tokens_array, long n)
{

    long i = 0;

    if (tokens_array == NULL) {
        return;
    }

    for (i = 0; i < n; i = i + 1) {
        free(tokens_array[i]);
    }

    free(tokens_array);

    return;

} // end of function free_all_allocated_memory()

