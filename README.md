# MakeGen
Makefile generator written in shitty C++


# Usage: PATH, NAME, CC, FLAGS


Path: The path where you want to put your Makefile (generally inside a project folder)

Name: The name of your program / library

Cc: The compiler you want to use (gcc, g++ or ar rcs (yes ar rcs is not a compiler))

Flags: -Wall -Wextra -Werror maybe?


# What it will do:

-Generate a Makefile inside the project folder

-Put the 42/101 Header at the top

-Automatically add $(SRCS)(.c | .cpp) and $(HEADERS)(.h) found inside the project ROOT

-Automatically add rules: all, $(NAME), clean, fclean, re and "normy", which will run the "Norminette" with arguments $(SRCS) & $(HEADERS)


# What it won't do (for now):

-Adapt to "./src" "./obj" "./include" kind of project organization

-Norme the $(SRCS) | $(HEADERS) lines to avoid going beyond 80 charaters on one line

-Manage .hpp for C++ (Because I prefer .h)

-Linking additionnal libraries / frameworks


At least you have a basic Makefile and you can tweak it by hand
