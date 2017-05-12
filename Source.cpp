#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<cstring>

void G();
void E();
void R();
void T();
void S();
void F();
void D();
char lex();

using namespace std;
string unconsumed_input();

fstream scanner("filename.txt");
bool error = false;
char next_token = '%';
string lexy = "";

int main()
{
	printf("Reading Grammer\n");
	G(); 
}

void G()
{
	lex();
	printf("G->E\n");
	E();
	if(next_token == '$' && !(error))
	{
		printf("success\n");
	}
	else 
	{
		cout<<"failure:unconsumed input == "<< unconsumed_input();
	}

}
void E()
{
	if (error) return;
	printf("E -> T R\n");
	T();
	R();
}

void R()
{
	if(error) return;
	if(next_token == '+')
	{
		printf("R -> + T R\n");
		lex();
		T();
		R();
		
	}
	else if (next_token== '-')
	{
		printf("R -> - T R\n");
		lex();
		T();
		R();
	}
	else  
	{
      printf("R->e\n");
    }

}

void T()
{
	if (error) return;
	printf("T -> F S\n");
	F();
	S();

}

void S()
{
	if (error) return;
	if (next_token=='*') 
	{
    	printf("S -> * F S\n");
      	lex();
      	F();
       	S();   
   }
   else if (next_token=='/') 
	{
		printf("S -> / F S\n");
		lex();
      	F();
       	S();   
   }
  else 
	{
      printf("S -> e\n");
   	}

}

void F()
{
	
	if (error) return;
 	if (next_token=='(' )  
	{
       	printf("F->( E )\n");
       	lex();
       	E();
   		if (next_token == ')'  )
		{
            lex();
        }
		else 
		{  
			error=true; 
            printf("error: unexptected token %c\n", next_token);      
            cout<<"unconsumed_input 1 = "<<unconsumed_input(); 
           	return;
       } 
	}
	else if(isdigit(next_token)) 
	{
      	printf("F->%c\n", next_token);
       	D();
    }
    else 
	{
          error=true; 
          printf("error: unexptected token %c\n", next_token);
          cout<<"unconsumed_input 2 = "<<unconsumed_input();   
    }
}

void D()
{
	if (error) return;
 	if(isdigit(next_token)) 
	{
       	printf("D->%c\n", next_token);
     	lex();
   	} 
	else 
	{
      	error=true; 
      	printf("error: unexptected token %c\n", next_token); 
    	cout<<"unconsumed_input 3 = "<<unconsumed_input();
   }


}
char lex()
{
	char ch;
	while(1)
	{
		scanner.get(ch);
		if(ch == ' ' || ch == '\n')
		{
			break;
		}
		next_token = ch;
		return next_token;
	}
} 

string unconsumed_input()
{
	if(!(scanner.eof()))
	{
		char ch;

    	while(scanner)
    	{
			scanner.get(ch);
			if (scanner.eof())
          	 	 break;
			lexy +=ch;
	
		}
	}
	return lexy;
}