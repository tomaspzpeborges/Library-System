#!/bin/bash 
/Users/tomaspzpeborges/OneDrive\ -\ University\ of\ Leeds/Programming\ Project/egypt-1.10/egypt $@ | dot -Gsize=8,11  -Tpdf -o callgraph.pdf
