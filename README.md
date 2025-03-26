# C Flags Parser Library

A lightweight command-line flag parser for C projects that supports both short and long flags with arguments.

## Features

- **Short flags**: `-v`, `-o=value`, `-ovalue`, `-o value`
- **Long flags**: `--verbose`, `--output=value`, `--output value`
- **Argument support**: Flags can be marked as requiring arguments
- **Error handling**: Automatic validation for missing arguments
- **Flexible syntax**: Supports both `-f=value`, `-fvalue` and `-f value` styles
- **Repeated same flag with arguments**: `-f value1 -f value1 --format value2`
- **Store Non flags or args in `parser->extra_args`**
```bash
$ ./parser extra -v -h -o outfile --output=outfile2 extra2 --verbose

Flags found:
  -v, --verbose
  -o, --output (args:  'outfile' 'outfile2' )
  -h, --help
Extra params: ( 'extra' 'extra2' )
```
## Basic Usage

### 1. Define Flags

Create an array of `t_flag` structures:

```c
t_flag flags[] = {
    // Format: {short_name, long_name, argument_requirement}
    {'v', "verbose", NO_ARG},   // No argument
    {'o', "output",  NEED_ARG}, // Requires argument
    {'h', "help",    NO_ARG},
    {0,   "version", NO_ARG}    // Long-only flag
};
```

### 2. Initialize Parser
```c
t_flag_parser flag_parser = parser_init(flags, FLAGS_COUNT(flags), argc, argv);
```

### 3. Parse Arguments
```c
parse(&flag_parser);
```

### 4. Print Results
```c
print_parsed_flags(&flag_parser);
```

### 5. Cleanup Parser
```c
cleanup_parser(&flag_parser);
```

## Error Handling
The parser automatically checks for:
- Unknown flags
- Missing required arguments

```bash
$ ./program -x
Unknown flag: -x

$ ./program --output
Error: Flag --output requires an argument
```

## Compilation
```bash
make && gcc -Wall -Wextra -Werror main.c flag_parser.a -o your_program
```

## Command-line Syntax

| Example           | Description                                |
| :---------------- | :------                                    |
| -v                |  Short flag without argument               |
| --verbose         |  Long flag without argument                |
| -o file.tx        |  Short flag with separate argument         |
| -o=file.txt       |  Short flag with attached argument         |
| -ofile.txt        |  Short flag with attached argument         |
| --output file.txt |  Long flag with separate argument          |
| --output=file.txt |  Long flag with attached argument          |
| -vh               |  Combined short flags (no args)            |
| -vo file.txt      |  Combined short flags (with separated arg) |
| -vo=file.txt      |  Combined short flags (with attached arg)  |
| -vofile.txt       |  Combined short flags (with attached arg)  |
