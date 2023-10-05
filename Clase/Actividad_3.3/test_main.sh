#!/bin/bash

SRC_DIR=$(dirname "${BASH_SOURCE[0]}")

TESTS_PATH="${SRC_DIR}/tests"
RESULTS_PATH="${SRC_DIR}/results"
OUTPUT_FILE="${SRC_DIR}/output.txt"

echo "Sourced directory: $sourced_directory"

find "$TESTS_PATH" -type f > "$OUTPUT_FILE"

echo $(find "$TESTS_PATH" -type f)

echo -e "\nFile paths saved to $OUTPUT_FILE\n"

g++ -std=c++11 -o ${SRC_DIR}/main ${SRC_DIR}/main.cpp

echo -e "Executable created"

TESTS_PASSED=0
TOTAL_TESTS=0

while IFS= read -r FILE_PATH; do
    TOTAL_TESTS=$(($TOTAL_TESTS + 1))
    echo -e "\nRunning test $TOTAL_TESTS on $FILE_PATH..."

    RESULT_PATH="${RESULTS_PATH}/$(basename "${FILE_PATH}")"

    ${SRC_DIR}/main < "$FILE_PATH" > "${SRC_DIR}/cpp_output.txt"
    ASSERT_RESULT="$(python ${SRC_DIR}/corroborate.py "${RESULT_PATH}" ${SRC_DIR}/cpp_output.txt)"
    rm -f ${SRC_DIR}cpp_output.txt
    
    if [ $ASSERT_RESULT -eq 0 ]
    then
        echo "Test passed!"
        TESTS_PASSED=$(($TESTS_PASSED + 1))
    else
        echo "Test failed!"
    fi

    sleep 2
done < "$OUTPUT_FILE"

echo -e "\n<-> Passed ${TESTS_PASSED} out of ${TOTAL_TESTS} - ${TESTS_PASSED}/${TOTAL_TESTS} <->\n"

echo -e "Deleting residual...\n"

rm -f ${SRC_DIR}/output.txt
rm -f ${SRC_DIR}/cpp_output.txt
rm -f ${SRC_DIR}/main.exe

sleep 1

echo -e "Done!"