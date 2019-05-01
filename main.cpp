//
//  main.cpp
//  Assignment2
//
//  Created by Yashwee Kothari on 2/25/19.
//  Copyright © 2019 Yashwee Kothari. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "tokens.h"
#include <map>
#include <list>

using namespace std;

int main(int argc,  char * argv[]) {
    int linenumber  =1;
    bool v=false;
    bool ids =false;
    bool string1 =false;
   
    istream *input = &cin;
    
    ifstream inFile;
   
    for(int i =1; i<argc; i++){
    
     string vari(argv[i]);
        
    if(vari == "-v"){ 
        v = !v;
      
    }
        else if(vari =="-ids"){
         ids = !ids;
        
        }
        
        else if(vari == "-strings"){
       string1 = !string1;
        
        }
        
       else if(vari[0] == '-'){
           cerr<< "UNRECOGNIZED FLAG " << vari <<endl;
        return -1;
       } 
        
        
       else if (i == argc-1){
           
           
        
        inFile.open(vari);
           
      if( inFile.is_open() == false ) {
        cerr << "CANNOT OPEN "<< vari << endl;
        return -1;
    } 
            input = &inFile; 
       
        
        }
        
        else{
           
         cerr << "ONLY ONE FILE NAME ALLOWED" <<endl;
        return -1;
        }
        
      
  
    }
    
    
    
    
    
    Token tok;
    int tokenCounter=0;
   
    list<string> idents;
    list<string> sconsts;
    
    while((tok = getNextToken(*input, linenumber)) != TokenType:: ERR && tok != TokenType::DONE){
        
     
        tokenCounter++;
        if(v){
           cout<<tok<<endl;
        }
        
        if(tok.GetTokenType() == ID){
            idents.push_back(tok.GetLexeme());
        }
        
        if(tok.GetTokenType() == SCONST){
            sconsts.push_back(tok.GetLexeme());
        
        }
        
       
    }
    
    ///// 
    
    if(tok.GetTokenType()== TokenType:: ERR){
        cout<< "Error on line " << linenumber << " (" <<tok.GetLexeme()<< ")"<<endl; 
        return -1;
    }
    
    
    ////
    
     if(ids){
         if(idents.size()>0){
          idents.unique();
          idents.sort();
         
         cout<< "IDENTIFIERS: ";
          for (string n : idents) {
              
           cout << n;
              if(n.compare(idents.back())){
                  cout<<", ";
              }
           
    }
         cout<<endl;
         }
            
        }
        
        
        if(string1){
        if(sconsts.size()>0){
           sconsts.unique();
          sconsts.sort();
         
         cout<< "STRINGS:" <<endl;
          for (string n : sconsts) {
              
           cout << n<< endl;
              if(!n.compare(sconsts.front())){
                 //cout<<endl;
              }
              
              
           
    }
        
        }
            
    }
    
    
    
  
    cout<<"Total lines: "<< linenumber-1<<endl;
  
 
    if(tokenCounter >=1){
    cout<<"Total tokens: " << tokenCounter <<endl;
    }
    
    
   
    
    
    return 0;
}
