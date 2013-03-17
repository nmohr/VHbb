#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

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
for i in range(fpf_s.getSize()):
    nuis_s = fpf_s.at(i)
    name   = nuis_s.GetName();
    nuis_b = fpf_b.find(name)
    nuis_p = prefit.find(name)
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
if options.plotsf:
    n=0
    labels=[]
    v_s=[] # dX/sigma_in values
    v_b=[] # sigma_out/sigma_in values
    rho=[] # rho
    sys=[] # systematics. Not properly filled yet
    x_position=[] # x position in the plot, basically the SF value
    y_position=[] # y position in the plot. @TO IMPLEMENT: According to the number of entries per background the spacing is different.
    # loop on all the nuisances
    for name in names:
        # take only the nuisances which have SF in their name
        if ('SF' in name ):
            print name
            labels.append(name)
            n+=1
            # Take the values
            # The usual order is: dX/sigma_in for background only - sigma_out/sigma_in for background only - dX/sigma_in for background+signal - sigma_out/sigma_in for background+signal - rho
            v = table[name] 
            # forget about the flag
            v = [ re.sub('!','',i) for i in v ]
            if pmsub  != None: v = [ re.sub(pmsub[0],  pmsub[1],  i) for i in v ]
            if sigsub != None: v = [ re.sub(sigsub[0], sigsub[1], i) for i in v ]
            v_b.append(v[0].split(','))
            v_s.append(v[1].split(','))
            rho.append(v[2].split(','))
            x_position.append(0.)
            y_position.append(n-1.)
            sys.append(0.1) # need to decide how to quote the systematics and where to take them from

    # count the number of different channels
    channels = [0.,0.,0.]
    print labels
    for label in labels:
        if label.find('Zll') > 0. : channels[0] = 1.
        if label.find('Wln') > 0. : channels[1] = 1.
        if label.find('Znn') > 0. : channels[2] = 1.
    # calculate the shift on the y position
    shift=0.
    for channel in channels: shift+=channel;
    print shift
    shift=1./(shift+1)
    print shift
    #shift the elements in the array
    for i in range(0,len(y_position)): y_position[i]+=shift
    print y_position
    # clean the label
    labels = [re.sub('CMS_vhbb_','',label) for label in labels ]
    try:
        labels = [re.sub('_Zll_SF_8TeV','',label) for label in labels ]
        labels = [re.sub('_Wln_SF_8TeV','',label) for label in labels ]
        labels = [re.sub('_Znn_SF_8TeV','',label) for label in labels ]
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
    sf=[]
    sf_e=[]
    initial_uncertainty=0.2 # initial uncertainty. @TO FIX: this can go in a config or as input arg
    for i in v_b:
        try:
            sf.append(1+initial_uncertainty*eval(i[0])) # calculate the actual value for the scale factors
            sf_e.append(initial_uncertainty*eval(i[1])) # calculate the actula value for the uncertainties
        except:
            print 'Problem evaluating the SF or the SF errors'
    print sf
    print sf_e
    c = ROOT.TCanvas("c","c",600,600)


    label_dictionary = {"TT":"t#bar{t}","ZjHF":"Z+b#bar{b}","ZjLF":"Z+udscg"}
#labels = ["W+udscg","W+b#bar{b}","Z+udscg","Z+b#bar{b}","t#bar{t}"]
    #d = numpy.array([0.94, 1.72, 1.10,1.08,1.01])
    d = numpy.array(sf)
    #e = numpy.array([0.02,0.16,0.02,0.04,0.02])
    e = numpy.array(sf_e)
    #for the moment just random systematics
    sys_e = numpy.array(sys)
    #TO FIX: Y position of the point. 
    p = numpy.array(y_position)
    zero = numpy.array(x_position)

    h2 = ROOT.TH2F("h2","",1,0.7,2.2,n,0,n)
    h2.GetXaxis().SetTitle("Scale factor")
    
    for i in range(n):
        h2.GetYaxis().SetBinLabel(i+1,label_dictionary[labels[i]])

    g = ROOT.TGraphErrors(n,d,p,e,zero)
    g.SetFillColor(0)
    g.SetLineColor(2)
    g.SetLineWidth(3)
    g.SetMarkerStyle(21)

    g2 = ROOT.TGraphErrors(n,d,p,sys_e,zero)
    g2.SetFillColor(0)
    #g2.SetLineColor(2);
    g2.SetLineWidth(3);
    g2.SetMarkerStyle(21);
    
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
    
    #l2 = ROOT.TLegend(0.5, 0.82,0.92,0.95)
    l2 = ROOT.TLegend(0.55, 0.85,0.85,0.87)
    l2.SetLineWidth(2)
    l2.SetBorderSize(0)
    l2.SetFillColor(0)
    l2.SetFillStyle(4000)
    l2.SetTextFont(62)
    l2.AddEntry(g,"SF","p")
    l2.AddEntry(g,"Stat.","l")
    l2.AddEntry(g2,"Syst.","l")
    l2.SetTextSize(0.035)
    l2.SetNColumns(3)
    l2.Draw("same")
    
    g.Draw("P same")
    g2.Draw("[] same")
    ROOT.gPad.SetLeftMargin(0.2)
    ROOT.gPad.Update()
    c.Print("histo.pdf")

