#!/bin/bash

returnError(){
    echo -e "\nIncorrect command: ${1}\n"
    echo -e "List of commands from \"sendc\":\n"
    echo -e "\tsendc <Path_To_Local_File> <Path_To_Remote_File> - Sends file from local machine to remote machine."
    echo -e "\tsendc -r <Path_To_Local_Dir> <Path_To_Remote_Dir> - Sends a complete directory from local machine to remote machine."
}

sendf() {
    FROM="$1"
    DEST="${TARGET_PATH}/$2"

    echo -e "\nFrom: ${FROM}"
    echo -e "To: ${DEST}\n"

    if [ -e "${FROM}" ]
    then
        echo "Procesing file"
        scp "${FROM}" root@137.184.16.45:"${DEST}"
    else
        returnError "Local file does not exist."
        return 1
    fi
}

sendd() {
    FROM="$1"
    DEST="${TARGET_PATH}/$2"

    echo -e "\nFrom: ${FROM}"
    echo -e "To: ${DEST}\n"

    if [ -d "${FROM}" ]
    then
        echo "Procesing file"
        scp -r "${FROM}" root@137.184.16.45:"${DEST}"
    else
        returnError "Local file does not exist."
        return 1
    fi
}

TARGET_PATH="/root/Algorithms"

if [ $# -eq 0 ]
then
    returnError "Argument not given."
    return 1
elif [ $# -ge 1 ]
then
    if [ $1 == "--help" ] || [ $1 == "--h" ]
    then
        echo -e "List of commands from \"sendc\":\n"
        echo -e "\tsendc <Path_To_Local_File> <Path_To_Remote_File> - Sends file from local machine to remote machine (Machine path is from \"/root/Algorithms\")."
        echo -e "\tsendc -r <Path_To_Local_Dir> <Path_To_Remote_Dir> - Sends a complete directory from local machine to remote machine (Machine path is from \"/root/Algorithms\")."
        return 0
    elif [ $1 == "-r" ]
    then
        if [ $# -eq 1 ]
        then
            returnError "Neither local path or target given."
            return 1
        elif [ $# -eq 2 ]
        then
            returnError "Target not given."
            return 1
        fi
        sendd $2 $3
        return 0
    fi

    if [ $# -eq 1 ]
    then
        returnError "Target path not given."
        return 1
    fi
fi

sendf $1 $2