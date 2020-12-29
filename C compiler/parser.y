%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include <algorithm>
#include <vector>
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

vector<string> vars;
vector<string> arrays;
vector<int> arraySize;

string varType;
int errors = 0;

int bucket = 20;

int labelCount=0;
int tempCount=0;

char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

SymbolTable symbolTable(bucket);

SymbolInfo code;

string println = "\n\nOUTDEC PROC\n PUSH AX\n PUSH BX\n PUSH CX\n PUSH DX\n OR AX, AX\n JGE _END_IF1\n PUSH AX\n MOV DL, '-'\n MOV AH, 2\n INT 21H\n POP AX\n NEG AX\n _END_IF1:\n XOR CX, CX\n MOV BX, 10D\n _REPEAT_1: \nXOR DX, DX\n DIV BX\n PUSH DX \n INC CX\n OR AX, AX\n JNE _REPEAT_1\n MOV AH, 2\n _PRINT_LOOP:\n POP DX \nOR DL, 30H\n INT 21H \nLOOP _PRINT_LOOP\n POP DX\n POP CX \nPOP BX \nPOP AX \nRET \nOUTDEC ENDP\n\n END MAIN";

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

%type <info>type_specifier expression logic_expression rel_expression simple_expression term unary_expression factor variable var_declaration declaration_list start program unit func_declaration func_definition compound_statement statements statement expression_statement SEMICOLON

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%error-verbose


%%

start : program
	{
		//write your code in this block in all the similar blocks below
		$1->code+= println;
		fprintf(fp2,".MODEL SMALL \n.STACK 100H \n.DATA\n");
		for(int i = 0; i<vars.size() ; i++){
			fprintf(fp2, "%s DW ?\n", vars[i].c_str());			
		}
		for(int i = 0 ; i< arrays.size() ; i++) {
			fprintf(fp2, "%s DW %d DUP(?)\n", arrays[i].c_str(), arraySize[i]);
		}
		fprintf(fp2, "\n.CODE\n");
		fprintf(fp2, "%s", $1->code.c_str());

	}
	;

program : program unit 
		{
			$$ = $1;
			$$->code += $2->code;
		}
	| unit
	{
		$$ = $1;
	}
	;
	
unit : var_declaration
	{
		$$ = $1;
	}
     | func_declaration
    {
		$$ = $1;
	}
     | func_definition
    {
		$$ = $1;
	}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
				{
					

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
					SymbolInfo *function = new SymbolInfo();
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

					$$ = function;
					$$->code += $2->getName() + " PROC \n";
					$$->code += $6->code;

					if($2->getName()=="main"){
						$$->code+="\tMOV AH,4CH\n\tINT 21H\n";
						$$->code+="main ENDP\n";
					}
					
				}
		| type_specifier ID LPAREN RPAREN compound_statement
		{	

			SymbolInfo *function = new SymbolInfo();
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

			$$ = function;
			$$->code += $2->getName() + " PROC \n";
			$$->code += $5->code;

			if($2->getName()=="main"){
				$$->code+="\tMOV AH,4CH\n\tINT 21H\n";
				$$->code+="main ENDP\n";
				//$$->code+="END main";
			}
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
				{
					
					//symbolTable.insertinCurrentScope($4->getName(), $4->getType());
				}
		| parameter_list COMMA type_specifier
		{
			
		}
 		| type_specifier ID
 		{
			
			//symbolTable.insertinCurrentScope($2->getName(), $2->getType());
		}
		| type_specifier
		{
			
		}
 		;

 		
compound_statement : LCURL {symbolTable.enterScope();} statements RCURL
					{
						
						symbolTable.exitScope();
						$$ = $3;
					}
 		    | LCURL {symbolTable.enterScope();} RCURL
 		    {
				
				symbolTable.exitScope();
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
				{
					

				}
 		 ;
 		 
type_specifier	: INT
				{
					SymbolInfo *s = new SymbolInfo("INT", "INT");
					varType = "INT";
					$$ = s;
					//$$->setVarType(varType);

				}
 		| FLOAT
 		{
			SymbolInfo *s = new SymbolInfo("FLOAT", "FLOAT");
			varType = "FLOAT";
			$$ = s;
		}
 		| VOID
 		{
			SymbolInfo *s = new SymbolInfo("VOID", "VOID");
			varType = "VOID";
			$$ =  s;
		}
 		;
 		
declaration_list : declaration_list COMMA ID
				{
					
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
							temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
							if(find(vars.begin(), vars.end(), temp->getASMvar()) == vars.end()){
								vars.push_back(temp->getASMvar());
							}

							
						}
					}
					
				}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
 		{
			
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
					temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
					int size = atoi(($5->getName().c_str()));
					temp->setArraySize(size);
				}
			}
		}
 		  | ID
 		{
			

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
					temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
					if(find(vars.begin(), vars.end(), temp->getASMvar()) == vars.end()){
						vars.push_back(temp->getASMvar());
					}
				}
			}
		}
 		  | ID LTHIRD CONST_INT RTHIRD
 		{
			
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
					temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
					int size = atoi(($3->getName().c_str()));
					cout << size << endl;
					temp->setArraySize(size);
				}
			}
		}
 		  ;
 		  
statements : statement
			{
				$$ = $1;
			}
	   | statements statement
	   	{
			$$ = $1;
			$$->code += $2->code;
			delete $2;
		}
	   ;
	   
statement : var_declaration
			{
				//fprintf(fp2,"At line no %d: statement : var_declaration\n\n", line_count);

			}
	  | expression_statement
	  	{
	  		//fprintf(fp2,"At line no %d: statement : expression_statement\n\n", line_count);

	  		$$ = $1;
		}
	  | compound_statement
	  	{
			//fprintf(fp2,"At line no %d: statement : compound_statement\n\n", line_count);

			$$ = $1;
		}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  	{
			//fprintf(fp2,"At line no %d: statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n", line_count);

			$$ = $3;
			char *label1 = newLabel();
			char *label2 = newLabel();
			$$->code += string(label1) + ":\n";
			$$->code+=$4->code;
			$$->code+="\tMOV AX , "+$4->getASMvar()+"\n";
			$$->code+="\tCMP AX , 0\n";
			$$->code+="\tJE "+string(label2)+"\n";
			$$->code+=$7->code;
			$$->code+=$5->code;
			$$->code+="\tJMP "+string(label1)+"\n";
			$$->code+=string(label2)+":\n";
		}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	  	{
			//fprintf(fp2,"At line no %d: statement : IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE\n\n", line_count);
			
			$$=$3;		
			char *label=newLabel();
			$$->code+="\tMOV AX, "+$3->getASMvar()+"\n";
			$$->code+="\tCMP AX, 0\n";
			$$->code+="\tJE "+string(label)+"\n";
			$$->code+=$5->code;
			$$->code+=string(label)+":\n";

		}
	  | IF LPAREN expression RPAREN statement ELSE statement
	  	{
			//fprintf(fp2,"At line no %d: statement : IF LPAREN expression RPAREN statement ELSE statement\n\n", line_count);
			$$ = $3;
			char *label1 = newLabel();
			char *label2 = newLabel();
			$$->code+="\tMOV AX, "+$3->getASMvar()+"\n";
			$$->code+="\tCMP AX, 0\n";
			$$->code+="\tJE "+string(label1)+"\n";
			$$->code+=$5->code;
			$$->code+="\tJMP " + string(label2) + "\n";
			$$->code+=string(label1)+":\n";
			$$->code+= $7->code;
			$$->code+=string(label2)+":\n";

		}
	  | WHILE LPAREN expression RPAREN statement
	  	{
			//fprintf(fp2,"At line no %d: statement : WHILE LPAREN expression RPAREN statement\n\n", line_count);
			//$$ = new SymbolInfo();
			char * label1 = newLabel();
			char * label2 = newLabel();
			$$->code = string(label1) + ":\n"; 
			$$->code+=$3->code;
			$$->code+="\tMOV AX , "+$3->getASMvar()+"\n";
			$$->code+="\tCMP AX , 0\n";
			$$->code+="\tJE "+string(label2)+"\n";
			$$->code+=$5->code;
			$$->code+="\tJMP "+string(label1)+"\n";
			$$->code+=string(label2)+":\n";

		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  	{
			SymbolInfo *t = symbolTable.lookUp($3->getName());
			if(t == NULL) cout << "null" << endl;
			$$ = t;
			$$ = new SymbolInfo();
			$$->code += "\tMOV AX, " + t->getASMvar() +"\n";
			$$->code += "\tCALL OUTDEC\n";
		}
	  | RETURN expression SEMICOLON
	  	{
			//yet to implement
		}
	  ;
	  
expression_statement 	: SEMICOLON
						{
							SymbolInfo *sem = new SymbolInfo();
							$$ = sem;
							$$->code = "";
						}			
			| expression SEMICOLON 
			{
				$$ = $1;
				//$$->code += $2->code;
			}
			;
	  
variable : ID
			{
				
				SymbolInfo *t = symbolTable.lookUp($1->getName());
				if(t == NULL) {
					fprintf(fp3,"Error at line no %d: Undeclared variable %s \n\n", line_count, $1->getName().c_str());
					errors++;
				}
				else if(t!= NULL && t->getType() == "ARRAY"){
					fprintf(fp3,"Error at line no %d: Array without index \n\n", line_count);
					errors++;
				}
				else{
					SymbolInfo *id = new SymbolInfo(t->getName(), t->getType());
					$$ = id;
					$$->setVarType(t->getVarType());
					$$->setASMvar(id->getASMvar()+to_string(symbolTable.idCount));
					if(find(vars.begin(), vars.end(), $$->getASMvar()) == vars.end()){
						vars.push_back($$->getASMvar());
					}
					//vars.push_back($$->getASMvar());
					//cout << $$->getVarType() << endl;
				}
				
			} 		
	 | ID LTHIRD expression RTHIRD 
	{
		
		SymbolInfo *t = symbolTable.lookUp($1->getName());
		if(t == NULL) {
			fprintf(fp3,"Error at line no %d: Undeclared variable %s \n\n", line_count, $1->getName().c_str());
			errors++;
		}
		else if(t!= NULL && t->getType() == "VAR"){
			fprintf(fp3,"Error at line no %d: Not an array \n\n", line_count);
			errors++;
		}
		else if($3->getVarType() != "INT"){
			fprintf(fp3,"Error at line no %d: Non-integer Array Index\n\n", line_count);
			errors++;
		}
		else{
			SymbolInfo *id = new SymbolInfo(t->getName(), t->getType());
			$$ = id;
			$$->setArraySize(t->getArraySize());
			$$->setASMvar(id->getASMvar() + to_string(symbolTable.idCount));
			cout << "line count " << line_count << " " << $$->getASMvar() << endl;
			if(find(arrays.begin(), arrays.end(), $$->getASMvar()) == arrays.end()){
				arrays.push_back($$->getASMvar());
				arraySize.push_back(t->getArraySize());
			}
			//arrays.push_back($$->getASMvar());
			//arraySize.push_back(t->getArraySize());
			$$->setVarType(t->getVarType());
			$$->code=$3->code ;
			$$->code += "\tMOV BX, " +$3->getASMvar() +"\n";
			//$$->code += "\tADD BX, BX\n";
					
			delete $3;
		}
		//$$->code += $3->code;
	}
	 ;
	 
 expression : logic_expression
 			{
				
				$$ = $1;
			}	
	   | variable ASSIGNOP logic_expression
		{
			//fprintf(fp2,"At line no %d: expression : variable ASSIGNOP logic_expression\n\n", line_count);
			
			if($1->getVarType() == "INT" && $3->getVarType() == "FLOAT"){
				fprintf(fp3,"Warning at line no %d: Assigning float type to integer\n\n", line_count);
				errors++;
			}
			if($1->getVarType() == "FLOAT" && $3->getVarType() == "INT"){
				fprintf(fp3,"Warning at line no %d: Assigning int type to float\n\n", line_count);
				errors++;
			}
			$$ = $1;
			$$->code=$3->code+$1->code;
			$$->code+="\tMOV AX, "+$3->getASMvar()+"\n";
			if($$->getType()=="ARRAY"){ 
				$$->code+= "\tMOV  "+$1->getASMvar()+"[BX], AX\n";
			}
				
			else{
				$$->code+= "\tMOV "+$1->getASMvar()+", AX\n";
			}
			delete $3;
		}    	
	   ;
			
logic_expression : rel_expression 
				{
					
					$$ = $1;
				}	
		 | rel_expression LOGICOP rel_expression
		{
			//fprintf(fp2,"At line no %d: logic_expression : rel_expression LOGICOP rel_expression\n\n", line_count);
			$$=$1;
			$$->code+=$3->code;
			char * label1 = newLabel();
			char * label2 = newLabel();
			char * t = newTemp();
			$$->setVarType("INT");
			if($1->getVarType() != $3->getVarType()){
				fprintf(fp3,"Error at line no %d: Type Mismatch\n\n", line_count);
				errors++;
			}
			else{
				if($2->getName() == "&&"){
					$$->code += "\tMOV AX , " + $1->getASMvar() +"\n";
					$$->code += "\tCMP AX , 0\n";
				 	$$->code += "\tJE " + string(label1) +"\n";
					$$->code += "\tMOV AX , " + $3->getASMvar() +"\n";
					$$->code += "\tCMP AX , 0\n";
					$$->code += "\tJE " + string(label1) +"\n";
					$$->code += "\tMOV " + string(t) + " , 1\n";
					$$->code += "\tJMP " + string(label2) + "\n";
					$$->code += string(label1) + ":\n" ;
					$$->code += "\tMOV " + string(t) + ", 0\n";
					$$->code += string(label2) + ":\n";
					$$->setASMvar(t);
					vars.push_back(t);
				}
				else if($2->getName()=="||"){
					$$->code += "\tMOV AX , " + $1->getASMvar() +"\n";
					$$->code += "\tCMP AX , 0\n";
				 	$$->code += "\tJNE " + string(label1) +"\n";
					$$->code += "\tMOV AX , " + $3->getASMvar() +"\n";
					$$->code += "\tCMP AX , 0\n";
					$$->code += "\tJNE " + string(label1) +"\n";
					$$->code += "\tMOV " + string(t) + " , 0\n";
					$$->code += "\tJMP " + string(label2) + "\n";
					$$->code += string(label1) + ":\n" ;
					$$->code += "\tMOV " + string(t) + ", 1\n";
					$$->code += string(label2) + ":\n";
					$$->setASMvar(t);
					vars.push_back(t);
				}
				delete $3;
			}
			

		} 	
		 ;
			
rel_expression	: simple_expression 
				{
					
					$$ = $1;
				}
		| simple_expression RELOP simple_expression
		{
			//fprintf(fp2,"At line no %d: rel_expression	: simple_expression RELOP simple_expression\n\n", line_count);
			$$=$1;
			$$->code+=$3->code;
			$$->code+="\tMOV AX, " + $1->getASMvar()+"\n";
			$$->code+="\tCMP AX, " + $3->getASMvar()+"\n";
			$$->setType("VAR");
			$$->setVarType("INT");
			if($1->getVarType() != $3->getVarType()){
				fprintf(fp3,"Error at line no %d: Type Mismatch\n\n", line_count);
				errors++;
			}
			else{
				char *t=newTemp();
				char *label1=newLabel();
				char *label2=newLabel();
				if($2->getName()=="<"){
					$$->code+="\tJL " + string(label1)+"\n";
				}
				else if($2->getName()=="<="){
					$$->code+="\tJLE " + string(label1)+"\n";
				}
				else if($2->getName()==">"){
					$$->code+="\tJG " + string(label1)+"\n";
				}
				else if($2->getName()==">="){
					$$->code+="\tJGE " + string(label1)+"\n";
				}
				else if($2->getName()=="=="){
					$$->code+="\tJE " + string(label1)+"\n";
				}
				else if($2->getName()=="!="){
					$$->code+="\tJNE " + string(label1)+"\n";
				}
				$$->code+="\tMOV "+string(t) +", 0\n";
				$$->code+="\tJMP "+string(label2) +"\n";
				$$->code+=string(label1)+":\n";
				$$->code+= "\tMOV "+string(t)+", 1\n";
				$$->code+=string(label2)+":\n";
				$$->setASMvar(t);
				vars.push_back(t);
				delete $3;
			}
		}
		;
				
simple_expression : term
					{
						
						$$ = $1;
					} 
		  | simple_expression ADDOP term
		{
			//fprintf(fp2,"At line no %d: simple_expression : simple_expression ADDOP term\n\n", line_count);
			
			$$=$1;
			$$->code+=$3->code;
			
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				$$->setType("VAR");
				$$->setVarType("FLOAT");
				if($2->getName()=="+"){
					char* t = newTemp();
					$$->code += "\tMOV AX, " + $1->getASMvar() + "\n";
					$$->code += "\tADD AX, " + $3->getASMvar() + "\n";
					$$->code += "\tMOV " + string(t) +" , AX\n";
					$$->setASMvar(string(t));
					vars.push_back(t);
				}
				else if($2->getName() == "-"){
					char* t = newTemp();
					$$->code += "\tMOV AX, " + $1->getASMvar() + "\n";
					$$->code += "\tSUB AX, " + $3->getASMvar() + "\n";
					$$->code += "\tMOV " + string(t) +" , AX\n";
					$$->setASMvar(string(t));
					vars.push_back(t);
				}
			}
			else{
				$$->setType("VAR");
				$$->setVarType("INT");
				if($2->getName()=="+"){
					char* t = newTemp();
					$$->code += "\tMOV AX, " + $1->getASMvar() + "\n";
					$$->code += "\tADD AX, " + $3->getASMvar() + "\n";
					$$->code += "\tMOV " + string(t) +" , AX\n";
					$$->setASMvar(string(t));
					vars.push_back(t);
				}
				else if($2->getName() == "-"){
					char* t = newTemp();
					$$->code += "\tMOV AX, " + $1->getASMvar() + "\n";
					$$->code += "\tSUB AX, " + $3->getASMvar() + "\n";
					$$->code += "\tMOV " + string(t) +" , AX\n";
					$$->setASMvar(string(t));
					vars.push_back(t);
				}
			}
			//$$->code += $1->code;
			delete $3;
		} 
		  ;
					
term :	unary_expression
		{
			
			$$ = $1;
		}
     |  term MULOP unary_expression
    {
		//fprintf(fp3,"At line no %d: term :	term MULOP unary_expression\n\n", line_count);
		
		$$=$1;
		$$->code += $3->code;
		$$->code += "\tMOV AX, "+ $1->getASMvar()+"\n";
		$$->code += "\tMOV BX, "+ $3->getASMvar() +"\n";
		
		char *t=newTemp();
		
		if($2->getName() == "*"){
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				$$->setVarType("FLOAT");
				$$->setType("VAR");
			}
			$$->code += "\tMUL BX\n";
			$$->code += "\tMOV "+ string(t) + ", AX\n";
			$$->setASMvar(string(t));
			vars.push_back(t);
		}
		else if($2->getName() == "/"){
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				$$->setVarType("FLOAT");
				$$->setType("VAR");
			}
			$$->code += "\tXOR DX , DX\n";
			$$->code += "\tDIV BX\n";
			$$->code += "\tMOV "+ string(t) + ", AX\n";
			$$->setASMvar(string(t));
			vars.push_back(t);
		}
		else if($2->getName() == "%"){
			if($1->getVarType() == "FLOAT" || $3->getVarType() == "FLOAT"){
				fprintf(fp3,"Error at line no %d: Integer operand on modulus operator\n\n", line_count, $1->getName().c_str());
				errors++;
			}
			$$->setVarType("FLOAT");
			$$->setType("VAR");
			$$->code += "\tXOR DX , DX\n";
			$$->code += "\tDIV BX\n";
			$$->code += "\tMOV "+ string(t) + ", AX\n";
			$$->setASMvar(string(t));
			vars.push_back(t);
		}
	}
     ;

unary_expression : ADDOP unary_expression
				{
					//fprintf(fp2,"At line no %d: unary_expression : ADDOP unary_expression\n\n", line_count);
					if($1->getName() == "+"){
						$$ = $2;
					}
					else if($1->getName() == "-"){
						$$ = $2;
						$$->code += "\tMOV AX, " + $2->getASMvar() + "\n";
						$$->code += "\tNEG AX\n";
						$$->code += "\tMOV " + $2->getASMvar() + " , AX\n";
					}
				}  
		 | NOT unary_expression
		{
			//fprintf(fp2,"At line no %d: unary_expression : NOT unary_expression\n\n", line_count);
			$$ = $2;
			char *t=newTemp();
			$$->code="\tMOV AX, " + $2->getASMvar() + "\n";
			$$->code+="\tNOT AX\n";
			$$->code+="\tMOV "+string(t)+", AX\n";
			$$->setASMvar(string(t));
			vars.push_back(t);
		} 
		 | factor
		{
			
			$$ = $1;
		} 
		 ;
	
factor	: variable
		{
			//fprintf(fp2,"At line no %d: factor : variable\n\n", line_count);
			$$ = $1;
			if($1->getType() == "ARRAY"){
				char *t = newTemp();
				$$->code+="\tMOV AX, " + $1->getASMvar() + "[BX]\n";
				$$->code+= "\tMOV " + string(t) + ", AX\n";
				$$->setASMvar(string(t));
				vars.push_back(t);
			}
			else{

			}
		} 
	| ID LPAREN argument_list RPAREN
	{
			
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
			
			//fprintf(fp2,"At line no %d: factor : LPAREN expression RPAREN\n\n", line_count);
			$$ = $2;
	}
	| CONST_INT
	{
			
			$1->setVarType("INT");
			$$ = $1;
	} 
	| CONST_FLOAT
	{
			
			$1->setVarType("FLOAT");
			$$ = $1;
	}
	| variable INCOP
	{
			
			$$ = $1;
			$$->code += "\tMOV AX, " + $$->getASMvar()+ "\n";
			$$->code += "\tINC AX\n";
			$$->code += "\tMOV " + $$->getASMvar() + ", AX\n";
	} 
	| variable DECOP
	{
			
			$$ = $1;
			$$->code += "\tMOV AX, " + $$->getASMvar()+ "\n";
			$$->code += "\tDEC AX\n";
			$$->code += "\tMOV " + $$->getASMvar() + ", AX\n"; 
	}
	;
	
argument_list : arguments
				{
					
				}
			  |
			{
				
			}  
			  ;
	
arguments : arguments COMMA logic_expression
			{
				
			}
	      | logic_expression
	    {
			
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
	
	//symbolTable.printAll();

	fprintf(fp3,"Total Lines : %d \n\n", line_count);
	fprintf(fp3,"Total Errors : %d \n\n", errors);

	fclose(fp2);
	fclose(fp3);
	
	return 0;
}

