# Model-language-translator-on-Cpp
Write a translator program for the model language. The basic part of the description of the model language is given
on page 37 of the book (Volkova I. A., Vylitok A. A., Rudenko T. V. Formal grammars and languages. Elements of the theory
of translation : 3rd ed. Moscow: VMK MSU, 2009). The description of the language is obtained from its basic part by excluding
variables of type int and adding one-dimensional arrays of type int to it. Language constructs
that define an array containing a certain number of elements, and constructs that
there is an access to an array element, can be selected arbitrary, for example such:
D → I {, I}: int [N]
F → I [E]
S → I [E] := E | read(I [E])
or such:
D → I {, I}: array of N int
F → I >> E
S → I >> E := E | read(I >> E)
and so on. A prerequisite for passing the program is the presence of a fully described (on a piece of paper
or in a text editor) grammar defining the language.
If the executable file of the translator program is called a.out, then call ./a.out MyProg.ml it should
lead to the translation and launch of the program, the text of which is in the file MyProg.ml .
