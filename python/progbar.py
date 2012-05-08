import sys
class progbar:
    def __init__(self,width):
        self.width=width
        sys.stdout.write("\033[1;47m%s\033[1;m" % (" " * width))
        sys.stdout.flush()
        sys.stdout.write("\b" * (width+1)) # return to start of line, after '['
    def move(self):
        sys.stdout.write("\033[1;42m \033[1;m")
        sys.stdout.flush()
