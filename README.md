fractran
========

Fractran interpreter in Fractran

This was originally a [Stack Overflow answer](http://stackoverflow.com/a/1773868/112) that was closed. I've just copied the code and documentation here, but haven't tested anything.

The interpreter is fractran.fr, and is 1779 fractions.

Input is specified as follows:

First, we encode a fraction `m/n = p_0^a0... p_k^ak` by:

- Start with 1. Then, for each `ai`:
-  Multiply by `p_2i^ai` if `ai > 0`
-  Multiply by `p_2i+1^{-ai}` if `a_i < 0`

This way, we encode any fraction as a positive integer. Now, given a progoram (sequence of encoded fractions F0, F1, ...), we encode that by

p_0^F0 p1^F1 ...

Finally, input to the interpreter is given by:

2^(program) 3^(input) 5

where `program` and `input` are encoded as above. For example, in the first test problem, `3/2` gets encoded to `15`, so the program gets encoded to `2^15`; and `108` gets encoded to `500`. So, we pass

2^{2^15} 3^500 5

to the program. The output, then is of the form

2^(program) 3^(output)

so in the first example, it'll be

2^{2^15} 3^3125

<hr/>

How does it work?
-----------------

I wrote a meta-language that compiles down to Fractran. It allows for functions (simple Fractran and sequences of other functions), and a `while` loop and `if` statement (for convenience!). The code for that is in interpeter.frp).

If you want to compile that code down to Fractran yourself, you can use fracc. I used my C++ YAML parser [yaml-cpp](http://code.google.com/p/yaml-cpp/), so you'd have to download and link with that; but I used the 0.3.x branch, and haven't updated it to 0.5.x. Patches welcome. For both yaml-cpp and the "compiler", you'll need [CMake](http://www.cmake.org) for cross-platform makefile generating.

The usage of this program is:

./fracc interpreter.frp

It reads the name of a function from standard input, and writes the corresponding "pseudo-Fraction" (I'll explain that in a second) to standard output. So to compile the interpreter (the Interpret function), you could run

echo "Interpret" | ./fracc interpreter.frp > interpret

The output ("pseudo-Fractran") will be a sequence of lines, each with a string of space-separated digits. A line corresponds to a fraction: if the `n`th digit in the line is `an`, then the fraction is the product of `p_n^an`.

It's very easy to convert this to Fractran, but if you're lazy, you can use to-fractions.py

**Note about input**: if you want to test out a different function this way, the convention is always the same. It has a number of parameters (usually the comment above the function explains this) in pseudo-Fractran, so give it what it wants, plus a `1` on the very next slot (so in ordinary Fractran, multiply once by the first prime that it won't use). This is a "signal" bit to the function to start going.

<hr/>

However,
--------

I don't recommend actually trying to run the Fractran interpreter (alas). I tested many of its components, and, for example, the function `IncrementPrimes`, which takes a pair of primes and returns the next two primes, takes about **8 minutes** to run, using my silly C++ interpreter. Plus, it goes (at least) quadratically in the number of function calls - doubling the number of function calls makes it take at least four times as long (more if there are `while` loops or `if` statements). So I'm guessing that running the interpreter will take at least days, if not years :(

So how do I know it works? Well, of course I'm not 100% certain, but I'm pretty close. First of all, I tested many, many of its components, and in particular, I tested all of the elements of the meta-language (sequences of functions and `if` and `while` statements) very thoroughly.

Also, the meta-language is easy to translate into your favorite language, and even easier to translate to C++, since all parameters of functions are passed by reference. If you're feeling lazy again, you can use interpreter-cpp.

So you can compare the two interpreters, run the C++ version (it also takes input/output in pseudo-Fractran), check that that works, and then convince yourself that the meta-language works too.

<hr/>

Or!
---

If you're feeling inspired, and *really* want to see this interpreter interpreted, you can write a "clever" Fractran interpreter based around the type of Fractran output that we get. The output is very structured - sequences of functions are implemented using signals, so if you somehow cache where the interpreter was, you could jump there immediately if nothing important changed. This, I think, would dramatically speed up the program (perhaps cutting down running time by one or more powers).

But, I'm not really sure how to do this, and I'm happy with what's done, so I'll leave it as an exercise for the reader.