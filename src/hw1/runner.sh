#!/bin/bash
# Joshua Meharg CS392 2023


if [[ ! $PWD = $HOME ]] ; then
    echo "ERROR: runner.sh has to be run in $HOME"
    echo "       Also make sure testcases2-txt and junk.sh are in the $HOME"
    exit 1
fi

if [[ ! -a "junk.sh" ]] ; then

echo "junk.sh not found in home directory"
exit 1

fi

if [[ ! -a "testcases-2.txt" ]] ; then

echo "testcases-2.txt not found in home directory, download it from canvas/move it to home directory"
exit 1

fi


if [[ $# > 0 ]] ; then

echo "ERROR: too many arguments"
echo "usage: ./runner.sh"
exit 1

fi



input="/$HOME/testcases-2.txt"

touch junk0.txt
mkdir -p dir1 2>/dev/null
mkdir -p dir2/dir3 2>/dev/null
mkdir .hidden1.txt 2>/dev/null
mkdir .hideme 2>/dev/null
mkdir .hideme2 2>/dev/null
touch .hideme2/hide.txt

touch dir1/junk1.txt

touch dir2/.hidden2.txt
touch dir2/file3.txt
touch dir2/junk2.txt

touch dir2/dir3/junk3.txt

touch file1.txt
touch file2.txt
touch file4.txt
touch junk0.txt
touch junksol.sh
touch lastone.txt
touch yetanother



num=0
next=0
# echo "successfully set up test files + directories"
# sleep 1
# clear >$(tty)

clear >$(tty)
echo "===============================================PLEASE READ==============================================="
echo 
echo "Info: tested echo $ ? after each command automatically and"
echo "      removed tree tests that's why it appears THAT TESTS ARE SKIPPED"
echo 
echo "Info: Despite skipping tests test case numbers still"
echo "      allign with the original ones in testcases-2.txt for easy comparison"
echo 
echo "Info: This script simply sets up all the test files and calls all the commands in "
echo "      the testcases-2.txt for you, there is no automatic comparison with expected output"
echo 
echo "IMPORTANT: however don't just rely on this for all your testing"
echo "           or think you'll get a 100 if all theses test cases work this is just for your convience :)"
echo
read -sp 'Press enter to continue '
clear >$(tty)
echo

while read line
do 
    
    if [ $next = 1 ] && [ "${line:0:4}" = "echo" ] ; then
        num=$(( $num + 1 ))
        next=0
    fi

    if [ $next = 1 ] && [ "${line:0:4}" = "tree" ] ; then
        num=$(( $num + 1 ))
        next=0
    fi



    if [ $next = 1 ] ; then
        echo
        echo "Test $num"
        echo "running command: $line"
        echo
        echo "==============================OUTPUT=============================="
        eval $line 
        eval exit_value=$(eval echo $?)
        # echo $? has to be run right after $line command to catchthe exit value this is why its saved into
        # a variable and printed later rather than just calling echo $? later
        echo "=================================================================="
        echo "Command finsihed with exit value: $exit_value"
        echo
        num=$(( $num + 1 ))
        next=0
    fi

    if [ "${line:0:4}" = "Test" ] ; then
        next=1
    fi


    # fi
    
done < "$input"

# rm -r dir1
# rm -r dir2
# rm -r .hideme2
