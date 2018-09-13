#!/bin/bash

run_test () {
    gcc -o test-power test-power.c $1
    if [ "$?" != "0" ]
    then
        echo "Could not compile test-power.c with $1" > /dev/stderr
        exit 1
    fi
    ./test-power
    return $?
}

correct=/usr/local/ece551/power/power.o
echo "-------------------------------------"
echo "**Testing correct implementation **"
run_test $correct
if [ "$?" != 0 ]
then
    echo "Your test program falsely failed the correct implementation!" > /dev/\
stderr
    exit 1
fi
echo ""

for i in /usr/local/ece551/power/power*.o
do
    test=`basename $i | sed 's/power//' | sed 's/.o//'`
    if [ "$test"  == "" ]
    then
	continue
    fi
    echo "-------------------------------------"
    echo "**Testing broken implementation ${test} **"
    run_test $i
    if [ "$?" == 0 ]
    then
	echo "Your test program did not identify $i as broken!" > /dev/stderr
	exit 1
    fi
    echo ""
done
echo "All tests were correct."
echo ""
