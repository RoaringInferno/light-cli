#include <iostream>

#include "light-cli"

std::string get_argument_type_name(const lcli::cli_parser::argument_t::type &type);
std::string get_print_string(const lcli::cli_parser::argument_t &argument);

int main(int argc, char *argv[])
{
    std::vector<std::string> raw_argument_list(argc - 1);
    for (int i = 1; i < argc; i++)
    {
        raw_argument_list[i] = argv[i];
    }
    lcli::cli_parser parser(raw_argument_list);
    for (const lcli::cli_parser::argument_t &argument : parser)
    {
        std::cout << get_print_string(argument) << "\n";
    }
    return 0;
}

std::string get_argument_type_name(const lcli::cli_parser::argument_t::type &type)
{
    switch (type)
    {
    case lcli::cli_parser::argument_t::hard_argument:
        return "hard_argument";
    case lcli::cli_parser::argument_t::soft_argument:
        return "soft_argument";
    case lcli::cli_parser::argument_t::short_option_string:
        return "short_option_string";
    case lcli::cli_parser::argument_t::long_option:
        return "long_option";
    case lcli::cli_parser::argument_t::passed_long_option_value:
        return "passed_long_option_value";
    default:
        return "unknown";
    }
}

std::string get_print_string(const lcli::cli_parser::argument_t &argument)
{
    return "{" + get_argument_type_name(argument.argument_type) + ": " + std::string(argument) + "}";
}