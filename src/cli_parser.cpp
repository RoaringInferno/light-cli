#include "cli_parser.hpp"

lcli::cli_parser::cli_parser(const std::vector<std::string> &raw_argument_list)
{
    parse(raw_argument_list);
}

void lcli::cli_parser::parse(const std::vector<std::string> &raw_argument_list)
{
    // Pre-allocating the minimum amount of memory, saving time in the hot loop
    //  Could be made more efficient by calculating the exact amount of arguments (making an initial pass over the raw argument list)
    //  While the argument list is small, the performance gain is negligible
    arguments.reserve(raw_argument_list.size());

    // Force all arguments to be hard arguments, short-circuiting the option parsing
    // This flag is switched to true when the "--" argument is found
    bool force_hard_argument = false;

    for (const std::string& raw_argument : raw_argument_list)
    {
        if (force_hard_argument) // Short-circuit the option parsing if the "--" argument was found
        {
            arguments.push_back({argument::type::hard_argument, raw_argument});
            continue;
        }

        const std::string::size_type size = raw_argument.size(); // Cache the size of the argument

        if (size == 0) // Skip empty arguments
        {
            continue;
        }

        if (size == 1) // Skip single character arguments
        {
            arguments.push_back({argument::type::hard_argument, raw_argument});
            continue;
        }

        std::string::size_type index = 0; // Create an iterator to traverse the argument


        if (raw_argument[index] == '-') // Check if the argument is an option
        {
            // No need to check for "-", as it is handled by the single character check
            index++; // Next character

            if (raw_argument[index] == '-') // Check if the argument is a long option
            {
                if (size == 2)
                {
                    force_hard_argument = true;
                    continue;
                }

                index++; // Skip the second dash
                while (index < size && raw_argument[index] != '=') // Traverse the option name
                {
                    index++;
                }

                arguments.push_back({argument::type::long_option, std::string_view(&raw_argument[2], index - 2)}); // Push the long option name
                if (index == size) // No value was explicitly passed to the long option
                {
                    continue;
                }

                index++; // Skip the "=" character
                arguments.push_back({argument::type::passed_long_option_value, std::string_view(&raw_argument[index], size - index)}); // Push the value passed to the long option
                continue;
            }

            arguments.push_back({argument::type::short_option_string, std::string_view(&raw_argument[index], size - 1)});
            continue;
        }

        arguments.push_back({argument::type::soft_argument, raw_argument}); // Push the argument as a soft argument (can be used by a preceeding option)
    }
}