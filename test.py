import os
import subprocess

cwd = os.getcwd()
truth_file = cwd + "/spanning_trees_count.txt"
graphs_dir = cwd + "/graphs/"
exe = cwd + "/graph.exe"

graphs_list = os.listdir(graphs_dir)

verify_lines = []
with open(truth_file) as file:
    verify_lines = file.readlines()

verify = []
for line in verify_lines:
    vals = line.split()
    pair = []
    pair.append(vals[0])
    pair.append(vals[1].rstrip())
    verify.append(pair)

verify.sort()

print("Output | Truth | Graph")
print("______________________")
for pair in verify:
    args = graphs_dir + pair[0] + ".txt"
    ret = subprocess.run([exe, args], capture_output=True)
    print(str(ret.stdout.decode('ascii')) + " | " + str(pair[1]) + " | " + str(pair[0]))
