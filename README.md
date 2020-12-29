# C Compiler

In this project, we have implemented a subset of C compiler.

First, we have implemented a symbol table. A symbol-table is a data structure maintained by compilers in order to store information about the occurrence of various entities such as identifiers, objects, function names etc. Information of different entities may include type, value, scope etc. At the starting phase of constructing a compiler, we constructed a symbol-table which maintains a list of hash tables where each hash table contains information of symbols encountered in a scope of the source program.

Second, we constructed a lexical analyzer. Lexical analysis is the process of scanning the source program as a sequence of characters and converting them into sequence of tokens. A program that performs this task is called a lexical analyzer or a lexer or a scanner. For example if a portion of source program contains int x=5; the scanner would convert in a sequence of tokens like <INT><ID,x><ASSIGNOP,=><COST_NUM,5><SEMICOLON>. After completing the construction of a simple symbol table, we constructed a scanner for a subset of C language. The task was performed using a tool named flex (Fast Lexical Analyzer Generator) which is a popular tool for generating scanners.

Thrid, we constructed the last part of the front end of a compiler for a subset of C language. That means we performed syntax analysis and semantic analysis with a grammar rule containing function implementation in this assignment. To do so, we built a parser with the help of Lex (Flex) and YACC (Bison).

Finally,  we generated intermediate code for a source program having no error. That means if the source code does not contain any error, that was to be detected in the previous steps, we generated intermediate code for the source code. We have picked 8086 assembly language as our intermediate representation.
