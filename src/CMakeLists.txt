add_executable(myapp main.c myapp.c filter.c facul.c)

target_compile_options(myapp PRIVATE -Wall -Wextra -Werror)
