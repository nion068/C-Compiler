%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
//#include "symbol.h"
#include "SymbolInfo.h"
#include "SymbolTable.h"

//#define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
extern int yylineno;
extern char* yytext;

FILE *fp, *fp2, *fp3;

//SymbolTable *table;

string varType;
int errors = 0;

int bucket = 20;

SymbolTable symbolTable(bucket);

SymbolInfo code;


void yyerror(char *s)
{
	fprintf(fp2, "Error at line %d : %s\n\n", line_count, s);
}


%}

%union{
	SymbolInfo *info;
}

%token IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE  INCOP DECOP ASSIGNOP BITOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON MULTI_COMMENT SINGLE_COMMENT STRING PRINTLN

%token <info>ID 
%token <info>CONST_INT 
%token <info>CONST_FLOAT 
%token <info>CONST_CHAR 
%token <info>ADDOP
%token <info>MULOP
%token <info>LOGICOP
%token <info>RELOP

%type <info>type_specifier expression logic_expression rel_expression simple_expression term unary_expression factor variable var_declaration declaration_list

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%error-verbose


%%

start : program
	{
		//write your code in this block in all the similar blocks below
	}
	;

program : program unit 
		{
			fprintf(fp2,"At line no %d: program : program unit \n\n %s \n\n", line_count, yytext);
		}
	| unit
	{
		fprintf(fp2,"At line no %d: program : unit\n\n %s \n\n", line_count, yytext);
	}
	;
	
unit : var_declaration
	{
		fprintf(fp2,"At line no %d: unit : var_declaration \n\n %s \n\n", line_count, yytext);
	}
     | func_declaration
    {
		fprintf(fp2,"At line no %d: unit : func_declaration\n\n %s \n\n", line_count, yytext);
	}
     | func_definition
    {
		fprintf(fp2,"At line no %d: unit : func_definition\n\n %s \n\n", line_count, yytext);
	}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
				{
					fprintf(fp2,"At line no %d: func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON \n\n \n\n", line_count);

					SymbolInfo *t = symbolTable.lookUp($2->getName());
					if(t != NULL && (t->getType() == "FUNC_DEC" || t->getType() == "FUNC_DEF")) {
						fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, $2->getName().c_str());
						errors++;
					}
					else{
						symbolTable.insertinCurrentScope($2->getName(), "FUNC_DEC");
						SymbolInfo *temp = symbolTable.lookUp($2->getName());
						temp->setFuncRetType(varType);
					}

				}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			fprintf(fp2,"At line no %d: func_declaration :  type_specifier ID LPAREN RPAREN SEMICOLON\n\n \n\n", line_count);
			
			SymbolInfo *t = symbolTable.lookUp($2->getName());
			if(t != NULL && (t->getType() == "FUNC_DEC" || t->getType() == "FUNC_DEF")) {
				fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, $2->getName().c_str());
				errors++;
			}
			else{
				symbolTable.insertinCurrentScope($2->getName(), "FUNC_DEC");
				SymbolInfo *temp = symbolTable.lookUp($2->getName());
				temp->setFuncRetType(varType);
			}
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
				{
					fprintf(fp2,"At line no %d: func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n \n\n", line_count);
					SymbolInfo *t = symbolTable.lookUp($2->getName());
					if(t != NULL && t->getType() == "FUNC_DEF") {
						fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, $2->getName().c_str());
						errors++;
					}
					else if(t == NULL){
						symbolTable.insertinCurrentScope($2->getName(), "FUNC_DEF");
						SymbolInfo *temp = symbolTable.lookUp($2->getName());
						temp->setFuncRetType(varType);
					}
					
				}
		| type_specifier ID LPAREN RPAREN compound_statement
		{
			fprintf(fp2,"At line no %d: func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n \n\n", line_count);
			SymbolInfo *t = symbolTable.lookUp($2->getName());
			if(t != NULL && t->getType() == "FUNC_DEF") {
				fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, $2->getName().c_str());
				errors++;
			}
			else if(t == NULL){
				symbolTable.insertinCurrentScope($2->getName(), "FUNC_DEF");
				SymbolInfo *temp = symbolTable.lookUp($2->getName());
				temp->setFuncRetType(varType);
			}
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
				{
					fprintf(fp2,"At line no %d: parameter_list  : parameter_list COMMA type_specifier ID\n\n \n\n", line_count);
					//symbolTable.insertinCurrentScope($4->getName(), $4->getType());
				}
		| parameter_list COMMA type_specifier
		{
			fprintf(fp2,"At line no %d: parameter_list : parameter_list COMMA type_specifier\n\n %s \n\n", line_count);
		}
 		| type_specifier ID
 		{
			fprintf(fp2,"At line no %d: parameter_list : type_specifier ID\n\n \n\n", line_count);
			//symbolTable.insertinCurrentScope($2->getName(), $2->getType());
		}
		| type_specifier
		{
			fprintf(fp2,"At line no %d: parameter_list : type_specifier\n\n %s \n\n", line_count, yytext);
		}
 		;

 		
compound_statement : LCURL {symbolTable.enterScope();} statements RCURL
					{
						fprintf(fp2,"At line no %d: compound_statement : LCURL statements RCURL\n\n \n\n", line_count);
						symbolTable.printAll();
						symbolTable.exitScope();
					}
 		    | LCURL {symbolTable.enterScope();} RCURL
 		    {
				fprintf(fp2,"At line no %d: compound_statement : LCURL RCURL\n\n \n\n", line_count);
				symbolTable.printAll();
				symbolTable.exitScope();
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
				{
					fprintf(fp2,"At line no %d: var_declaration : type_specifier declaration_list SEMICOLON\n\n", line_count);

				}
 		 ;
 		 
type_specifier	: INT
				{
					fprintf(fp2,"At line no %d: type_specifier : INT\n\n", line_count);
					varType = "INT";
				}
 		| FLOAT
 		{
			fprintf(fp2,"At line no %d: type_specifier : FLOAT\n\n", line_count);
			varType = "FLOAT";
		}
 		| VOID
 		{
			fprintf(fp2,"At line no %d: type_specifier : VOID\n\n", line_count);
			varType = "VOID";
		}
 		;
 		
declaration_list : declaration_list COMMA ID
				{
					fprintf(fp2,"At line no %d: declaration_list : declaration_list COMMA ID\n\n", line_count);
					if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
					}
					else{
						SymbolInfo *t = symbolTable.lookUp($3->getName());
						if(t != NULL) {
							fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, $3->getName().c_str());
							errors++;
						}
						else{
							symbolTable.insertinCurrentScope($3->getName(), "VAR");
							SymbolInfo *temp = symbolTable.lookUp($3->getName());
							temp->setVarType(varType);
						}
					}
					
				}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
 		{
			fprintf(fp2,"At line no %d: declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n", line_count);
			if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
			}
			else{
				SymbolInfo *t = symbolTable.lookUp($3->getName());
				if(t != NULL && t->getType() == "ARRAY") {
					fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, $3->getName().c_str());
					errors++;
				}
				else{
					symbolTable.insertinCurrentScope($3->getName(), "ARRAY");
					SymbolInfo *temp = symbolTable.lookUp($3->getName());
					temp->setVarType(varType);
				}
			}
		}
 		  | ID
 		{
			fprintf(fp2,"At line no %d: declaration_list : ID\n\n", line_count);

			if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
			}
			else{
				SymbolInfo *t = symbolTable.lookUp($1->getName());
				if(t != NULL) {
					fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, $1->getName().c_str());
					errors++;
				}
				else{
					symbolTable.insertinCurrentScope($1->getName(), "VAR");
					SymbolInfo *temp = symbolTable.lookUp($1->getName());
					temp->setVarType(varType);
				}
			}
		}
 		  | ID LTHIRD CONST_INT RTHIRD
 		{
			fprintf(fp2,"At line no %d: declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n", line_count);
			if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
			}
			else{
				SymbolInfo *t = symbolTable.lookUp($1->getName());
				if(t != NULL && t->getType() == "ARRAY") {
					fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, $1->getName().c_str());
					errors++;
				}
				else{
					symbolTable.insertinCurrentScope($1->getName(), "ARRAY");
					SymbolInfo *temp = symbolTable.lookUp($1->getName());
					temp->setVarType(varType);
				}
			}
		}
 		  ;
 		  
statements : statement
			{
				fprintf(fp2,"At line no %d: statements : statement\n\n %s \n\n", line_count, yytext);
			}
	   | statements statement
	   	{
			fprintf(fp2,"At line no %d: statements : statements statement\n\n %s \n\n", line_count, yytext);
		}
	   ;
	   
statement : var_declaration
			{
				fprintf(fp2,"At line no %d: statement : var_declaration\n\n %s \n\n", line_count, yytext);
			}
	  | expression_statement
	  	{
			fprintf(fp2,"At line no %d: statement : expression_statement\n\n %s \n\n", line_count, yytext);
		}
	  | compound_statement
	  	{
			fprintf(fp2,"At line no %d: statement : compound_statement\n\n %s \n\n", line_count, yytext);
		}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  	{
			fprintf(fp2,"At line no %d: statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n %s \n\n", line_count, yytext);
		}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	  	{
			fprintf(fp2,"At line no %d: statement : IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE\n\n %s \n\n", line_count, yytext);
		}
	  | IF LPAREN expression RPAREN statement ELSE statement
	  	{
			fprintf(fp2,"At line no %d: statement : IF LPAREN expression RPAREN statement ELSE statement\n\n %s \n\n", line_count, yytext);
		}
	  | WHILE LPAREN expression RPAREN statement
	  	{
			fprintf(fp2,"At line no %d: statement : WHILE LPAREN expression RPAREN statement\n\n %s \n\n", line_count, yytext);
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  	{
			fprintf(fp2,"At line no %d: statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n %s \n\n", line_count, yytext);
		}
	  | RETURN expression SEMICOLON
	  	{
			fprintf(fp2,"At line no %d: statement : RETURN expression SEMICOLON\n\n %s \n\n", line_count, yytext);
		}
	  ;
	  
expression_statement 	: SEMICOLON
						{
							fprintf(fp2,"At line no %d: expression_statement 	: SEMICOLON\n\n %s \n\n", line_count, yytext);
						}			
			| expression SEMICOLON 
			{
				fprintf(fp2,"At line no %d: expression_statement 	: expression SEMICOLON\n\n", line_count);
			}
			;
	  
variable : ID
			{
				fprintf(fp2,"At line no %d: variable : ID\n\n", line_count);
				SymbolInfo *t = symbolTable.lookUp($1->getName());
				if(t == NULL) {
					fprintf(fp3,"Error at line no %d: Undeclared variable %s \n\n", line_count, $1->getName().c_str());
					errors++;
				}
				if(t!= NULL && t->getType() == "ARRAY"){
					fprintf(fp3,"Error at line no %d: Array without index \n\n", line_count);
					errors++;
				}
				$$ = t;
				
			} 		
	 | ID LTHIRD expression RTHIRD 
	{
		fprintf(fp2,"At line no %d: variable : ID LTHIRD expression RTHIRD\n\n %s \n\n", line_count, yytext);
		SymbolInfo *t = symbolTable.lookUp($1->getName());
		if(t == NULL) {
			fprintf(fp3,"Error at line no %d: Undeclared variable %s \n\n", line_count, $1->getName().c_str());
			errors++;
		}
		if(t!= NULL && t->getType() == "VAR"){
			fprintf(fp3,"Error at line no %d: Not an array \n\n", line_count);
			errors++;
		}
		if($3->getVarType() != "INT"){
			fprintf(fp3,"Error at line no %d: Non-integer Array Index\n\n", line_count);
			errors++;
		}
		$$ = t;
	}
	 ;
	 
 expression : logic_expression
 			{
				fprintf(fp2,"At line no %d: expression : logic_expression\n\n", line_count);
				$$ = $1;
			}	
	   | variable ASSIGNOP logic_expression
		{
			fprintf(fp2,"At line no %d: expression : variable ASSIGNOP logic_expression\n\n", line_count);
			if($1->getVarType() == "INT" && $3->getVarType() == "FLOAT"){
				fprintf(fp3,"Warning at line no %d: Assigning float type to integer\n\n", line_count);
				errors++;
			}
			if($1->getVarType() == "FLOAT" && $3->getVarType() == "INT"){
				fprintf(fp3,"Warning at line no %d: Assigning int type to float\n\n", line_count);
				errors++;
			}
			$$ = $1;
		}    	
	   ;
			
logic_expression : rel_expression 
				{
					fprintf(fp2,"At line no %d: logic_expression : rel_expression\n\n", line_count);
					$$ = $1;
				}	
		 | rel_expression LOGICOP rel_expression
		{
			fprintf(fp2,"At line no %d: logic_expression : rel_expression LOGICOP rel_expression\n\n", line_count);
			SymbolInfo *t = new SymbolInfo("INT", "VAR");
			t->setVarType("INT");
			if($1->getVarType() != $3->getVarType()){
				fprintf(fp3,"Error at line no %d: Type Mismatch\n\n", line_count);
				errors++;
			}
			$$ = t;

		} 	
		 ;
			
rel_expression	: simple_expression 
				{
					fprintf(fp2,"At line no %d: rel_expression	: simple_expression\n\n", line_count);
					$$ = $1;
				}
		| simple_expression RELOP simple_expression
		{
			fprintf(fp2,"At line no %d: rel_expression	: simple_expression RELOP simple_expression\n\n", line_count);
			SymbolInfo *t = new SymbolInfo("INT", "VAR");
			t->setVarType("INT");
			if($1->getVarType() != $3->getVarType()){
				fprintf(fp3,"Error at line no %d: Type Mismatch\n\n", line_count);
				errors++;
			}
			$$ = t;
		}
		;
				
simple_expression : term
					{
						fprintf(fp2,"At line no %d: simple_expression : term\n\n", line_count);
						$$ = $1;
					} 
		  | simple_expression ADDOP term
		{
			fprintf(fp2,"At line no %d: simple_expression : simple_expression ADDOP term\n\n", line_count);
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				SymbolInfo *t = new SymbolInfo($2->getName(), "VAR");
				t->setVarType("FLOAT");
				$$ = t;
			}
			else{
				SymbolInfo *t = new SymbolInfo($2->getName(), "VAR");
				t->setVarType("INT");
				$$ = t;
			}
		} 
		  ;
					
term :	unary_expression
		{
			fprintf(fp2,"At line no %d: term :	unary_expression\n\n", line_count);
			$$ = $1;
		}
     |  term MULOP unary_expression
    {
		fprintf(fp2,"At line no %d: term :	term MULOP unary_expression\n\n", line_count);
		if($2->getName() == "*"){
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				SymbolInfo *t = new SymbolInfo("FLOAT", "VAR");
				t->setVarType("FLOAT");
				$$ = t;
			}
		}
		else if($2->getName() == "/"){
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				SymbolInfo *t = new SymbolInfo("FLOAT", "VAR");
				t->setVarType("FLOAT");
				$$ = t;
			}
		}
		else if($2->getName() == "%"){
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				fprintf(fp3,"Error at line no %d: Integer operand on modulus operator\n\n", line_count, $1->getName().c_str());
				errors++;
			}
			SymbolInfo *t = new SymbolInfo("INT", "VAR");
			t->setVarType("INT");
			$$ = t;
		}
	}
     ;

unary_expression : ADDOP unary_expression
				{
					fprintf(fp2,"At line no %d: unary_expression : ADDOP unary_expression\n\n", line_count);
					$$ = $2;
				}  
		 | NOT unary_expression
		{
			fprintf(fp2,"At line no %d: unary_expression : NOT unary_expression\n\n", line_count);
			$$ = $2;
		} 
		 | factor
		{
			fprintf(fp2,"At line no %d: unary_expression : factor\n\n", line_count);
			$$ = $1;
		} 
		 ;
	
factor	: variable
		{
			fprintf(fp2,"At line no %d: factor : variable\n\n", line_count);
			$$ = $1;
		} 
	| ID LPAREN argument_list RPAREN
	{
			fprintf(fp2,"At line no %d: factor : ID LPAREN argument_list RPAREN\n\n %s \n\n", line_count, yytext);
			SymbolInfo *t = symbolTable.lookUp($1->getName());
			if(t == NULL) {
				fprintf(fp3,"Error at line no %d: Undeclared function %s \n\n", line_count, $1->getName().c_str());
				errors++;
			}
			else{
				if(t->getFuncRetType() == "VOID"){
					fprintf(fp3,"Error at line no %d: void function %s called as a part of expression\n\n", line_count, $1->getName().c_str());
					errors++;
				}
				else{
					$$ = t;
				}
			}

	}
	| LPAREN expression RPAREN
	{
			fprintf(fp2,"At line no %d: factor : LPAREN expression RPAREN\n\n", line_count);
			$$ = $2;
	}
	| CONST_INT
	{
			fprintf(fp2,"At line no %d: factor : CONST_INT\n\n", line_count);
			$1->setVarType("INT");
			$$ = $1;
	} 
	| CONST_FLOAT
	{
			fprintf(fp2,"At line no %d: factor : CONST_FLOAT\n\n", line_count);
			$1->setVarType("FLOAT");
			$$ = $1;
	}
	| variable INCOP
	{
			fprintf(fp2,"At line no %d: factor : variable INCOP\n\n", line_count);
			$$ = $1;
	} 
	| variable DECOP
	{
			fprintf(fp2,"At line no %d: factor : variable DECOP\n\n", line_count);
			$$ = $1;
	}
	;
	
argument_list : arguments
				{
					fprintf(fp2,"At line no %d: argument_list : arguments\n\n %s \n\n", line_count, yytext);
				}
			  |
			{
				fprintf(fp2,"At line no %d: argument_list : \n\n %s \n\n", line_count, yytext);
			}  
			  ;
	
arguments : arguments COMMA logic_expression
			{
				fprintf(fp2,"At line no %d: arguments : arguments COMMA logic_expression\n\n %s \n\n", line_count, yytext);
			}
	      | logic_expression
	    {
			fprintf(fp2,"At line no %d: arguments : logic_expression\n\n %s \n\n", line_count, yytext);
		}
	      ;
 

%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	fp2= fopen(argv[2],"w");
	fclose(fp2);
	fp3= fopen(argv[3],"w");
	fclose(fp3);
	
	fp2= fopen(argv[2],"a");
	fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	
	symbolTable.printAll();

	fprintf(fp2,"Total Lines : %d \n\n", line_count);
	fprintf(fp3,"Total Errors : %d \n\n", errors);

	fclose(fp2);
	fclose(fp3);
	
	return 0;
}

