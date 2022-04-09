#!/bin/bash

for ex in $(ls | grep ".aut")
do
    echo $(basename $ex .aut)
    bn=$(basename $ex .aut)
    ../build/automata $ex --graph > $bn.dot && dot -Tpng -Gsize=10,10\! -Gdpi=100 $bn.dot -o $bn.png
done
