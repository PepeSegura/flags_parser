#ifndef FLAG_PARSER_H
# define FLAG_PARSER_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_flag
{
    char        short_format;
    char        *long_format;
    bool        accept_arg;

    bool        found;
    char        *arg;
}   t_flag;


void    print_flag(t_flag flag);

#endif