#! /bin/bash

for filename in tests/*.in; do
    baseFile=$(basename "$filename" .in)
    baseFile="tests/${baseFile}"
    ./scrabble < "${baseFile}.in" > "${baseFile}.out"
    difference=$(diff "${baseFile}.exp" "${baseFile}.out")
    if [ ! -z "${difference}" ];
    then
        echo "Error in ${filename}: "
        echo "${difference}";
    fi
done

echo "All other tests passed"