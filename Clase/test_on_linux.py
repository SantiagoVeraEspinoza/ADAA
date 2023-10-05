import os
import sys
import re
import argparse
import paramiko

parser = argparse.ArgumentParser()
parser.add_argument('dir', help="Specify the starting dir")
args = parser.parse_args()

CWD = ""
TEST_PATH = ""

try: 
    CWD = os.path.abspath(args.dir)
    TEST_PATH = os.path.join(CWD, "test_main.sh")

    if not os.path.exists(TEST_PATH):
        print("Error, bad dir config!")
        sys.exit(1)
    if not os.path.isdir(CWD):
        print("Invalid Path!")
        sys.exit(1)
except Exception as exp:
    print(exp)
    sys.exit(1)

list_top = os.listdir(CWD)

if not ("tests" in list_top and "results" in list_top and "corroborate.py" in list_top and "test_main.sh" in list_top and "main.cpp" in list_top): 
    print("Error, bad dir config!")
    sys.exit(1)

DIR_NAME = CWD.split("\\")[-1]
CWD = CWD.replace("\\", "/")

ssh_client = paramiko.SSHClient()
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

hostname = '137.184.16.45'
port = 22
username = 'root'

ssh_client.connect(hostname, port, username)

print("\nConected to dev machine!")

sftp = ssh_client.open_sftp()

remote_directory = "/root/Algorithms/"

def upload_directory(local_path, remote_path):
    for item in os.listdir(local_path):
        local_item = local_path + "/" + item
        remote_item = remote_path + "/" + item
        
        if os.path.isfile(local_item):
            sftp.put(local_item, remote_item)
        elif os.path.isdir(local_item):
            try:
                sftp.mkdir(remote_item)
            except IOError:
                pass  # Directory already exists
            upload_directory(local_item, remote_item)

ssh_client.exec_command(f'mkdir -p {remote_directory + DIR_NAME}')

upload_directory(CWD, remote_directory + DIR_NAME)

print("\nCreated source dir!")

command = "chmod 777 " + remote_directory + DIR_NAME + "/corroborate.py"
stdin, stdout, stderr = ssh_client.exec_command(command)

print("\nExecuting tests!")

command = "source " + remote_directory + DIR_NAME + "/test_main.sh"
stdin, stdout, stderr = ssh_client.exec_command(command)

print("\nLinux result:\n")
print(re.search(r"\<-\>\s.+\s\<-\>", stdout.read().decode()).group())

sftp.close()
ssh_client.close()