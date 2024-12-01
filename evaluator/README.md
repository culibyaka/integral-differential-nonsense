# idn::Evaluator

## Expression

### Basic

<op> ::= '+' | '-' | '/' | '*'

<digit> ::= '0' | ... | '9'
<letter> ::= 'a' | ... | 'z' | 'A' | ... | 'Z'

<natural> ::= digit+
<number> ::= ('+' | '-')? natural ('.' natural)?

<name> ::= ('_' | letter)? (letters | digit | '_')*

### Advanced

<expr> ::= '(' expr op expr')' | number
