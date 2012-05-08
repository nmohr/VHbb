#!/usr/bin/python2.6  

import os
import math 

def getfloat_from_line( line ):
    start = line.find('.')
    number = float(line[start-1:])
    return number
    
def sum_errors( e1, e2 ):
    return math.sqrt( e1 * e1 + e2 * e2 )

def get_errors( line, sf ):
    if line.find('up') > 0:
        sf.append(getfloat_from_line(line))
    if line.find('down') > 0:
        sf.append(getfloat_from_line(line))
    return sf 

def get_correlation_matrix( file ):
    return [line.split() for line in file]

file = open('SFErrors_Pt50To100.txt','r')
stat = [0, 0, 0, 0]
dyl_btag = []
dyc_btag = []
dyb_btag = []
ttbar_btag = []
dyl_je = []
dyc_je = []
dyb_je = []
ttbar_je = []

for line in file:
#    print line

    if ( line.find('DYL') ) > 0:
        if( line.find('stat') > 0 ):
            stat[0] = getfloat_from_line(line)
        if ( line.find('btag') > 0 )  or (line.find('mistag') > 0 ):
            dyl_btag = get_errors( line, dyl_btag )
        if ( line.find('jer') > 0 ) or ( line.find('jec') > 0):
            dyl_je = get_errors( line, dyl_je )

    if ( line.find('DYC') ) > 0:
        if( line.find('stat') > 0 ):
            stat[1] = getfloat_from_line(line)
        if ( line.find('btag') > 0 )  or (line.find('mistag') > 0 ):
            dyc_btag = get_errors( line, dyc_btag )
        if ( line.find('jer') > 0 ) or ( line.find('jec') > 0):
            dyc_je = get_errors( line, dyc_je )

    if ( line.find('DYB') ) > 0:
        if( line.find('stat') > 0 ):
            stat[2] = getfloat_from_line(line)
        if ( line.find('btag') > 0 )  or (line.find('mistag') > 0 ):
            dyb_btag = get_errors( line, dyb_btag )
        if ( line.find('jer') > 0 ) or ( line.find('jec') > 0):
            dyb_je = get_errors( line, dyb_je )

    if ( line.find('TTbar') ) > 0:
        if( line.find('stat') > 0 ):
            stat[3] = getfloat_from_line(line)
        if ( line.find('btag') > 0 )  or (line.find('mistag') > 0 ):
            ttbar_btag = get_errors( line, ttbar_btag )
        if ( line.find('jer') > 0 ) or ( line.find('jec') > 0):
            ttbar_je = get_errors( line, ttbar_je )


dyl_syst = sum_errors( max(dyl_btag), max(dyl_je) )
dyc_syst = sum_errors( max(dyc_btag), max(dyc_je) )
dyb_syst = sum_errors( max(dyb_btag), max(dyb_je) )
ttbar_syst = sum_errors( max(dyl_btag), max(ttbar_je) )

print dyl_syst
print dyc_syst
print dyb_syst
print ttbar_syst

print "Final"

dyl_err = sum_errors( stat[0], dyl_syst )
dyc_err = sum_errors( stat[1], dyc_syst )
dyb_err = sum_errors( stat[2], dyb_syst )
ttbar_err = sum_errors( stat[3], ttbar_syst )

print dyl_err
print dyc_err
print dyb_err
print ttbar_err

correlation_file = open('CorrelationMatrix_Pt50To100.txt','r')
corr = get_correlation_matrix( correlation_file )
print corr

dyl_string = 'CMS_vhbb_ZjLF_SF    lnN    -    -     -    ' + str(1.+float(corr[0][0])*dyl_err) + ' ' + str(1.+(float(corr[0][1])*dyc_err)) + ' ' + str(1.+float(corr[0][2])*dyb_err) + ' ' + str(1.+float(corr[0][3])*ttbar_err) + '   -   -   -   -  '
dyc_string = 'CMS_vhbb_ZjCF_SF    lnN    -    -     -    ' + str(1.+float(corr[1][0])*dyl_err) + ' ' + str(1.+(float(corr[1][1])*dyc_err)) + ' ' + str(1.+float(corr[1][2])*dyb_err) + ' ' + str(1.+float(corr[1][3])*ttbar_err) + '   -   -   -   -  '
dyb_string = 'CMS_vhbb_ZjHF_SF    lnN    -    -     -    ' + str(1.+float(corr[2][0])*dyl_err) + ' ' + str(1.+(float(corr[2][1])*dyc_err)) + ' ' + str(1.+float(corr[2][2])*dyb_err) + ' ' + str(1.+float(corr[2][3])*ttbar_err) + '   -   -   -   -  '
ttbar_string = 'CMS_vhbb_TT_SF    lnN    -    -     -    ' + str(1.+float(corr[3][0])*dyl_err) + ' ' + str(1.+(float(corr[3][1])*dyc_err)) + ' ' + str(1.+float(corr[3][2])*dyb_err) + ' ' + str(1.+float(corr[3][3])*ttbar_err) + '   -   -   -   -  '

print dyl_string
print dyc_string
print dyb_string
print ttbar_string

