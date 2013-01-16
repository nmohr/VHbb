def printc(fg,bg,text):
    pre, post = makefix(3,fg)
    one, two = makefix(4,bg)
    pre+=one
    post+=two
    print pre+text+post
    
def makefix(first,color):
    if color == 'black': id=0
    elif color == 'red': id=1
    elif color == 'green': id=2
    elif color == 'yellow': id=3
    elif color == 'blue': id=4
    elif color == 'magenta': id=5
    elif color == 'cyan': id=6
    elif color == 'white': id=7
    else:
        first =0
    if first !=0:
        pre='\033[1;%s%sm'%(first,id)
        post='\033[1;m'
    else:
        pre=''
        post=''
    return pre, post
