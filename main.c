
#include "flag_parser.h"

void print_flags(t_flag *flags, size_t flags_count)
{
    int i = 0;

    printf("--------PRINTING--------\n");
    while (i < flags_count)
    {
        print_flag(flags[i]);
        i++;
    }
}

// →

int is_short_name(size_t size, t_flag *flags, char c)
{
    int pos = 0;

    while (pos < size)
    {
        if (flags[pos].short_format && flags[pos].short_format[0] == c)
            return (pos);
        pos++;
    }
    return (-1);
}

void set_data(size_t size, t_flag *flags, char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == )
        /* code */
    }
    
    while (i < size)
    {
        if (flags[i].short_format && strcmp(flags[i].short_format, str) == 0)
            flags[i].found = true;
        else if (flags[i].long_format && strcmp(flags[i].long_format, str) == 0)
            flags[i].found = true;
        i++;
    }
}

int main(int argc, char **argv)
{

    t_flag allowed_flags[] = {
        {"l", "list", false,},
        {"a", "all", true,},
        {"h", "human", false,},
        {NULL}
    };


    print_flags(allowed_flags, 3);
    set_data(3, allowed_flags, "list");
    set_data(3, allowed_flags, "h");
    print_flags(allowed_flags, 3);
}

