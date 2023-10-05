#!/bin/bash

if [ $# -eq 0 ]
then
    echo -e "\nIncorrect command: Argument not given.\n"
    echo -e "List of commands from \"c++\":\n"
    echo -e "\tc++ <Path_To_File> - Executes cpp file from path given\n"
    return 1
fi

if [ $1 = "--help" ] || [ $1 = "--h" ]
then
    echo -e "\nList of commands from \"c++\":\n"
    echo -e "\tc++ <Path_To_File> - Executes cpp file from path given\n"
    return 0
fi

THIS_FILE="$1"

if [[ $THIS_FILE != /* ]]; then
    THIS_FILE="./$THIS_FILE"
fi

if [ -e "${THIS_FILE}" ] && [ $(echo ${THIS_FILE} | grep -c .cpp) -ge 1 ]
then
    THIS_DIR=$(echo "${THIS_FILE}" | sed -E 's/[a-zA-Z0-9\-\_\s]+\.cpp$//')
    FILENAME="$(basename ${THIS_FILE} | sed -E 's/.cpp//')"
    g++ -std=c++17 -o "${THIS_DIR}${FILENAME}" "${THIS_FILE}"
    "${THIS_DIR}${FILENAME}"
    rm "${THIS_DIR}${FILENAME}"
elif [ $(echo ${THIS_FILE} | grep -c .cpp) -le 0 ]
then
    echo -e "\nIncorrect command: File is not a cpp file.\n"
    echo -e "List of commands from \"c++\":\n"
    echo -e "\tc++ <Path_To_File> - Executes cpp file from path given\n"
fi