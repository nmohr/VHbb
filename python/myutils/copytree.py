import ROOT 
from printcolor import printc
        
def copytree(pathIN,pathOUT,prefix,newprefix,file,Aprefix,Acut):

    print "##### COPY TREE - BEGIN ######"
    print "Input File : %s/%s%s.root " %(pathIN,prefix,file)
    print "Output File : %s/%s%s%s.root" %(pathOUT,newprefix,Aprefix,file)
        
    input = ROOT.TFile.Open("%s/%s%s.root" %(pathIN,prefix,file),'read')
    output = ROOT.TFile.Open("%s/%s%s%s.root" %(pathOUT,newprefix,Aprefix,file),'recreate')

    input.cd()
    obj = ROOT.TObject
    for key in ROOT.gDirectory.GetListOfKeys():
        input.cd()
        obj = key.ReadObj()
        #print obj.GetName()
        if obj.GetName() == 'tree':
            continue
        output.cd()
        #print key.GetName()
        obj.Write(key.GetName())

    inputTree = input.Get("tree")
    nEntries = inputTree.GetEntries()
    output.cd()
    print '\n\t copy file: %s with cut: %s' %(file,Acut)
    outputTree = inputTree.CopyTree(Acut)
    kEntries = outputTree.GetEntries()
    printc('blue','',"\t before cuts\t %s" %nEntries)
    printc('green','',"\t survived\t %s" %kEntries)
    outputTree.AutoSave()
    output.ls()
    print "Writing output file"
    output.Write()
    print "Closing output file"
    output.Close()
    print "Closing input file"
    input.Close()

    print "##### COPY TREE - END ######"
