# PSU_2018_nmobjdump
Second year project in C in which the goal is to re-code "nm" and "objdump -f -s" Unix System call. The project involves reading into symboles, tracing functions as well as applying ELF format.
The programs works on relocatable files ".o" & ".a", shared files ".so" and executable files.

EXEMPLE :

> ./my_nm print_ascii.o

> ./my_objdump my_nm
