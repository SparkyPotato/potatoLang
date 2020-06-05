# potatoLang
A simple interpreter I'm working on, written in C++.

# Getting it working
This is Visual Studio 2019 solution, so just clone it to your computer, or download it as a zip, and open it with Visual Studio.
When running, just provide the path of the file to interpret when prompted, and go on your merry way! Submit any bug reports to the Issues.

# Current fuctionality and Syntax
Basic Syntax:-

1. Statements are separated by newline characters.

2. Arguments are separated by spaces.

3. Functions require parentheses, even if there are no arguments to be passed.

Basic functionality:-

1. Set a variable by using `set <var-name> as <var-value>` - the `as` is not required. Currently, variables can be a float (number), string, boolean, or function return value.

2. Print to the console by using `print(<arguments>)` - where `<arguments>` can be a string, number, boolean, variable, or function return value.

3. Get input by using `set <var-name> as input(<prompt>)` - where `<prompt>` is the prompt to show to the user. The input will be assigned to `<var-name>`

4. Basic arithmetic is achieved by using the `add()`, `subtract()`, `multiply()`, `divide()` and `power()` functions. `add()`, and `multiply()` accept and infnite number of arguments - can be variables or numbers. `subtract()`, `divide()`, and `power()` only accept two arguments. The format followed for `power()` is `power(<base> <exponent>)`. 

5. `if` and `else` statements are supported. Currently, `else if` and nested `if` statements are not supported. 