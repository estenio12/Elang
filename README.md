# <h2>PROJECT DESCRIPTION</h2>

THIS PROJECT IS BEING DEVELOPED AS A COMPUTER SCIENCE FINAL COURSE<br> 
PROJECT AT FAM UNIVERSITY.

THIS PROJECT IS NOT INTENDED TO BE USED IN THE MARKET, BECAUSE ITS<br> 
ENTIRE ARCHITECTURE WAS NOT THOUGHT FOR IT.

ITS COMPILATION IS ACTUALLY A TRANSPILATION, WHERE THE COMPILER<br>
GETS THE SOURCE CODE, AND CONVERTS TO AN ALREADY EXISTING LANGUAGE,<br> 
WHICH IN THIS CASE IS C++.

THIS PROJECT IS UNDER MIT LICENSE, YOU ARE FREE TO DOWNLOAD, MODIFY<br>
AND DISTRIBUTE AS YOU WANT. WITHOUT THE NEED TO GIVE CREDIT TO THE<br> 
ORIGINAL AUTHOR, BUT, IF YOU WANT, YOU WILL BE VERY WELCOME! :D

# <h2>PROJECT STATE</h2>

 PRE-PROCESSOR  - TO DO<br>
 LEXIC ANALYSER - DONE<br>
 SINTATICAL ANALYSER - WIP<br>
 CODE OPTIMIZER - TO DO<br>
 CODE GENERATOR - TO DO<br>

# <h2>DEPENDECY</h2>

  GCC OR CLANG

DURING THE DEVELOPMENT OF THE LANGUAGE COMPILER, I AM USING GCC, BUT<br> 
THE FINAL PRODUCT WILL BE COMPILED WITH CLANG.

# <h2>LANGUAGEM DOCUMENTATION</h2>

THE NAME ELANG WAS INSPIRED BY THE NAME OF CLANG.

THE ELANG LANGUAGE WORKS WITH THE FUNCTIONAL PARADIGM, NOT SUPPORTING<br> 
OBJECT ORIENTATION AND LAMBDA FUNCTIONS YET.

<details>
<summary><h3> - Variables - <h3></summary>
<p>
var   = MUTABLE DATA STORAGE<br>
const = IMUTABLE DATA STORAGE
   
TYPE DATA SUPORTED:
 * NUMBER -> FLOAT AND INTEGER VALUES;
 * STRING -> TEXT AND CHARACTER VALUES;
   
EXEMPLE:
 var foo = "lorem ipsum";
 const PI = 3.14159265;
   
ARRAYS:
 var bar = [1,3,4,8];
 var foo = ["LOREM IPSUM",67.45, 15, 'C'];
 </p>
</details>
 
<details>
<summary><h3> - Functions - <h3></summary>
<p>
 fun    = COMMAND BLOCK;
 return = RETURN VALUES;
 
EXEMPLE:
 
fun bar(){
  # TO DO
}

fun foo(){
 
 const a = 10;
 const b = 10;

 var c = a + b;
 
 return c;
}
 
fun sum(var n1, var n2 ){
 
 return n1 + n2;
}
</p>
</details>
 
<details>
<summary><h3> - Conditions - <h3></summary>
<p>
 if, elif, else;
 
# TERNARY CONDITION
 
( condition ) ? true : false;
 
if( condition ){
 
 # TO DO
 
}elif( condition ){
 
 # TO DO
 
}else{
 
 # TO DO
}
</p>
</details>
 
 <details>
<summary><h3> - Loops - <h3></summary>
<p>
for, while, do while;
 
#<----| EXEMPLE: (FOR)
for( var i in 10 ){
        
 # with "in" keyword, this for repeat like:
 # 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
}
for( var i at 10 ){
        
 # with "at" keyword, this for repeat like:
 # 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
}
        
for( var i = 3 at 10 ){
 # with "at" keyword, this for repeat like:
 # 3, 4, 5, 6, 7, 8, 9, 10
}
        
#<----| EXEMPLE: (WHILE, DO)
 
while( condition ){
 
 # TO DO
 
}
 
do{
 
 # TO DO
 
}while( condition );
</p>
</details>
