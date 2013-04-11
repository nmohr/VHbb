#!/usr/bin/env python
import os,sys
from time import sleep
import signal
def signal_handler(signal, frame):
        print 'ciao!'
        sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

p = sys.argv
p[0] = 'qstat'
pj = ' '.join(p)
class progbar:
    def __init__(self,width):
        self.width=width
        sys.stdout.write("\033[1;47m%s\033[1;m" % (" " * width))
        sys.stdout.flush()
        sys.stdout.write("\b" * (width+1))
    def move(self):
        sys.stdout.write("\033[1;42m \033[1;m")
        sys.stdout.flush()
def getnum():
    q=os.popen(pj)
    num=len(q.readlines())
    if num > 2: return num-2
    else: return 0
num = getnum()
print 'You have %s jobs in total'%num
progress = progbar(num)
while num > 0:
    sleep(5)
    num2 = getnum()
    diff=num-num2
    if diff > 0:
        for i in range(0,diff): progress.move()
    num=num2
print '\ndone! :)'
