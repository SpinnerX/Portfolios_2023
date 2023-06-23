## Portfolios

### ProjectFormat
This project is just to allow testing for a format library I was currently in developing as there are things broken with it. As well the formatCpp
library needs a big refactoring with the current code base, as well the code does not fully have OS-compatibility features built-in just yet.

As these features will soon be implemented soon in the library, included with other features that I will have plans in the future. As the main focus
of this library will to be lightweight, and faster than using std::cout and std::cerr, and allow to use stderr and stdout while still allowing type-safety
for a much easier and readable code.

Haven't done the benchmarking yet for this library yet, but soon enough will be later on...


### Compiler
Using ARM32 and C++ with a bit of C, I did a basic implementation of a compiler taught in the Computer Architecture class. Where we discussed about optimization techniques such as SIMD, Neon used with ARM32, pipelining, etc.

Using what we learned also about embedded systems and CPU's, implemented a basic compiler to generate the assembly code for us. Which essentially parses a command and generates the assembly and using that assembly to help us generate the output from C++ to ARM32, to output.
