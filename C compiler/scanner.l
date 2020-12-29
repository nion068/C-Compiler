%x COMMENT

%x SINGLE_COMMENT

%x STRINGS

%{
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include <iostream>
#include "SymbolInfo.h"
#include "SymbolTable.h"
#include "y.tab.h"

using namespace std;

extern YYSTYPE yylval;

int line_count=1;
int erro_count = 0;
int temp_line_no = 0;

void yyerror(char *);

char string_buf[9999];
char *string_ptr;

extern int bucket;

extern SymbolTable symbolTable;

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
CHAR [a-zA-Z0-9 ]
DIGIT [0-9]
DIGITS [0-9]+
NEWLINE \n

%%

{WHITESPACE} 	{	}

{NEWLINE} {line_count++;}

"if"	{
			return IF;
		}
		
"else"	{
			return ELSE;
		}

"for"	{
			return FOR;
		}

"while"	{
			return WHILE;
		}

"do"	{
			return DO;
		}

"break"	{
			return BREAK;
		}

"int"	{
			return INT;
		}

"char"	{
			return CHAR;
		}

"float"	{
			return FLOAT;
		}

"double" {
			return DOUBLE;
		}

"void"	{
			return VOID;
		}

"return"	{
			return RETURN;
		}

"switch"	{
			return SWITCH;
		}

"case"	{
			return CASE;
		}

"default"	{
			return DEFAULT;
		}

"continue"	{
			return CONTINUE;
		}

"println"	{
			return PRINTLN;
		}


"+"		|

"-"		{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ADDOP");
			yylval.info = s;
			return ADDOP;
		}

"*"		|

"/"		|

"%"		{

			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"MULOP");
			yylval.info = s;
			return MULOP;

		}

"++"	{
			return INCOP;
		}

"--"	{

			return DECOP;

		}

"<"		|

"<="	|

">"		|

">="	|

"=="	|

"!="	{

			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RELOP");
			yylval.info = s;
			return RELOP;

		}

"="		{

			return ASSIGNOP;

		}

"&&"	|

"||"	{

			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LOGICOP");
			yylval.info = s;
			return LOGICOP;

		}

"&"		|

"|"		|

"^"		|

"<<"	|

">>"	{

			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"BITOP");
			yylval.info = s;
			return BITOP;

		}

"!"		{

			return NOT;

		}

"("		{

			return LPAREN;

		}

")"		{

			return RPAREN;

		}

"{"		{

			return LCURL;

		}

"}"		{

			return RCURL;

		}

"["		{

			return LTHIRD;

		}																					
		
"]"		{

			return RTHIRD;

		}

","		{

			return COMMA;

		}

";"		{

			return SEMICOLON;

		}

[_a-zA-Z][_a-zA-Z0-9]*		{

			SymbolInfo* s =new  SymbolInfo(yytext, "ID");
			yylval.info= s;
			return ID;

		}						

{DIGIT}+ 	{
				SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_INT");
				yylval.info = s;
				return CONST_INT;
			}

{DIGIT}*\.{DIGIT}+(E[+-]?{DIGIT}+)?		{

			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_FLOAT");
			yylval.info = s;
			return CONST_FLOAT;

		}	
			

'[a-zA-Z0-9]'		{

			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
			yylval.info = s;
			return CONST_CHAR;

		}

'\\[tvaraf0bn]'		{

			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
			yylval.info = s;
			return CONST_CHAR;

		}

"/*"			{

			temp_line_no = line_count;

			string_ptr = string_buf;

			*string_ptr++ = '/';
			*string_ptr++ = '*';

			BEGIN(COMMENT);

		}

<COMMENT>[^*\n]*		{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

		}

<COMMENT>"*"+[^*/\n]*		{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

		}		

<COMMENT>"*"+"/"		{

				BEGIN(INITIAL);

				char *yptr = yytext;

				while(*yptr){

					*string_ptr++ = *yptr++;

				}
				
				*string_ptr = '\0';

		}

<COMMENT>\n 		{

			*string_ptr++ = '\n';
			line_count++;

		}

<COMMENT><<EOF>>		{

			erro_count++;
			return 0;
		}		

"//"			{
	
			string_ptr = string_buf;

			temp_line_no = line_count;
			
			*string_ptr++ = '/';
			*string_ptr++ = '/';

			BEGIN(SINGLE_COMMENT);

		}

<SINGLE_COMMENT>[^\\\n]+ 	{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

		}

<SINGLE_COMMENT>\\\n  	{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

			line_count++;

		}

<SINGLE_COMMENT>\n 			{

			BEGIN(INITIAL);

			*string_ptr++ = '\0';

			line_count++;


		}
	

<SINGLE_COMMENT><<EOF>>		{

		}								

\" 				{
	
			BEGIN(STRINGS);
			string_ptr = string_buf;

		}

<STRINGS>\"		{

			BEGIN(INITIAL);
			*string_ptr = '\0';
			return STRING;
		}

<STRINGS>\n		{

			*string_ptr = '\0';
			erro_count++;
			line_count++;
			BEGIN(INITIAL);

	}

<STRINGS>\\n 	{

		*string_ptr++ = '\n';

}

<STRINGS>\\t 	{

		*string_ptr++ = '\t';

}

<STRINGS>\\r 	{

		*string_ptr++ = '\r';

}

<STRINGS>\\b 	{

		*string_ptr++ = '\b';

}

<STRINGS>\\f 	{

		*string_ptr++ = '\f';

}

<STRINGS>\\(.|\n) 	{

		*string_ptr++ = yytext[1];

}					

<STRINGS>[^\\\n\"]+ 	{

		char *yptr = yytext;

		while(*yptr){

			*string_ptr++ = *yptr++;

		}


}

{DIGITS}*((\.)+{DIGITS}+)+(E(\.)*[+-]?(\.)*{DIGITS})?(\.)*{DIGITS}*		{

			erro_count++;

		}

{DIGITS}+(E(\.)*[+-]?(\.)*{DIGITS})?(\.)*{DIGITS}*		{

			erro_count++;

		}		

{DIGITS}{LETTER}+	|

{DIGITS}[_a-zA-Z]+{DIGIT}*	{

			erro_count++;

		}

'{CHAR}+{CHAR}+'			{

			erro_count++;

		}

'({CHAR}*)?	|

'\\'		{

			erro_count++;

		}

''			{

			erro_count++;

		}





%%

int yywrap(void)
{
	return 1;
}
