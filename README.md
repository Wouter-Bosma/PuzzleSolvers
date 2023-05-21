# PuzzleSolvers
Sample projects to store solvers in c++ and a GUI in C# interacting via zeromq

This repo contains a (growing) number of solvers for generic coding problems or puzzles written in C++. The solvers are accessed via a zeromq layer and connect to a C# GUI.

Although it is over engineering, the reason is that it is more interesting to solve the problems in c++ but it is significantly easier to set-up a GUI in a higher level language like C#. The used standards are C++20 (due to the improved resolution of types) and .Net 6.0 (due to that being the latest LTS version).

Both apps communicate via a simple zeromq protocol with a serialized string as communication method. Other choices could have been possible (ie. json/xml) over a rest api. But for sake of simplicity this option has been chosen.

Both the C# and C++ programs have been written with vs2022 and both rely on the NuGet packages, namely the one for ZeroMQ.

