#include <iostream>

#include "light-cli"

std::string get_argument_type_name(const lcli::cli_parser::argument::type &type);
std::string get_print_string(const lcli::cli_parser::argument &argument);

int main(int argc, char *argv[])
{
    lcli::cli_parser parser(argc, argv);
    for (const lcli::cli_parser::argument &argument : parser)
    {
        std::cout << get_print_string(argument) << "\n";
    }
    return 0;
}

std::string get_argument_type_name(const lcli::cli_parser::argument::type &type)
{
    switch (type)
    {
    case lcli::cli_parser::argument::hard_argument:
        return "hard_argument";
    case lcli::cli_parser::argument::soft_argument:
        return "soft_argument";
    case lcli::cli_parser::argument::short_option_string:
        return "short_option_string";
    case lcli::cli_parser::argument::long_option:
        return "long_option";
    case lcli::cli_parser::argument::passed_long_option_value:
        return "passed_long_option_value";
    default:
        return "unknown";
    }
}

std::string get_print_string(const lcli::cli_parser::argument &argument)
{
    return "{" + get_argument_type_name(argument.argument_type) + ": " + std::string(argument) + "}";
}