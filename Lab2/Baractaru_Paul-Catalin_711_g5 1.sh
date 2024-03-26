#!/bin/bash

# Check of there are no command line arguments
if [ $# -eq 0 ]
then
echo "Give a folder name!"
exit 1
fi

# Loop over all command line arguments
for f in "$@"
do

# Check if the file name ends with ".c"
if [[ $f == *.c ]]
then 

# Count the number of lines that start with "#include" in the file
count=`grep -c '^#include' "$f"`

# Check if the count id greater than or equal to 3
if [[ count -ge 3 ]]
then
echo "$f"
fi
fi
done 
exit 0

