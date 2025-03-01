#!/bin/bash

 # Filename: junk.sh
 # Author  : John Graham 
 # Pledge  : I pledge my honor that I have abided by the Stevens Honor System. 
 


readonly name=".junk"

h=0
l=0
p=0
countargs=0

while getopts ":hlp" option; do
    case ${option} in
        h)
            h=1
            ;;
        l)
            l=1
            ;;
        p)
            p=1
            ;;
        *)
            h=2
            echo "Error: Unknown option '-$OPTARG'" >&2
            break
    esac
    countargs=$(( $countargs + 1 ))
done

if [[ $h -eq 2 ]]; then
cat << EOF
Usage: ./$(basename $0) [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files
EOF
    exit 1
fi
if [[ $(( $h + $l + $p )) -gt 1 ]]; then
    echo "Error: Too many options enabled." >&2
    h=2
elif [[ $(( $# - $countargs )) -gt 0 ]]; then
    if [[ ! $(( $h + $l + $p )) -eq 0 ]]; then
        echo "Error: Too many options enabled." >&2
        h=2
    fi
fi
if [[ $h -eq 2 ]]; then
cat << EOF
Usage: ./$(basename $0) [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files
EOF
    exit 1
fi

#DONE PARSING :)


if [[ ! -d /home/$(whoami)/$name ]]; then
    mkdir /home/$(whoami)/$name
fi

if [[ $# -eq 0 ]]; then
cat << EOF
Usage: ./$(basename $0) [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files
EOF
    exit 0
fi


junksize=$(( $( ls /home/$(whoami)/.junk -a | wc -l ) - 2 ))

if [[ $h -eq 1 ]]; then
cat << EOF
Usage: ./$(basename $0) [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files
EOF
    exit 0
elif [[ $l -eq 1 ]]; then
    ls /home/$(whoami)/$name -lAF
    exit 0
elif [[ $p -eq 1 ]]; then
    if [[ $junksize -gt 0 ]]; then
        rm -r /home/$(whoami)/$name/.* &> /dev/null
        rm -r /home/$(whoami)/$name/* &> /dev/null
    fi
    exit 0
fi


#JUNKING FILES

for file in $@; do
    if [[ -e $file ]]; then
        mv $file /home/$(whoami)/$name
    else
        echo "Warning: '$file' not found." >&2
    fi
done

exit 0