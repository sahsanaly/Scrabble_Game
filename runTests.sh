#! /bin/bash

numTestsFailed=0

for filename in tests/*.in; do
    baseFile=$(basename "$filename" .in)
    baseFile="tests/${baseFile}"
    ./scrabble < "${baseFile}.in" > "${baseFile}.out"
    difference=$(diff "${baseFile}.exp" "${baseFile}.out")
    if [ ! -z "${difference}" ];
    then
        echo
        ((numTestsFailed = numTestsFailed + 1))
        echo "Error in ${filename}: "
        echo "${difference}"
    fi
done

echo

if [ $numTestsFailed == 0 ];
    then
        echo "All test(s) passed."
    else
        echo "${numTestsFailed} test(s) failed. See above for error logs."
fi

echo