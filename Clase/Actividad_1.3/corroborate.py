#!/c/Python311/python

import re
import sys
import argparse

parser = argparse.ArgumentParser(description="Result assert!")
parser.add_argument("result", help="The path to the result to assert")
parser.add_argument("current", help="The path to the file that has the current result to compare")
args =parser.parse_args()

def isFormat(line):
    if re.search("^(\d\s)\d", line): return True

    return False

def getResultingLine(path):
    result_list = []
    count = 0

    with open(path, "r") as file:
        lines = file.readlines()
        for line in lines:
            # Process each line of input
            line = line.strip()

            if isFormat(line):
                result_list.append(line)

    return result_list

def main():
    file_path = args.result

    result = getResultingLine(args.current)

    with open(file_path, 'r') as file:
        lines = file.readlines()

        n_lines = []

        for line in lines:
            line = line.replace("\n", "")
            if line != "": n_lines.append(line)

        file.close()

        if n_lines == result:
            print(0)
            sys.exit(0)

    print(1)

if __name__ == "__main__":
    main()
