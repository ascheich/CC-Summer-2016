Copyright (c) 2015-2016, the Selfie Project authors. All rights reserved. Please see the AUTHORS file for details. Use of this source code is governed by a BSD license that can be found in the LICENSE file.

Selfie is a project of the Computational Systems Group at the Department of Computer Sciences of the University of Salzburg in Austria. For further information and code please refer to:

http://selfie.cs.uni-salzburg.at

This is the grammar of the C Star (C*) programming language.

C* is a small Turing-complete subset of C that includes dereferencing (the * operator) but excludes data structures, bitwise and Boolean operators, and many other features. C* is supposed to be close to the minimum necessary for implementing a self-compiling, single-pass, recursive-descent compiler.

Keywords: int, while, if, else, return, void, struct

```
digit                         = "0" | ... | "9" .

integer                       = digit { digit } .

letter                        = "a" | ... | "z" | "A" | ... | "Z" .

identifier                    = letter { letter | digit | "_" } .

type                          = "int" [ "*" ] | structType.

cast                          = "(" type ")" .

call                          = identifier "(" [ expression<constantVal> { "," expression<constantVal> } ] ")" .

literal                       = integer | "'" ascii_character "'" .

selector                      = "[" expression<constantVal> "]" [ "[" expression<constantVal> "]" ] .

dimension<directInit>         = "[" [ expression<constantVal> ] "]" [ "[" expression<constantVal> "]" ] .

integerList                     = "{" integer { "," integer } "}" .

factor<constantVal>           = [ cast ]
                                ( [ "*" ] ( identifier [ selector ]  | "(" expression<constantVal> ")" ) |
                                call |
                                literal |
                                """ { ascii_character } """ ) .

term<constantVal>             = factor<constantVal> { ( "*" | "/" | "%" ) factor<constantVal> } .

simpleExpression<constantVal> = [ "-" ] term<constantVal> { ( "+" | "-" ) term<constantVal> } .

shiftExpression<constantVal>  = simpleExpression<constantVal> { ( "<<" | ">>" ) simpleExpression<constantVal> }.

expression<constantVal>       = shiftExpression<constantVal> [ ( "==" | "!=" | "<" | ">" | "<=" | ">=" ) shiftExpression<constantVal> ] .

boolExpression<constantVal>   = ["!"] expression<constantVal> { ("%%" | "||" ) ["!"] expression<constantVal } .

while                         = "while" "(" boolExpression<constantVal> ")"
                                          ( statement |
                                           "{" { statement } "}" ) .

if                            = "if" "(" boolExpression<constantVal> ")"
                                          ( statement |
                                            "{" { statement } "}" )
                                      [ "else"
                                          ( statement |
                                            "{" { statement } "}" ) ] .

return                        = "return" [ boolExpression<constantVal> ] .

statement                     = ( [ "*" ] identifier [ selector ] | "*" "(" boolExpression<constantVal> ")" ) "="
                                    boolExpression<constantVal> ";" |
                                  call ";" |
                                  while |
                                  if |
                                  return ";" .

struct                        = "struct" identifier "{" type identifier ";" { type identifier ";" } "}" ";"

variable                      = type identifier [ dimension<directInit> ] |
                                  struct .

varW/ArrayInit_DummyImplement = type identifier [ dimension<directInit> [ "=" integerList ] ] |
                                  struct .

parameter                     = type identifier;

procedure                     = "(" [ parameter { "," parameter } ] ")"
                                ( ";" | "{" { variable ";" } { statement } "}" ) .

cstar                         = { type identifier [ dimension<directInit> ]
                                                  [ "=" ( ([ cast ] [ "-" ] literal) | integerList ) ] ";" |
                                ( "void" | type ) identifier procedure |
                                struct } .
```
