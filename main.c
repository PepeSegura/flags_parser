
#include "flag_parser.h"

int main(int argc, char **argv)
{
	t_flag  flags[] = {
		{'v',	"verbose",	NO_ARG},
		{'o',	"output",	NEED_ARG},
		{'h',	"help",		NO_ARG},
		{0,		"version",	NO_ARG}
	};

	t_flag_parser flag_parser = parser_init(flags, FLAGS_COUNT(flags), argc, argv);
	parse(&flag_parser);

	print_parsed_flags(&flag_parser);
	cleanup_parser(&flag_parser);
	
	return 0;
}

