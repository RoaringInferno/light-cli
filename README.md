# light-cli
Easy, simple, working CLI parser. Uses the following standard for parsing arguments:

- `--loption` -> `{long_option, "loption"}`
- `--loption=value` -> `{long_option, "loption"}`, `{passed_long_option_value, "value"}`
- `-soption` -> `{short_option_string, "soption"}`
- `argument` -> `{soft_argument, "argument"}`
- `--` -> all subsequent `argument`s -> `{hard_argument, "argument"}`s

Argument types are an enum defined in the `lcli::cli_parser::argument` and `lcli::cli_parser::argument::type` namespaces, with the latter being more stable.

Iterators are supported, and thus so are range-based for loops. Element access must be done through the `lcli::cli_parser::argument_list()` method, though it is not recommended.

All methods are marked as inline. This is due to their brevity. The parse function is marked as inline due to the likeliness of it only being called once.