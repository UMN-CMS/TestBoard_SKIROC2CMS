#
import sys
import os
import math
import os.path

fname = raw_input("Enter data file name: ")
if os.path.isfile(fname) != True:
	print "Data file not found" + fname
	exit(0)
	
fin = open(fname,"r")

# number of channels (high and low gain) and number of samples
NCH = 128
NSS = 13

DEBUGCH = 9999
DEBUGS = 9999

# data probably bad if higher than:
CUTHIGH = 300

# arrays needed to carry out std dev calculation
n    = [[[0 for y in range (NSS)] for z in range(NCH)] for chip in range(4)]
s    = [[[0 for y in range (NSS)] for z in range(NCH)] for chip in range(4)]
sofq = [[[0.0 for y in range (NSS)] for z in range(NCH)] for chip in range(4)]
avg  = [[[0.0 for y in range (NSS)] for z in range(NCH)] for chip in range(4)]
stdv = [[[0.0 for y in range (NSS)] for z in range(NCH)] for chip in range(4)]
avgavg = [[0.0 for z in range(NCH)] for chip in range(4)]
avgstdev = [[0.0 for z in range(NCH)] for chip in range (4)]

# remove first header lines
configtext = fin.readline()
configline = fin.readline()
neventsline = fin.readline()
runline = fin.readline()
separatorline = fin.readline()

els = neventsline.split()
nevents = int(els[4])

for i in range(0,nevents):
	for chip in range(0,4):
		header = fin.readline()
		#print "Header: ",header
		
		# some gymnastic to get the SK2 roll mask in the right representation
		hrollmask = header.split()[5]
		rollmask = int(hrollmask,16)
		chip = header.split()[3]
		chip = int(chip)
		hrollmask = bin(rollmask)
		hrollmask = hrollmask[2:]
		hrollmask = hrollmask[::-1]
		l = len(hrollmask)
	
		idx1 = -1
		idx2 = -1
		for k in range(0,l):
			if(hrollmask[k] != '0' and idx1 < 0):
				idx1 = k
			if(hrollmask[k] != '0' and idx1 >=0):
				idx2 = k
		
		els = [0 for x in range(NSS)]
		for ch in range(0,NCH):
			l = fin.readline()
			sels = l.split()
			for ns in range(0,NSS):
				x = int(sels[ns])
				if(ns != idx1 and ns != idx2):
					if(x > CUTHIGH):
						pass
	#					print "Eliminated ",i, ch, ns, x
					else:
						s[chip][ch][ns] = s[chip][ch][ns] + x
						n[chip][ch][ns] = n[chip][ch][ns] + 1
						if(ch == DEBUGCH and ns == DEBUGS):
							print "### ",x

print "Computing Averages",
for chip in range(0,4):
	print " chip ",chip,
	for ns in range(0,NSS):
		for ch in range(0,NCH):
			avg[chip][ch][ns] = float(s[chip][ch][ns]) / float(n[chip][ch][ns])
			avgavg[chip][ch]=avgavg[chip][ch]+avg[chip][ch][ns]/float(NSS)
#			print "avgavg = ", chip, ch, avgavg[chip][ch]

n = [[[0 for y in range (NSS)] for z in range(NCH)] for chip in range(4)]

print "\nComputing Standard Deviation"

fin.seek(0)
# remove first 4 header lines
dmy = fin.readline()
dmy = fin.readline()
dmy = fin.readline()
dmy = fin.readline()
dmy = fin.readline()
for i in range(0,nevents):
	for chip in range(0,4):
		header = fin.readline()
	#	print "****** ",header

		hrollmask = header.split()[5]
		rollmask = int(hrollmask,16)
		chip = header.split()[3]
		chip = int(chip)
		hrollmask = bin(rollmask)
		hrollmask = hrollmask[2:]
		hrollmask = hrollmask[::-1]
		l = len(hrollmask)

		idx1 = -1
		idx2 = -1
		for k in range(0,l):
			if(hrollmask[k] != '0' and idx1 < 0):
				idx1 = k
			if(hrollmask[k] != '0' and idx1 >=0):
				idx2 = k
	#	print "invalid data at pos ",idx1, idx2
		els = [0 for x in range(NSS)]
		for ch in range(0,NCH):
			l = fin.readline()
			sels = l.split()
			for ns in range(0,NSS):
				els[ns] = int(sels[ns])
				if(ns != idx1 and ns != idx2):
					if(els[ns] > CUTHIGH):
						print "Eliminated ",i, ch, ns, els[ns]
						pass
					else:
						sofq[chip][ch][ns] = sofq[chip][ch][ns] + (els[ns]-avg[chip][ch][ns])*(els[ns]-avg[chip][ch][ns])
						n[chip][ch][ns] = n[chip][ch][ns] + 1
						if(ch == DEBUGCH and ns == DEBUGS):
							print "=== ",(els[ns]-avg[chip][ch][ns])*(els[ns]-avg[chip][ch][ns]), els[ns], avg[chip][ch][ns]
for chip in range(0,4):
	for ch in range(0,NCH):
		for ns in range(0,NSS):
			sofq[chip][ch][ns] = math.sqrt(sofq[chip][ch][ns] / float(n[chip][ch][ns]))
			avgstdev[chip][ch] = avgstdev[chip][ch] + sofq[chip][ch][ns]/float(NSS)

fname = "ANA_" + fname 

print "Done, look at results in file: ",fname

fout = open(fname,"w")
nchip = 0
for chip in n:
	fout.write('Chip :%d\n Good samples per channel-column' % (nchip))
	for e in chip:
		fout.write('%s\n' % (e))
	nchip= nchip +1

nchip = 0
fout.write("\n\n SUM\n")
for chip in s:
	fout.write('Chip :%d\n' % (nchip))
	for e in chip:
		fout.write('%s\n' % (e))
	nchip= nchip +1

nchip = 0
fout.write("\n\n AVERAGES\n")
for chip in avg:
	fout.write('Chip :%d\n' % (nchip))
	for e in chip:
		for r in e:
			fout.write('%.2f ' %  (r))
		fout.write("\n")
	nchip= nchip +1

nchip = 0
fout.write("\n\n STANDARD DEVIATIONS\n")
for chip in sofq:
	fout.write('Chip :%d\n'  % (nchip))
	for e in chip:
		for r in e:
			fout.write('%4.2f ' % (r))
		fout.write("\n")
	nchip= nchip +1

# Dave
# Open another file and store summary - average pedestal and average stddev for each channel
# To do this, I need a lookup table for chip/channel to cell
# 

fLookupTable = open("Skiroc2CMS_sensor_map_simplified.csv","r")

# Number of channels on the sensor
NCHAN = 127

# arrays for chip number and chip channel number
nchip = [0 for chip in range(NCHAN)]
nchipchan = [0 for chip in range(NCHAN)] 

# remove first header line
titles = fLookupTable.readline()

fname = "AVG_" + fname
fout = open(fname,"w")
for i in range(0,NCHAN):
        l = fLookupTable.readline()
        sels = l.split(",")
        nchip[i] = int(sels[1])
        nchipchan[i] = int(sels[2])
        print "Low gain: i, sensorchan, chip, chipchan ", i, int(sels[0]), nchip[i], nchipchan[i]
	print "Low gain: avgavg, avgstdev = ", avgavg[nchip[i]][nchipchan[i]], avgstdev[nchip[i]][nchipchan[i]]
	fout.write('%.2f %.2f ' % (avgavg[nchip[i]][nchipchan[i]], avgstdev[nchip[i]][nchipchan[i]]))
	fout.write("\n")

fLookupTable.seek(0)
titles = fLookupTable.readline()
for i in range(0,NCHAN):
        l = fLookupTable.readline()
        sels = l.split(",")
        nchip[i] = int(sels[1])
        nchipchan[i] = int(sels[2])
        print "High gain: i, sensorchan, chip, chipchan ", i, int(sels[0]), nchip[i], nchipchan[i]+64
	print "High gain: avgavg, avgstdev = ", avgavg[nchip[i]][nchipchan[i]+64], avgstdev[nchip[i]][nchipchan[i]+64]
	fout.write('%.2f %.2f ' % (avgavg[nchip[i]][nchipchan[i]+64], avgstdev[nchip[i]][nchipchan[i]+64]))
	fout.write("\n")

                                               
