#!/bin/bash

TESTS_PATH="./tests"
RESULTS_PATH="./results"
OUTPUT_FILE="./output.txt"

find "$TESTS_PATH" -type f > "$OUTPUT_FILE"

echo -e "\nFile paths saved to $OUTPUT_FILE\n"

g++ -o main main.cpp

echo -e "Executable created"

TESTS_PASSED=0
TOTAL_TESTS=0

while IFS= read -r FILE_PATH; do
    TOTAL_TESTS=$(($TOTAL_TESTS + 1))
    echo -e "\nRunning test $TOTAL_TESTS on $FILE_PATH..."

    RESULT_PATH="${RESULTS_PATH}/$(basename "${FILE_PATH}")"

    TEST_RESULT="$(./main < "$FILE_PATH" | python ./corroborate.py "$RESULT_PATH")"
    
    if [ $TEST_RESULT == 0 ]
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

rm -f ./output.txt
rm -f ./main.exe

sleep 1

echo -e "Done!"