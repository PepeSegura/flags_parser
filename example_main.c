
#include "flag_parser.h"

int main(int argc, char **argv)
{
	t_flag  flags[] = {
		INIT_FLAG('v', "verbose",  NO_ARG),
		INIT_FLAG('o', "output",   NEED_ARG),
		INIT_FLAG('h', "help",     NO_ARG),
		INIT_FLAG(0,   "version",  NO_ARG),
	};

	t_flag_parser flag_parser = parser_init(flags, FLAGS_COUNT(flags), argc, argv);
	parse(&flag_parser);

	print_parsed_flags(&flag_parser);

	cleanup_parser(&flag_parser);
	return 0;
}

