#ifndef FLAG_PARSER_H
# define FLAG_PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define NEED_ARG 1
# define NO_ARG 0

typedef struct
{
	char		short_name;	// Short flag (e.g., 'v' for -v)
	const char	*long_name;	// Long flag (e.g., "verbose" for --verbose)
	int			has_arg;	// 1 if the flag expects an argument (e.g., -o file/-ofile/-o=file)

	char		*arg_value;	// Argument value (if provided)
	int			present;	// 1 if the flag is in the command line
}	t_flag;

typedef struct
{
	t_flag	*flags; // Array of Flag definitions
	int		count;  // Number of flags in the array
	int		argc;   // Original argc
	char	**argv; // Original argv
	int		pos;    // Current position in argv (during parsing)
}	t_flag_parser;

# define FLAGS_COUNT(flags) sizeof(flags) / sizeof(t_flag)

t_flag_parser	parser_init(t_flag *flags, int count, int argc, char **argv);
void			parse(t_flag_parser *parser);
void			print_parsed_flags(t_flag_parser *parser);
void			cleanup_parser(t_flag_parser *parser);

#endif
