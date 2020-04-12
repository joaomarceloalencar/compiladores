%token NUMBER
%% 
command : exp
        ; 
exp : exp '+' term 
    | exp '-' term 
    | term 
    ;
 
term : term '*' factor 
    | factor 
    ;      

factor : NUMBER 
    | '('exp')' 
    ;  
