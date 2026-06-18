> This project is still a work in progress.

# Mini Compiler

Mini Compiler written in `C` using `Flex` and `Bison`, developed as part of a compiler construction project during the third year of my bachelor's degree.
It parses a small "Algorithmic" (ALGO) language, builds an AST, and then generates code for a simple RAM machine.
The RAM machine was developed by one of my former professors.
Link to the RAM machine: https://zanotti.univ-tln.fr/RAM/#machineram 


## Features

- declarations with `DECLA`
- assignments with `<-`
- arithmetic expressions
- comparisons with `<`, `>`, and `=`
- output with `AFFICHER` 
- loops `TQ ... FAIRE ... FTQ` 
- conditions `SI ... ALORS ... SINON ... FSI`


## Utilization

```bash
./bin/arc test/exemple0.algo progRAM.txt
```


## Example

```text
DECLA toto;
toto <- 2;
TQ toto > 0 FAIRE
    SI toto = 3 ALORS
        toto <- 0;
    SINON
        toto <- toto - 1;
    FSI
FTQ
AFFICHER toto;
```

## Structure

- `arc/src/` : compiler source files
- `arc/include/` : headers files
- `arc/test/` : examples and tests

## Future work

- improve the reliability of code generation
- add better tests
- clean generated files 
- add functions to the grammar and the compiler

