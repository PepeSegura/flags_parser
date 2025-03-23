#include "flag_parser.h"

void    print_flag(t_flag flag)
{
    printf("Short:       %s\n", flag.short_format);
    printf("Long:        %s\n", flag.long_format);
    printf("Accepts_arg: %d\n", flag.accept_arg);

    printf("Found:       %d\n", flag.found);
    printf("Arg:         %s\n", flag.arg);
    printf("-------\n");
}
