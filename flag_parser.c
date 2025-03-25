#include "flag_parser.h"

t_flag_parser   parser_init(t_flag *flags, int count, int argc, char **argv)
{
	return (t_flag_parser){
		.flags = flags,
		.count = count,
		.argc = argc,
		.argv = argv,
		.pos = 1,
	};
}

t_flag* match_short_flag(t_flag_parser *parser, char c)
{
	for (int i = 0; i < parser->count; i++)
	{
		if (parser->flags[i].short_name == c)
			return (&parser->flags[i]);
	}
	return (NULL);
}

t_flag* match_long_flag(t_flag_parser *parser, const char *name)
{
	char *equal_pos = strchr(name, '=');
	char *arg = NULL;
	if (equal_pos)
	{
		arg = equal_pos + 1;
		equal_pos[0] = '\0';
	}
	for (int i = 0; i < parser->count; i++)
	{
		if (strcmp(parser->flags[i].long_name, name) == 0)
		{
			if (arg)
				parser->flags[i].arg_value = arg;
			return (&parser->flags[i]);
		}
	}
	return (NULL);
}

int    parse_flag_arg(t_flag_parser *parser, t_flag *flag)
{
	// if (flag->has_arg == NO_ARG || flag->arg_value)
	// 	return (0);
	if (flag->has_arg == NO_ARG)
		return (0);

	char *arg = strchr(parser->argv[parser->pos], '=');
	if (arg)
	{
		flag->arg_value = arg + 1;
		return (1);
	}
	if (parser->pos + 1 >= parser->argc || parser->argv[parser->pos + 1][0] == '-')
	{
		if (flag->long_name)
			dprintf(2, "Error: Flag --%s requires an argument.\n", flag->long_name);
		if (flag->short_name)
			dprintf(2, "Error: Flag -%c requires an argument.\n", flag->short_name);
		exit(EXIT_FAILURE);
	}
	parser->pos++;
	flag->arg_value = parser->argv[parser->pos];
	return (1);
}

void    parse(t_flag_parser *parser)
{
	while (parser->pos < parser->argc)
	{
		char *arg = parser->argv[parser->pos];
		if (strncmp(arg, "--", 2) == 0)
		{
			char *name = arg + 2;
			t_flag *flag = match_long_flag(parser, name);
			if (!flag)
			{
				dprintf(2, "Unknown flag: %s\n", arg);
				exit(EXIT_FAILURE);
			}
			flag->present = 1;
			parse_flag_arg(parser, flag);
		}
		else if (arg[0] == '-')
		{
			char *short_flags = arg + 1;
			for (int i = 0; short_flags[i] != '\0'; i++)
			{
				t_flag *flag = match_short_flag(parser, short_flags[i]);
				if (!flag)
				{
					dprintf(2, "Unknown flag: -%c\n", short_flags[i]);
					exit(EXIT_FAILURE);
				}
				flag->present = 1;
				if (flag->has_arg == NEED_ARG)
				{
					if (short_flags[i + 1] != '\0')
					{
						if (short_flags[i + 1] == '=')
							i++;
						flag->arg_value = &short_flags[i + 1];
						break;
					}
					else
					{
						if (parser->pos + 1 >= parser->argc || parser->argv[parser->pos + 1][0] == '-')
						{
							dprintf(2, "Error: Flag -%c requires an argument.\n", flag->short_name);
							exit(EXIT_FAILURE);
						}
						parser->pos++;
						flag->arg_value = parser->argv[parser->pos];
					}
					break;
				}
			}
		}
		parser->pos++;
	}
}

void print_parsed_flags(t_flag_parser *parser)
{
	printf("Flags found:\n");
	for (int i = 0; i < parser->count; i++)
	{
		t_flag *flag = &parser->flags[i];
		if (flag->present)
		{
			printf("  ");
			if (flag->short_name)
				printf("-%c", flag->short_name);
			if (flag->short_name && flag->long_name)
				printf(", ");
			if (flag->long_name)
				printf("--%s", flag->long_name);
			
			if (flag->has_arg && flag->arg_value)
			{
				printf(" (args: '%s'", flag->arg_value);
			}
			printf("\n");
		}
	}
}
