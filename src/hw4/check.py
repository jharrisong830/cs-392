# NAME:           check.py
# AUTHOR:         John Graham
# DATE:           03/21/23

import subprocess
import os
import sys
import getopt

HELP= \
"CS 392 - Homework 4 Check Script\n\
NOTE: this script assumes it is being run on a Linux system (i.e. an Ubuntu VM). Running on other systems will have unexpected results.\n\
NOTE: you should have stdiox.h, stdiox.c, checker.c, and stdin-1 in the same directory as this file for this script to work.\n\
\n\
      -h    Dispay this message\n\
      -r    Attempts to compile/run based on the commands on Canvas\n\
      -c    Cleans files created by this script (a.out, text, longtext, stdout)"


if __name__=="__main__":
    argc=len(sys.argv)
    if argc==1: print(HELP)
    else:
        opts, args=getopt.getopt(sys.argv[1:], "hrc")
        if len(opts)>1:
            raise ValueError("Too many flags.")
        for opt, arg in opts:
            if opt in ["-h"]:
                print(HELP)
            elif opt in ["-r"]:
                stdinput=open("stdin-1", "r")
                stdoutput=open("stdout", "w")
                subprocess.run(["gcc", "-g", "checker.c", "stdiox.c"], check=True)
                subprocess.run(["./a.out"], check=True, stdin=stdinput, stdout=stdoutput)
                stdinput.close()
                stdoutput.close()
            elif opt in ["-c"]:
                if os.path.exists("text"):
                    os.remove("text")
                if os.path.exists("longtext"):
                    os.remove("longtext")
                if os.path.exists("a.out"):
                    os.remove("a.out")
                if os.path.exists("stdout"):
                    os.remove("stdout")