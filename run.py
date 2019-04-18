from subprocess import Popen, PIPE
import os
import re
import numpy as np
import sys

times = []
if len(sys.argv) < 2:
    print("Provide the number of runs")
else:
    for i in range(0, int(sys.argv[1])):
        process = Popen([os.getcwd() + '/build/src/simulator', os.getcwd() + '/build/tests/queens/queens.elf'], stdout=PIPE)
        (output, err) = process.communicate()
        m = re.search('Simulation speed is ([+-]?([0-9]*[.])?[0-9]+)', output.decode("utf-8"))
        exit_code = process.wait()
        times.append(m.group(1))
    print ("The mean accuracy after", sys.argv[1], "runs is", "{:7.4f}".format(np.mean(np.array(times).astype(np.float))),\
           "and the standard deviation is ", "{:6.4f}".format(np.std(np.array(times).astype(np.float))))
    if len(sys.argv) == 3 and sys.argv[2] == "-v":
        print (times)
