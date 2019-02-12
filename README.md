# Postfix_Infix_Stack

Part I - postfix.cpp

A. main(): will call the menu()  function
B. menu(): creates a stack variable and an input variable. Will enter a loop and prompt user for input. Input will be a series of
characters. The exceptions() function will be called. If the exceptions() function does nothing, then the execute() function will be
called (still w/in the loop)
C. execute(): Will enter a loop until the end of input. Will call an isNumber() function, an isOperator() function, or a print() 
function depending on the what information from the input is parsed. If the string is a number, it will be pushed onto a stack. If the
string is an operator, two values are popped from the stack, the operation is carried out on the two numbers, and the result is pushed
onto the stack. After every number or operator, the print() function is called
D. isNumber(): returns a boolean value. Determines if the string is a number
E. isOperator(): returns a boolean value. Determines if the string is an operator
F. print(): Prints the operation


Part II - infix.cpp

A. main(): Creates a stack variable and a tree variable. Will enter a loop until end of file. Will call the treeBuild() function
B. treeBuild(): Will build a tree for every line of operations (After every operation, the tree will be deleted, and the program will
move on the next line in the file). Will call the isOperator() function to determine of the character is an operator. After every line
in the file, the deleteTree() function will be called
C. isOperator(): returns a booolean value. Determines if the string is an operator
D. print(): prints the tree for an operation using preorder traversal
E. deleteTree(): deletes the current tree in use
