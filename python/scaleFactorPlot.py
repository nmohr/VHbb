#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser
from HiggsAnalysis.CombinedLimit.DatacardParser import *
from HiggsAnalysis.CombinedLimit.ShapeTools     import *
from copy import copy,deepcopy
from numpy import matrix


def trunc(f, n):
    '''Truncates/pads a float f to n decimal places without rounding'''
    slen = len('%.*f' % (n, f))
    return str(f)[:slen]
        

def removeDouble(seq):
    seen = set()
    seen_add = seen.add
    return [ x for x in seq if x not in seen and not seen_add(x)]


def getInputSigma(options):
    opts = copy(options)
    
    file = open(opts.dc, "r")
#    os.chdir(os.path.dirname(opts.dc))
    opts.bin = True
    opts.noJMax = None
    opts.nuisancesToExclude = []
    opts.stat = False
    opts.excludeSyst = ['SF']
    DC = parseCard(file, opts)

    theSyst = {}
    nuiVar = {}
#    if not opts.bin in DC.bins: raise RuntimeError, "Cannot open find %s in bins %s of %s" % (opts.bin,DC.bins,opts.dc)
    b = DC.bins[0]
    exps = {}
    expNui = {}
    for (p,e) in DC.exp[b].items(): # so that we get only self.DC.processes contributing to this bin
        exps[p] = [ e, [] ]
        expNui[p] = [ e, [] ]
#    print DC.systs
    for (lsyst,nofloat,pdf,pdfargs,errline) in DC.systs:
        if pdf in ('param', 'flatParam'): continue
        # begin skip systematics
        skipme = False
        for xs in opts.excludeSyst:
            if not re.search(xs, lsyst): 
                skipme = True
        if skipme: continue
        # end skip systematics
        counter = 0
        for p in DC.exp[b].keys(): # so that we get only self.DC.processes contributing to this bin
            if errline[b][p] == 0: continue
            if p == 'QCD': continue
            if pdf == 'gmN':
                exps[p][1].append(1/sqrt(pdfargs[0]+1));
            elif pdf == 'gmM':
                exps[p][1].append(errline[b][p]);
            elif type(errline[b][p]) == list: 
                kmax = max(errline[b][p][0], errline[b][p][1], 1.0/errline[b][p][0], 1.0/errline[b][p][1]);
                exps[p][1].append(kmax-1.);
            elif pdf == 'lnN':
                exps[p][1].append(max(errline[b][p], 1.0/errline[b][p])-1.);
    return exps



def get_scale_factors(channel,labels,shift,v_b,input_sigma,nuisances):
    print 'Channel ' +  channel
    sf=[]
    sf_e=[]
#   correspondency_dictionary = {"TT":"TT","s_Top":"s_Top","Zj0b":"Z0b","Zj1b":"Z1b","Zj2b":"Z2b","Wj0b":"Wj0b","Wj1b":"Wj1b","Wj2b":"Wj2b","Zj1HF":"Z1b","Zj2HF":"Z2b","ZjLF":"Z0b"}
#   correspondency_dictionary = {"TT":"TT","s_Top":"s_Top","Zj0b":"Zj0b","Zj1b":"Zj1b","Zj2b":"Zj2b","Wj0b":"Wj0b","Wj1b":"Wj1b","Wj2b":"Wj2b","Zj1HF":"Z1b","Zj2HF":"Z2b","ZjLF":"Z0b","s_Top":"s_Top"}
    correspondency_dictionary = {"TT":"TT","s_Top":"s_Top","Zj0b":"Zj0b","Zj1b":"Zj1b","Zj2b":"Zj2b","Wj0b":"Wj0b","Wj1b":"Wj1b","Wj2b":"Wj2b","Zj1HF":"Z1b","Zj2HF":"Z2b","ZjLF":"Z0b","s_Top":"s_Top"}
#    print input_sigma
#    print input_sigma['TT'][1][0]
#    initial_uncertainty=0.2 # initial uncertainty. @TO FIX: this can go in a config or as input arg
    count=0
    print labels
#    channels = ['high','High','low','Low','Med','med']
#    channels = ['Zee','Zmm']
    channels = ['Zll']
    for i in v_b:
        print 'Nuisances ' + nuisances[count]
        for h in channels:
            if h in channel and h in re.sub('M','m',re.sub('L','l',re.sub('H','h',nuisances[count]))):
                print count
                try:
                    print 'Label : ' + str(labels[count])
                    print 'Relative SF : ' + i[0]
                    print 'Relative Error : ' + i[1]
                    print 'Correspondance : ' + str(correspondency_dictionary[labels[count]])
                    print 'Input sigma list : ' + str(input_sigma[correspondency_dictionary[labels[count]]])
                    print 'Input sigma value : ' + str(input_sigma[correspondency_dictionary[labels[count]]][1][0])
                    sf.append(1+input_sigma[correspondency_dictionary[labels[count]]][1][0]*eval(i[0])) # calculate the actual value for the scale factors
                    sf_e.append(input_sigma[correspondency_dictionary[labels[count]]][1][0]*eval(i[1])) # calculate the actula value for the uncertainties
                    print sf
                    print sf_e
                except:
                    print 'Problem evaluating the SF or the SF errors'
        count+=1
    print sf
    print sf_e
    return [sf,sf_e]



def getGraph(channel,labels,shift,v_b,input_sigma,x_position,y_position,nuisances):

    sf = get_scale_factors(channel,labels,shift,v_b,input_sigma,nuisances)[0]
    sf_e = get_scale_factors(channel,labels,shift,v_b,input_sigma,nuisances)[1]
    d = numpy.array(sf) # store scale factors in array
    e = numpy.array(sf_e) # store scale factors errors in array
    p = numpy.array(y_position)
    zero = numpy.array(x_position)

#    for i in range(len(labels)):
#        print 'CMSSW_vhbb_'+labels[i]+'_Zll_SF_8TeV '+ str(d[i]) + ' +/- ' + str(e[i])

    markerStyle = 20
    if ('high' in channel or 'High' in channel ):
        markerStyle = 21
    if ('med' in channel or 'Med' in channel ):
        markerStyle = 22
    if ('Zee' in channel ):
        markerStyle = 21

    for i in range(len(p)): p[i] = p[i]+shift
    print 'POSITIONS: '
    print p
    g = ROOT.TGraphErrors(n,d,p,e,zero)
    g.SetFillColor(0)
    g.SetLineColor(2)
    g.SetLineWidth(3)
    g.SetMarkerStyle(markerStyle)
    print 'Ok'
    return g




# import ROOT with a fix to get batch mode (http://root.cern.ch/phpBB3/viewtopic.php?t=3198)
hasHelp = False
for X in ("-h", "-?", "--help"):
    if X in argv:
        hasHelp = True
        argv.remove(X)
argv.append( '-b-' )
import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gSystem.Load("libHiggsAnalysisCombinedLimit.so")
argv.remove( '-b-' )
if hasHelp: argv.append("-h")

parser = OptionParser(usage="usage: %prog [options] in.root  \nrun with --help to get list of options")
parser.add_option("--vtol", "--val-tolerance", dest="vtol", default=0.30, type="float", help="Report nuisances whose value changes by more than this amount of sigmas")
parser.add_option("--stol", "--sig-tolerance", dest="stol", default=0.10, type="float", help="Report nuisances whose sigma changes by more than this amount")
parser.add_option("--vtol2", "--val-tolerance2", dest="vtol2", default=2.0, type="float", help="Report severely nuisances whose value changes by more than this amount of sigmas")
parser.add_option("--stol2", "--sig-tolerance2", dest="stol2", default=0.50, type="float", help="Report severely nuisances whose sigma changes by more than this amount")
parser.add_option("-a", "--all",      dest="all",    default=False,  action="store_true", help="Print all nuisances, even the ones which are unchanged w.r.t. pre-fit values.")
parser.add_option("-A", "--absolute", dest="abs",    default=False,  action="store_true", help="Report also absolute values of nuisance values and errors, not only the ones normalized to the input sigma")
parser.add_option("-p", "--poi",      dest="poi",    default="r",    type="string",  help="Name of signal strength parameter (default is 'r' as per text2workspace.py)")
parser.add_option("-f", "--format",   dest="format", default="text", type="string",  help="Output format ('text', 'latex', 'twiki'")
parser.add_option("-g", "--histogram", dest="plotfile", default=None, type="string", help="If true, plot the pulls of the nuisances to the given file.")
parser.add_option("--sf", "--scale-factor", dest="plotsf", default=None, type="string", help="If true, plot the scale factors in a histograms.")
parser.add_option("-D", "--datacard", dest="dc", default="", help="Datacard to be plotted")

(options, args) = parser.parse_args()
if len(args) == 0:
    parser.print_usage()
    exit(1)

file = ROOT.TFile(args[0])
if file == None: raise RuntimeError, "Cannot open file %s" % args[0]
fit_s  = file.Get("fit_s")
fit_b  = file.Get("fit_b")
prefit = file.Get("nuisances_prefit")
if fit_s == None or fit_s.ClassName()   != "RooFitResult": raise RuntimeError, "File %s does not contain the output of the signal fit 'fit_s'"     % args[0]
if fit_b == None or fit_b.ClassName()   != "RooFitResult": raise RuntimeError, "File %s does not contain the output of the background fit 'fit_b'" % args[0]
if prefit == None or prefit.ClassName() != "RooArgSet":    raise RuntimeError, "File %s does not contain the prefit nuisances 'nuisances_prefit'"  % args[0]

isFlagged = {}
table = {}
fpf_b = fit_b.floatParsFinal()
fpf_s = fit_s.floatParsFinal()
pulls = []

correlation_matrix_name=[]
correlation_matrix=[[]]

for i in range(fpf_s.getSize()):
    nuis_s = fpf_s.at(i)
    name   = nuis_s.GetName();
    nuis_b = fpf_b.find(name)
    nuis_p = prefit.find(name)
    if( name.find('SF') > 0. ):
        correlation_matrix_name.append(name)
    row = []
    flag = False;
    mean_p, sigma_p = 0,0
    if nuis_p == None:
        if not options.abs: continue
        row += [ "[%.2f, %.2f]" % (nuis_s.getMin(), nuis_s.getMax()) ]
    else:
        mean_p, sigma_p = (nuis_p.getVal(), nuis_p.getError())
        if options.abs: row += [ "%.2f +/- %.2f" % (nuis_p.getVal(), nuis_p.getError()) ]
    for fit_name, nuis_x in [('b', nuis_b), ('s',nuis_s)]:
        if nuis_x == None:
            row += [ " n/a " ]
        else:
            row += [ "%+.2f +/- %.2f" % (nuis_x.getVal(), nuis_x.getError()) ]
            if nuis_p != None:
                valShift = (nuis_x.getVal() - mean_p)/sigma_p
                if fit_name == 'b':
                    pulls.append(valShift)
                sigShift = nuis_x.getError()/sigma_p
#                print name
#                print nuis_x.getError()
#                print nuis_p.getVal()
#                print sigShift
                if options.abs:
                    row[-1] += " (%+4.2fsig, %4.2f)" % (valShift, sigShift)
                else:
                    row[-1] = " %+4.2f, %4.2f" % (valShift, sigShift)
                if (abs(valShift) > options.vtol2 or abs(sigShift-1) > options.stol2):
                    isFlagged[(name,fit_name)] = 2
                    flag = True
                elif (abs(valShift) > options.vtol  or abs(sigShift-1) > options.stol):
                    if options.all: isFlagged[(name,fit_name)] = 1
                    flag = True
                elif options.all:
                    flag = True
    row += [ "%+4.2f"  % fit_s.correlation(name, options.poi) ]
    if flag or options.all: table[name] = row
    # filling correlation table
    correlation_matrix_line=[]
    for j in range(fpf_b.getSize()):
        _nuis_b = fpf_b.at(j)
        _name   = _nuis_b.GetName();
        if name.find('SF') > 0 and ( _name.find('SF') > 0 or options.all ) :
            #          print name + '  __CORR__  ' + _name 
            #          print fit_b.correlation(name,_name)
#            print _nuis_b.getError()
#            print fit_b.correlation(name,_name)*_nuis_b.getError()
            print name
            print _name
            print fit_b.correlation(name,_name)
            correlation_matrix_line.append(trunc(fit_b.correlation(name,_name),2))
    if len(correlation_matrix_line) > 0:
        correlation_matrix.append(correlation_matrix_line)

print correlation_matrix_name
print correlation_matrix[1]
print correlation_matrix[2]
print correlation_matrix[3]
print correlation_matrix[4]

fmtstring = "%-40s     %15s    %15s  %10s"
highlight = "*%s*"
morelight = "!%s!"
pmsub, sigsub = None, None
if options.format == 'text':
    if options.abs:
        fmtstring = "%-40s     %15s    %30s    %30s  %10s"
        print fmtstring % ('name', 'pre fit', 'b-only fit', 's+b fit', 'rho')
    else:
        print fmtstring % ('name', 'b-only fit', 's+b fit', 'rho')
elif options.format == 'latex':
    pmsub  = (r"(\S+) \+/- (\S+)", r"$\1 \\pm \2$")
    sigsub = ("sig", r"$\\sigma$")
    highlight = "\\textbf{%s}"
    morelight = "{{\\color{red}\\textbf{%s}}}"
    if options.abs:
        fmtstring = "%-40s &  %15s & %30s & %30s & %6s \\\\"
        print "\\begin{tabular}{|l|r|r|r|r|} \\hline ";
        print (fmtstring % ('name', 'pre fit', '$b$-only fit', '$s+b$ fit', r'$\rho(\theta, \mu)$')), " \\hline"
    else:
        fmtstring = "%-40s &  %15s & %15s & %6s \\\\"
        print "\\begin{tabular}{|l|r|r|r|} \\hline ";
        #what = r"$(x_\text{out} - x_\text{in})/\sigma_{\text{in}}$, $\sigma_{\text{out}}/\sigma_{\text{in}}$"
        what = r"\Delta x/\sigma_{\text{in}}$, $\sigma_{\text{out}}/\sigma_{\text{in}}$"
        print  fmtstring % ('',     '$b$-only fit', '$s+b$ fit', '')
        print (fmtstring % ('name', what, what, r'$\rho(\theta, \mu)$')), " \\hline"
elif options.format == 'twiki':
    pmsub  = (r"(\S+) \+/- (\S+)", r"\1 &plusmn; \2")
    sigsub = ("sig", r"&sigma;")
    highlight = "<b>%s</b>"
    morelight = "<b style='color:red;'>%s</b>"
    if options.abs:
        fmtstring = "| <verbatim>%-40s</verbatim>  | %-15s  | %-30s  | %-30s   | %-15s  |"
        print "| *name* | *pre fit* | *b-only fit* | *s+b fit* | "
    else:
        fmtstring = "| <verbatim>%-40s</verbatim>  | %-15s  | %-15s | %-15s  |"
        print "| *name* | *b-only fit* | *s+b fit* | *corr.* |"
elif options.format == 'html':
    pmsub  = (r"(\S+) \+/- (\S+)", r"\1 &plusmn; \2")
    sigsub = ("sig", r"&sigma;")
    highlight = "<b>%s</b>"
    morelight = "<strong>%s</strong>"
    print """
<html><head><title>Comparison of nuisances</title>
<style type="text/css">
    td, th { border-bottom: 1px solid black; padding: 1px 1em; }
    td { font-family: 'Consolas', 'Courier New', courier, monospace; }
    strong { color: red; font-weight: bolder; }
</style>
</head><body style="font-family: 'Verdana', sans-serif; font-size: 10pt;"><h1>Comparison of nuisances</h1>
<table>
"""
    if options.abs:
        print "<tr><th>nuisance</th><th>pre fit</th><th>background fit </th><th>signal fit</th><th>correlation</th></tr>"
        fmtstring = "<tr><td><tt>%-40s</tt> </td><td> %-15s </td><td> %-30s </td><td> %-30s </td><td> %-15s </td></tr>"
    else:
        what = "&Delta;x/&sigma;<sub>in</sub>, &sigma;<sub>out</sub>/&sigma;<sub>in</sub>";
        print "<tr><th>nuisance</th><th>background fit<br/>%s </th><th>signal fit<br/>%s</th><th>&rho;(&mu;, &theta;)</tr>" % (what,what)
        fmtstring = "<tr><td><tt>%-40s</tt> </td><td> %-15s </td><td> %-15s </td><td> %-15s </td></tr>"

names = table.keys()
names.sort()
highlighters = { 1:highlight, 2:morelight };
for n in names:
    v = table[n]
    if options.format == "latex": n = n.replace(r"_", r"\_")
    if pmsub  != None: v = [ re.sub(pmsub[0],  pmsub[1],  i) for i in v ]
    if sigsub != None: v = [ re.sub(sigsub[0], sigsub[1], i) for i in v ]
    if (n,'b') in isFlagged: v[-3] = highlighters[isFlagged[(n,'b')]] % v[-3]
    if (n,'s') in isFlagged: v[-2] = highlighters[isFlagged[(n,'s')]] % v[-2]
    if options.abs:
       print fmtstring % (n, v[0], v[1], v[2], v[3])
    else:
       print fmtstring % (n, v[0], v[1], v[2])

if options.format == "latex":
    print " \\hline\n\end{tabular}"
elif options.format == "html":
    print "</table></body></html>"

if options.plotfile:
    import ROOT
    ROOT.gROOT.SetStyle("Plain")
    ROOT.gStyle.SetOptFit(1)
    histogram = ROOT.TH1F("pulls", "Pulls", 60, -3, 3)
    for pull in pulls:
        histogram.Fill(pull)
    canvas = ROOT.TCanvas("asdf", "asdf", 800, 800)
    histogram.GetXaxis().SetTitle("pull")
    histogram.SetTitle("Post-fit nuisance pull distribution")
    histogram.SetMarkerStyle(20)
    histogram.SetMarkerSize(2)
    #histogram.Fit("gaus")
    histogram.Draw("pe")
    canvas.SaveAs(options.plotfile)


########### SCALE FACTOR PLOT ###############
## If you fit scale factors this part of   ##
## will create a plt reading from the      ##
## nuisances. All the nuisance cointaning  ##
## "SF" in their name will be plotted      ##
#############################################

import numpy
if options.plotsf and options.dc:
    n=0
    labels=[]
    v_s=[] # dX/sigma_in values
    v_b=[] # sigma_out/sigma_in values
    rho=[] # rho
    sys=[] # systematics. Not properly filled yet
    x_position=[] # x position in the plot, basically the SF value
    y_position=[] # y position in the plot. @TO IMPLEMENT: According to the number of entries per background the spacing is different.
    #!! loop on all the nuisances
    for name in names:
        #!! take only the nuisances which have SF in their name
        if ('SF' in name ):
            print name
            labels.append(name)
            n+=1
            #!! take the values
            #!! the usual order is: dX/sigma_in for background only - sigma_out/sigma_in for background only - dX/sigma_in for background+signal - sigma_out/sigma_in for background+signal - rho
            v = table[name] 
            #!! forget about the flag
            v = [ re.sub('!','',i) for i in v ]
            v = [ re.sub('\*','',i) for i in v ]
            if pmsub  != None: v = [ re.sub(pmsub[0],  pmsub[1],  i) for i in v ]
            if sigsub != None: v = [ re.sub(sigsub[0], sigsub[1], i) for i in v ]
            v_b.append(v[0].split(','))
            v_s.append(v[1].split(','))
            rho.append(v[2].split(','))
            x_position.append(0.)
            y_position.append(n-1.)
            sys.append(0.1) #@TO FIX: need to decide how to quote the systematics and where to take them from

    # count the number of different channels
    channels = [0.,0.,0.,0.,0.]
    ch={'Zll':0.,'Zll low Pt':0.,'Zll high Pt':0.,'Wln':0.,'Wln low Pt':0.,'Wln high Pt':0.,'Znn':0.,'Znn low Pt':0.,'Znn high Pt':0.,'Znn med Pt':0.,'Zee':0.,'Zmm':0.}
    print labels
    for label in labels:
        #!! create channel list and labels for legend
        if label.find('Zee') > 0. :
                ch['Zee'] = 1.
        if label.find('Zmm') > 0. :
                ch['Zmm'] = 1.
        if label.find('Zll') > 0. :
            if label.find('lowPt') > 0.:
                ch['Zll low Pt'] = 1.
            elif label.find('highPt') > 0.:
                ch['Zll high Pt'] = 1.
            else:
                ch['Zll'] = 1.
        if label.find('Wln') > 0. :
            if label.find('lowPt') > 0.:
                ch['Wln low Pt'] = 1.
            elif label.find('highPt') > 0.:
                ch['Wln high Pt'] = 1.
            else:
                ch['Wln'] = 1.
        if label.find('Znunu') > 0. :
            if label.find('LowPt') > 0.:
                ch['Znunu low Pt'] = 1.
            elif label.find('MedPt') > 0.:
                ch['Znunu med Pt'] = 1.
            elif label.find('HighPt') > 0.:
                ch['Znunu high Pt'] = 1.
            else:
                ch['Znunu'] = 1.

    # calculate the shift on the y position
    shift=0.
    for channel,active in ch.iteritems(): shift+=active;
    shift=1./(shift+1)

    #shift the elements in the array
#    for i in range(0,len(y_position)): y_position[i]+=shift

    print 'Y_POSITION' 
    print y_position
    # clean the labels
    nuisances = labels
    labels = [re.sub('CMS_vhbb_','',label) for label in labels ]
    try:
        labels = [re.sub('_Zll_SF_','',label) for label in labels ]
        labels = [re.sub('_Wln_SF_','',label) for label in labels ]
        labels = [re.sub('_Zee_SF_','',label) for label in labels ]
        labels = [re.sub('_Zmm_SF_','',label) for label in labels ]                
        labels = [re.sub('_SF_Znunu','',label) for label in labels ]
        labels = [re.sub('lowPt_8TeV','',label) for label in labels ]
        labels = [re.sub('highPt_8TeV','',label) for label in labels ]
        labels = [re.sub('medPt_8TeV','',label) for label in labels ]
        labels = [re.sub('_Zll_lowPt_SF_8TeV','',label) for label in labels ]
        labels = [re.sub('_Zll_highPt_SF_8TeV','',label) for label in labels ]
        labels = [re.sub('_LowPt','',label) for label in labels ]
        labels = [re.sub('_HighPt','',label) for label in labels ]
        labels = [re.sub('LowPt_8TeV','',label) for label in labels ]
        labels = [re.sub('MedPt_8TeV','',label) for label in labels ]
        labels = [re.sub('HighPt_8TeV','',label) for label in labels ]
        labels = [re.sub('8TeV','',label) for label in labels ]
        labels = [re.sub('8TeV','',label) for label in labels ]
    except:
        print '@WARNING: No usual naming for datacard scale factors nuisances'
        print labels

#CMS_vhbb_TT_Zll_SF_8TeV                       ! +0.56, 0.13!     ! +0.54, 0.13!       -0.00
#CMS_vhbb_ZjHF_Zll_SF_8TeV                        +1.79, 1.14        +1.80, 1.13       +0.00
#CMS_vhbb_ZjLF_Zll_SF_8TeV                     ! +3.51, 0.94!     ! +3.42, 0.95!       -0.00

    print n
    print labels
    print v_s
    print v_b
    print rho

    label_dictionary = {"TT":"t#bar{t}","ZjHF":"Z+bX","ZjLF":"Z+udscg","Zj1HF":"Z+b","Zj2HF":"Z+b#bar{b}","Wj0b":"W+light","Wj1b":"W+b","Wj2b":"W+b#bar{b}","Zj0b":"Z+light","Zj1b":"Z+b","Zj2b":"Z+b#bar{b}","s_Top":"t"}
    c = ROOT.TCanvas("c","c",600,600)

    input_sigma = getInputSigma(options)
    print 'Input sigma'
    print input_sigma

    graphs={}
    j=1
    for channel,active in ch.iteritems():
        print channel
        print active
        if active > 0.:
            graphs[channel] = getGraph(channel,labels,j*shift,v_b,input_sigma,x_position,y_position,nuisances) # create the graph with the scale factors
            j+=1
            
    print graphs

    labels = removeDouble(labels)
    n= len(labels)
    h2 = ROOT.TH2F("h2","",1,0.,2.5,n,0,n) # x min - max values. 
    h2.GetXaxis().SetTitle("Scale factor")
    
    for i in range(n):
        h2.GetYaxis().SetBinLabel(i+1,label_dictionary[labels[i]])

    
    drawSys=False
    if(drawSys):
        #for the moment just random systematics
        sys_e = numpy.array(sys)
        #!! Create the graph for the systematics, if any. It will show only error brackets, no points
        g2 = ROOT.TGraphErrors(n,d,p,sys_e,zero)
        g2.SetFillColor(0)
        g2.SetLineWidth(3);
    
    h2.Draw(); ROOT.gStyle.SetOptStat(0);
    h2.GetXaxis().SetTitleSize(0.04);
    h2.GetXaxis().SetLabelSize(0.04);
    h2.GetYaxis().SetLabelSize(0.06);
    #h2.SetFillStyle(4000)
    c.SetFillStyle(4000)
    
    globalFitBand = ROOT.TBox(1.0, 0., 1.5, n);
    globalFitBand.SetFillStyle(3013);
    globalFitBand.SetFillColor(65);
    globalFitBand.SetLineStyle(0);
    #globalFitBand.Draw("same");
    globalFitLine = ROOT.TLine(1.0, 0., 1.0, n);
    globalFitLine.SetLineWidth(2);
    globalFitLine.SetLineColor(214);#214
    globalFitLine.Draw("same");

    #!! Legend
    l2 = ROOT.TLegend(0.70, 0.85,0.85,0.75)
    l2.SetLineWidth(2)
    l2.SetBorderSize(0)
    l2.SetFillColor(0)
    l2.SetFillStyle(4000)
    l2.SetTextFont(62)
    for channel,g in graphs.iteritems():
        print channel
        l2.AddEntry(g,channel,"pl")
    #l2.AddEntry(g,"Stat.","l")
    if(drawSys) : l2.AddEntry(g2,"Syst.","l")
    l2.SetTextSize(0.035)
#    l2.SetNColumns(3)
    l2.Draw("same")

    for channel,g in graphs.iteritems():
        print channel
        g.Draw("P same")
    if(drawSys) : g2.Draw("[] same")
    ROOT.gPad.SetLeftMargin(0.2)
    ROOT.gPad.Update()
    c.Print("histo.pdf")





