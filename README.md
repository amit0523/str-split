
File str_split.c implements a function called str_split() which splits a string
into an array of string tokens based on a string delimiter. The signature of
this function is:
        
        char **str_split(const char *str, const char *delim, long max_splits)

Function str_split() splits a string ('str') into an array of string tokens (a
token is also a string). This function uses the 'delim' string to split 'str'
into tokens. If a 'delim' is found at position "i", then the token ends at the
position "i - 1".

'max_splits' argument is used to control hwo many times 'str' should be split.
For example, if 'max_splits' is 1, then 'str' will be split one time only. So,
if 'str' is "a;b;c" and 'delim' is ";" and 'max_splits' is 1 then 'str' will be
split one time only and two tokens will be generated - "a" and "b;c".

If 'max_splits' is zero (0) then an array of tokens is returned whose first
token (at index 0) is a copy of 'str' and the second token (at index 1) is NULL.

If 'max_splits' is negative then it means that all tokens should be returned.

In some (error/invalid, etc.) cases NULL is returned. If NULL is returned then
this means that 'str' was not split and nothing was done. The cases where NULL
will be returned are listed below:

     ** 'str' is NULL.
     ** 'str' is an empty string.
     ** 'str' size (including null terminating character) is greater than
         'MAX_STR_SIZE_ALLOWED'.
     ** 'delim' is NULL.
     ** 'delim' is an empty string.
     ** 'delim' size (including null terminating character) is greater than
         'MAX_STR_SIZE_ALLOWED'.

In successful cases, the return value of this function is a pointer to an array
of string tokens. This array of tokens is terminated by a NULL token.

The psuedocode of looping through this array of tokens is:

         long i = 0;
         while (tokens_array[i]) {
             ..do stuff here..
             i = i + 1;
         }

All these tokens had been allocated using calloc(), so when these tokens are no
longer needed then the user should free these tokens by calling the function
'free_tokens_array()'.

If 'delim' is not found in 'str' then an array of tokens is returned whose
first token (at index 0) is a copy of 'str' and the second token (at index 1) is
NULL.

Sometimes, depending on 'str' and 'delim', it is quite possible that in the
returned array of tokens, some tokens are empty tokens (means that the first
character of the token is a null character). For example, if there are two
consecutive 'delim', then one empty token will be generated.

This function returns empty tokens because some users may want them. One use
case is the following - if the user is splitting records from a file to insert
in a database, then when an empty token is found, then the user can insert NULL
or 0, etc. in that column.

In case, empty tokens are of no use then they can be skipped by using the
following line of code: "if ((tokens_array[i])[0] == '\0') { continue; }".

There are two more functions available that you can use: print_tokens_array()
and get_total_number_of_tokens_in_tokens_array().

---- End of README ----
