#!/usr/bin/env python
import ROOT
from optparse import OptionParser
import sys
import itertools
ROOT.gROOT.SetBatch(True)

argv = sys.argv
parser = OptionParser()
parser.add_option("-F", "--input-file", dest="input", default="",
                      help="input file")
parser.add_option("-T", "--test", dest="test", default=False,
                      help="run as test on 100 events")

(opts, args) = parser.parse_args(argv)
test=eval(opts.test)

def _is_already_there(list,event):
    if event in list: return True
    else: return False

def _fill_event(input):
    f = ROOT.TFile.Open(input,'read')
    f.ls()
    t = f.Get('tree')

    event = t.GetBranch('EVENT')
    event_list=[]
    duplicate_event=[]
    
    for i in range(0,t.GetEntries()):
        if i > 100 & test: continue
        if not i%10000: print i

        event.GetEntry(i)
        Event = [t.event,t.run,t.lumi]
        if(t.GetEntries() < 1000):
            if(_is_already_there(event_list,Event)):
                duplicate_event.append(Event)
        event_list.append(Event)

    print 'Duplicated events list: '
    print duplicate_event
    return event_list


def main():
    input = opts.input
    print input
    eventlist = _fill_event(input)
    eventlist.sort()
    newlist = list(k for k,_ in itertools.groupby(eventlist))
    print '| ---------------------------------------------- |'
    print '| Results                                        |'
    print '| ---------------------------------------------- |'
    print '| Number of tested events: ' + str( len(eventlist) )
    print '| Number of duplicated events: ' + str( len(eventlist) - len(newlist) )
    print '| ---------------------------------------------- |'
    
if __name__ == '__main__': main()
