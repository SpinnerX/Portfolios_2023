# There's four main needs for ASM in this day and age
```
1) Optimization
2) Embedded systems
3) Compilers
4) Cracking

For this assignment, we'll focus on #3. In particular, assembly is handy with
compilers in two ways:

1) Writing your own compilers
2) Optimizing the output of compilers
3) Seeing if a compiler has an error (like off by one).

This assignment will touch a bit on all three of these areas. You will write a
very simple compiler, that will translate a new programming language, called
Basic Basic v8, into assembly, and then assemble it into an executable.

Your compiler will be named bb8. Your source code files will all end in .bb.
So you'll compile your BB8 source like this:
bb8 main.bb

And this will generate a main.s, and a.out, and automatically run it!

Unlike our other assembly projects, this one will be written in C or C++
(your choice). Your code's OUTPUT will be assembly. And an executable.

If no errors are found in the source code, you will then assemble the source
code emitted, and produce an a.out!
```
# Basic Basic v8.0 Language Specification
```
General Error Rule:
0. Any line that does not conform to the rules below will result in your
compiler outputting "Syntax Error on Line X" (where X is the line of code) and
terminating without creating an assembly source code or executable.

Each line of code will take up *exactly* one line of text (BB8 is newline
terminated):

1. Every line of code must start with a number
1.1 All lines must start with a number, and the line number of each line must
be greater than the line number of the line before it, but they do not need to
be continuous. (I.e., line could be numbered 10, 20, 30, etc.)
1.2 All lines that start with a number and then REM are comments, and the rest
of the line must be discarded.

2. After the number and space, there will be a command. The following commands
exist:
2.1 GOTO X - this makes it so the next line of code to run is line X
(X is a number)
2.2 PRINT X - this will print the value of variable X (see variables, below)
to stdout, and add a newline.
2.3 PRINT "STRING" - this will print the string held within the double quotes
to stdout, without adding a newline.
2.4 LET X = Y + Z - this will set the value of variable X to the sum of Y and
Z (which are also variables)
2.5 LET X = Y - Z - this will set the value of variable X to the difference of
Y and Z
2.6 LET X = Y * Z - this will set the value of variable X to the product of Y
and Z
2.7 LET X = NUMBER - this will set variable X to the immediate value held in
number
2.8 IF (LOGICAL EXPRESSION) THEN GOTO X - if the logical expression is true
(see below) then jump to line X.
2.9 IF (LOGICAL EXPRESSION) THEN GOTO X ELSE GOTO Y - if the logical
expression is true (see below) then jump to line X, otherwise jump to line Y.
2.10 INPUT X - this will read one number from the standard input and store it
into the variable specified.
2.11 END - terminates the program
2.12 Note: All commands take up exactly one line. Any command not matching the
above is a syntax error.

3. Variables.
3.1 All variables will be 32-bit integers.
3.2 All variables have single letter names.
3.2 Only 8 variables exist: A, B, C, I, J, X, Y, Z.
3.3 Trying to use any other variable is a syntax error.
3.4 All variables must be set to 0 at program start
3.5 Example: LET X = C + Z will set X to the sum of C + Z

4. Logical expressions.
4.1 All logical expressions are comparisons of two variables. (I.e. no
comparisons with immediates.)
4.2 The following comparisons must be supported: >, <, >=, <=, ==, !=.
4.3 The only thing an if statement can do is GOTO one line, and maybe ELSE
goto another line.
4.4 Example: IF X > Y THEN GOTO 10

5. Program termination.
5.1 The program will terminate when it tries to go past the last line of code
5.2 The program will terminate whenever a EXIT or END command is executed

6. Syntax errors.
6.1 Any line of code not conforming to the syntax specified above will
generate an error.
6.2 All errors will be detected at compile time. There are no run time errors.
6.3 When a syntax error is detected, print out: "Syntax Error on line X" and
terminate compilation.
6.4 Even if a file has multiple syntax errors, only print out the first error
and quit.
6.5 A GOTO statement with an invalid line number (i.e. one that does not exist)
 is an error
6.6 Using a variable name that does not exist is an error
6.7 Using an operation or logical expression not supported is an error
6.8 Giving a command that does not exist is an error

Example code #1:
10 PRINT "HELLO WORLD!\n";
20 GOTO 10

This will go into an infinite loop, printing out HELLO WORLD! over and over.

Example code #2:
5 REM This is a comment
10 LET X = 0
11 LET A = 5
12 LET Y = 1
20 IF X > A THEN GOTO 100
25 PRINT "X = "
30 PRINT X
40 LET X = X + Y
50 GOTO 20
100 END

This will print to the screen:
X = 5
X = 4
X = 3
X = 2
X = 1
```
