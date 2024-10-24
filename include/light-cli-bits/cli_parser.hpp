#pragma once

#include <vector>
#include <string>

namespace lcli
{
    class cli_parser
    {
    public: // Public types
        struct argument
        {
            enum type : unsigned char
            {
                hard_argument, // A hard argument is an argument that cannot be passed to an option
                soft_argument, // A soft argument is an argument that can be passed to an option
                short_option_string, // A short option string is a string of short options that is passed with a single dash
                long_option, // A long option is an option that is passed with a double dash
                passed_long_option_value // A passed long option value is an option value that was passed to a long option
            };
            type argument_type;
            std::string_view argument_value;

            inline operator std::string_view() const { return argument_value; }
        };
    private: // Private types
        typedef std::vector<argument> argument_list_t;
    public: // Public types
        typedef argument_list_t::size_type size_type;

        typedef argument_list_t::iterator iterator;
        typedef argument_list_t::const_iterator const_iterator;
    private: // Private members
        argument_list_t arguments;
    public: // Public Constructors
        inline cli_parser() = default;
        inline cli_parser(const std::vector<std::string>& raw_argument_list);
        inline cli_parser(const cli_parser &) = default;
        inline cli_parser(cli_parser &&) = default;
        inline cli_parser &operator=(const cli_parser &) = default;
        inline cli_parser &operator=(cli_parser &&) = default;
        inline ~cli_parser() = default;
    public: // Public functions
        /**
         * @brief The parse function
         * 
         * This function will parse the raw argument list and populate the argument list with the parsed arguments according to the following rules:
         * 
         * - "--loption" -> {long_option, "loption"}
         * 
         * - "--loption=value" -> {long_option, "loption"}, {passed_long_option_value, "value"}
         * 
         * - "-soption" -> {short_option_string, "soption"}
         * 
         * - "argument" -> {soft_argument, "argument"}
         * 
         * - "--" : all subsequent "argument"s -> {hard_argument, "argument"}
         * @param raw_argument_list The raw argument list to parse
         */
        inline void parse(const std::vector<std::string>& raw_argument_list);

        // Argument list accessors
        inline argument_list_t &argument_list() { return arguments; }
        inline const argument_list_t &argument_list() const { return arguments; }

        // Argument list iterators
        inline iterator begin() { return arguments.begin(); }
        inline iterator end() { return arguments.end(); }
        inline const_iterator begin() const { return arguments.begin(); }
        inline const_iterator end() const { return arguments.end(); }

        // Argument list size
        inline size_type size() const { return arguments.size(); }

        // Argument list empty
        inline bool isempty() const { return arguments.empty(); }

        // Argument list clear
        inline void clear() { arguments.clear(); }
    };
} // namespace largs