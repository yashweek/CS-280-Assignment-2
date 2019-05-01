//
//  getNextToken.cpp
//  getNextToken
//
//  Created by Yashwee Kothari on 2/27/19.
//  Copyright © 2019 Yashwee Kothari. All rights reserved.
//

#include "tokens.h"
#include <map>

using namespace std;

string stringToUpper(string &s)
{
   for(int i = 0; i < s.length(); i++)
  {
    s[i] = toupper(s[i]);
  }
   return s;
}

 map <string, TokenType > TokenMap = {
        { "PRINT", PRINT},
        { "SET",SET},
        { "IF",IF},
        { "LOOP",LOOP},
        { "BEGIN",BEGIN},
        { "END", END},
        { "ID",ID},
        { "ICONST",ICONST},
        { "SCONST", SCONST},
        { "PLUS", PLUS},
        { "MINUS", MINUS},
        { "STAR", STAR},
        { "SLASH", SLASH},
        { "LPAREN", LPAREN},
        { "RPAREN", RPAREN},
        { "SC", SC},
        { "NL", NL},
        { "ERR", ERR},
        { "DONE", DONE}
        
    
    };

map < TokenType,string > TokenMap2 = {
        {  PRINT, "PRINT"},
        {  SET, "SET"},
        {  IF, "IF"},
        {  LOOP, "LOOP"},
        {  BEGIN, "BEGIN"},
        {  END, "END"},
        {  ID, "ID"},
        {  ICONST, "ICONST"},
        {  SCONST, "SCONST"},
        {  PLUS, "PLUS"},
        {  MINUS, "MINUS"},
        {  STAR, "STAR"},
        {  SLASH, "SLASH"},
        {  LPAREN, "LPAREN"},
        {  RPAREN, "RPAREN"},
        {  SC, "SC"},
        {  NL, "NL"},
        {  ERR, "ERR"},
        {  DONE, "DONE"}
        
    
    };


    
ostream& operator <<(ostream& out, const Token& tok){

    TokenType tt = tok.GetTokenType();
      out<<TokenMap2[tt];
    if(tt== ID || tt==ICONST || tt==SCONST || tt== ERR){
      out<< "(" << tok.GetLexeme() <<")";
    }
    
    return out;
}
 
Token getNextToken(istream& in, int& linenumber){
   
    
    char ch;
    string lexeme;
    
    enum  LexState  {BEGIN, IDENT, ICONST, SCONST, ERR, DONE, COMMENT} state = BEGIN; 
    
    //in is the file 
   
    
    while(in.get(ch)){ 
        
     switch(state){
             
         case BEGIN:
             
             if(isalpha(ch)){
                 lexeme += ch;
                 state = IDENT;
             
             }
              
             if(isdigit(ch)){
                 lexeme += ch;
                 state = ICONST;
                 
             }
             
             if(ch == '"'){
                 state = SCONST;
              
             }
              
            if(ch == '+' ){ 
                lexeme += ch;
               return Token(PLUS, lexeme, linenumber);
                
            }
             
            if(ch == '-'){
                lexeme += ch;
                return Token(MINUS, lexeme, linenumber);
                
            
            }
             
            if(ch == '*'){
                lexeme += ch;
              return Token(STAR, lexeme, linenumber);
                lexeme.clear();
            
            }
             
            if(ch == '/'){  
                lexeme += ch;
             return Token(SLASH, lexeme, linenumber);
                lexeme.clear();
            
            }
             
            if(ch == '('){
                lexeme += ch;
                return Token(LPAREN, lexeme, linenumber);
                lexeme.clear();
            
            }
             
            if(ch == ')'){
            lexeme += ch;
               return Token(RPAREN, lexeme, linenumber);
                lexeme.clear();
            }
             
             if(ch == '.'){
            lexeme += ch;
               return Token(TokenType::ERR, lexeme, linenumber);
                lexeme.clear();
            }
               
            if(ch == ';'){
                lexeme += ";";
              
                return Token(SC, lexeme, linenumber);
                lexeme.clear();
            }
             
            if(ch == '\n'){
                lexeme += ch;
                linenumber++;
                return Token(NL, lexeme, linenumber);
                lexeme.clear();
            }
               
               
             if(ch == '#'){
                state = COMMENT;
            }
    
            break;
             
             
            //IDENTIFIER
             
         case IDENT:
             if(isalpha(ch) || isdigit(ch)){
                 lexeme +=ch;
                 if(!isalnum(in.peek())) {
                    
                 }
                 
             }
             else {
                
                 //doesn't recognize periods as punctuation 
                 
             
                 
                 if(ch == '.'){
                    lexeme.clear();
                    lexeme +=ch;
                
                    return Token(TokenType::ERR, lexeme, linenumber);
                 }
                 
                  if(ch == '!'){
                    lexeme.clear();
                    lexeme +=ch;
                
                    return Token(TokenType::ERR, lexeme, linenumber);
                 }
                 
                 in.putback(ch);
                
                string lex2 = lexeme;
                
                 if (TokenMap.count(stringToUpper(lex2)) > 0){    //seeing if it is a keyword by making it uppercase and then checking
                   
                     return Token(TokenMap[lex2], lexeme, linenumber);
                     
                      
                 }
                 
                 else{ //not a keyword
                     
                 
              return Token(TokenType::ID, lexeme, linenumber);
                     
                  
                 }
           
             }
             
             
            break;
             
           
             //ICONST
         
         case ICONST:
             if(isdigit(ch)){
                 lexeme += ch;
                 
             }
             
             else if(isalpha(ch)){
                 lexeme +=ch;
               
                return Token(TokenType::ERR, lexeme, linenumber);
                
                 
             }
             
          
             
             else{ 
                in.putback(ch);
          return Token(TokenType:: ICONST, lexeme, linenumber);

                
             
             }
            
            break;
             
        
             
             //SCONST
             
         case SCONST:
             if(ch == '"'){
             
           return Token(TokenType::SCONST, lexeme, linenumber);
        
             }
             
             else if(ch == '\\'){
                 if(isalpha(in.peek()) || isspace(in.peek()) || ispunct(in.peek())){
                     if(in.peek() == 'n'){
                         in.get(ch);
                         lexeme += '\n';
                     }
                     else{
                         in.get(ch);
                         lexeme +=ch;
                     }
                 
                 }
                 
                 else{
                 lexeme += "\\";
                 
                 }
             
             }
             
             else if(ch == '\n'){
                 lexeme +=ch;
                 lexeme.insert(0, 1, '"');
              return Token(TokenType::ERR, lexeme, linenumber);
             }
            
           else {
             lexeme += ch;
                 
             } 
             
             
            break;
         
         case COMMENT:
             if(ch == '\n'){
                 linenumber++;
                return Token(TokenType::NL, lexeme, linenumber);
                
             }
           
             
            break;
             
         
         case DONE:
            break;
             
         case ERR:
         
            
             break;
             
     
     //do cases
     }
    
    }
    
   
   if(in.eof()){
               return Token(TokenType::DONE, lexeme, linenumber);
            }
		

    
    
    
    
    
    
return Token();
    
    //Token (IDEN, lexme, line#)
    
}


