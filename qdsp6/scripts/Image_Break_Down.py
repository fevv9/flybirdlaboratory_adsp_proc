import os
import re
import sys
import shutil
import csv
interFlag = 0
LibAccum=0
LibBaseAddrDec = 0
LibName = 0
TextCheckFlag = 0
RodataCheckFlag = 0
DataCheckFlag = 0
SdataCheckFlag = 0
SbssCheckFlag = 0
BssCheckFlag = 0
DevList = []
DevIndex = 0
hash =  dict([])
libhash = {}
libhash1 = {}
comphash = {}
lines = {}
TextIndex = 0
RodataIndex = 1
DataIndex = 2
SdataIndex = 3
SbssIndex = 4
BssIndex = 5
CompIndex = 0
Textflag = 0
Rodataflag = 0
Dataflag = 0
Sdataflag = 0
Sbssflag = 0
Bssflag = 0
islandflag = 0
crmexe = 0
arg_len=len(sys.argv)
#print arg_len
if arg_len > 5:
    msmchipset=sys.argv[1]
    mapfile=sys.argv[2]
    PDType=sys.argv[3]
    toolsUsed=int(sys.argv[4])
    Location=sys.argv[5]
    BuildStatus=sys.argv[6]
    MemLocation=sys.argv[7]
    crmexe=1
else:
    msmchipset=sys.argv[1]
    mapfile=sys.argv[2]
    PDType=sys.argv[3]
    toolsUsed=int(sys.argv[4])
infile = open("%s" % mapfile, 'r')
if crmexe:
   csvout = csv.writer(open("%s\\Memory_info_%s_%s.csv" % (MemLocation,msmchipset,BuildStatus), "wb"))
else:
   csvout = csv.writer(open("Memory_info_%s_%s.csv" % (msmchipset,PDType), "wb"))
lines = infile.readlines()			
line_number = 0
while line_number < len(lines):
    to_line = lines[line_number]
    line_number += 1
    start=re.search('^.start\s+(\w+)\s+(\w+)', to_line)
    if start:
         StartBase=start.group(1)
         StartSize=start.group(2)
    init=re.search('^.init\s+(\w+)\s+(\w+)', to_line)
    if init:
         InitBase=init.group(1)
         InitSize=init.group(2)
    plt=re.search('^.plt\s+(\w+)\s+(\w+)', to_line)
    if plt:
         PltBase=plt.group(1)
         PltSize=plt.group(2)
    text=re.search('^.text\s+(\w+)\s+(\w+)', to_line)
    if text:
         TextBase=text.group(1)
         TextSize=text.group(2)
         TextBaseDec=int(TextBase, 16)
         TextSizeDec=int(TextSize, 16)
         TextOverallSize=TextBaseDec+TextSizeDec
         line_number=line_number
         while TextBaseDec < TextOverallSize:
                 line_number=line_number+1
                 textLine=lines[line_number]
                 nextsec=re.search('^\.(\w+)\s+(\w+)\s+(\w+)', textLine)
                 if not nextsec:
                        nextsec=re.search('^\.(\w+.\w+)\s+(\w+)\s+(\w+)', textLine)
                        if not nextsec:
                               nextsec=re.search('^(\w+.\w+)\s+(\w+)\s+(\w+)', textLine) 
                 FirstPattern=re.search('\.\w+\.\w+\n',textLine)
                 SecondPattern=re.search('\.\w+\.\w+\.\w+\n',textLine)				 	
                 if FirstPattern or SecondPattern:
                       line_number=line_number+1
                       ScanLine=lines[line_number]
                       CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)
                       if not CommonPattern:
                            CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)
                            if not CommonPattern:
                                CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)									   
                                if not CommonPattern:                            
                                   CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   
                                   if not CommonPattern:                            
                                      CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)									  
                       if CommonPattern:
                                  LibBaseAddr=CommonPattern.group(1)
                                  LibSize=CommonPattern.group(2)
                                  LibLevelComp=CommonPattern.group(3)
                                  LibLevel2Comp=CommonPattern.group(4)
                                  LibName=CommonPattern.group(5)
                                  LibBaseAddrDec=int(LibBaseAddr, 16)
                                  if TextCheckFlag == 0:
                                        TextCheckFlag = 1
                                        TextAlignHole=LibBaseAddrDec-TextBaseDec
                                        if TextAlignHole != 0:
                                              TextAlignName="Text_Align"
                                              libhash[TextAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash1[TextAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash[TextAlignName][TextIndex] = TextAlignHole
                                              libhash1[TextAlignName][CompIndex] = TextAlignName
                                  LibSizeDec=int(LibSize, 16)
                                  if Textflag == 1:		
                                        if not LibNamePrev in libhash:
                                            libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]											
                                            libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                            if LibBaseAddrDec != 0:											
                                                libhash[LibNamePrev][TextIndex] = libhash[LibNamePrev][TextIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                                Comp1 = 'Qualcomm'
                                                Comp2 = 'avs'
                                                Comp3 = 'core'
                                                Comp4 = 'Sensors'
                                                if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                        LibLevelCompPrev = LibLevel2CompPrev
                                                libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev	
                                        else:
                                            if LibBaseAddrDec != 0:										
                                                libhash[LibNamePrev][TextIndex] = libhash[LibNamePrev][TextIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)                                                                                   
                                  Textflag=1; 
                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',textLine)
                 if not CommonPattern1:
                    CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',textLine)
                    if not CommonPattern1:
                        CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',textLine)
                        if not CommonPattern1:
                           CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',textLine)
                           if not CommonPattern1:
                              CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',textLine) 							
                              if not CommonPattern1:
                                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',textLine)								 
                                 if not CommonPattern1:
                                    CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',textLine)
                                    if not CommonPattern1:
                                       CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',textLine)
                                       if not CommonPattern1:
                                          CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',textLine)										  
                                          if not CommonPattern1:
                                             CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',textLine)											 
                 if CommonPattern1:                  
                       LibBaseAddr=CommonPattern1.group(1)
                       LibSize=CommonPattern1.group(2)
                       LibLevelComp=CommonPattern1.group(3)
                       LibLevel2Comp=CommonPattern1.group(4)
                       LibName=CommonPattern1.group(5)
                       LibBaseAddrDec=int(LibBaseAddr, 16)
                       if TextCheckFlag == 0:
                            TextCheckFlag = 1
                            TextAlignHole=LibBaseAddrDec-TextBaseDec
                            if TextAlignHole != 0:
                                TextAlignName="Text_Align"
                                libhash[TextAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash1[TextAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash[TextAlignName][TextIndex] = TextAlignHole
                                libhash1[TextAlignName][CompIndex] = TextAlignName
                       LibSizeDec=int(LibSize, 16)					   
                       if Textflag == 1:								  
                            if not LibNamePrev in libhash:
                                libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]								
                                if LibBaseAddrDec != 0:                                
                                     libhash[LibNamePrev][TextIndex] = libhash[LibNamePrev][TextIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                     Comp1 = 'Qualcomm'
                                     Comp2 = 'avs'
                                     Comp3 = 'core'
                                     Comp4 = 'Sensors'
                                     if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                          LibLevelCompPrev = LibLevel2CompPrev
                                     libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev								                              
                            else:
                                if LibBaseAddrDec != 0:							
                                     libhash[LibNamePrev][TextIndex] = libhash[LibNamePrev][TextIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                       Textflag = 1
                       LibSizeDec=int(LibSize, 16)
                 if LibBaseAddrDec != 0:					   
                     LibBaseAddrDecPrev = LibBaseAddrDec 
                     LibNamePrev=LibName
                     LibLevelCompPrev=LibLevelComp
                     LibLevel2CompPrev=LibLevel2Comp				 
                 #if nextsec or nextsec1 or nextsec2:
                 if nextsec:
                       #print textLine				 
                       nextsecBase=nextsec.group(2)
                       #print nextsecBase
                       nextsecBaseDec=int(nextsecBase, 16)
                       TextBaseDec=nextsecBaseDec
                       #print TextBaseDec
         libhash[LibNamePrev][TextIndex] = libhash[LibNamePrev][TextIndex] + (TextOverallSize - LibBaseAddrDecPrev)
    rodata=re.search('^.rodata\s+(\w+)\s+(\w+)', to_line)
    if rodata:
         #print (to_line)	
         RodataBase=rodata.group(1)
         RodataSize=rodata.group(2)
         RodataBaseDec=int(RodataBase, 16)
         RodataSizeDec=int(RodataSize, 16)
         RodataOverallSize=RodataBaseDec+RodataSizeDec
         line_number=line_number
         while RodataBaseDec < RodataOverallSize:
                 line_number=line_number+1
                 rodataLine=lines[line_number]
                 #print (rodataLine)				 
                 nextsec=re.search('^\.(\w+)\s+(\w+)\s+(\w+)', rodataLine)
                 if nextsec:
                            Commonnextsec=nextsec
                 nextsec3=re.search('^(\w+)\s+(0x\w+)\s+(0x\w+)', rodataLine)
                 if nextsec3:
                            Commonnextsec=nextsec3							
                 nextsec1=re.search('^\.(\w+)\_DEVCFG\_DATA\n', rodataLine)		
                 if nextsec1:
                           line_number1=line_number+1
                           rodataLine1=lines[line_number1]
                           nextsec2=re.search('(\s+)(\w+)\s+(\w+)', rodataLine1)
                           Commonnextsec=nextsec2				 
                 FirstPattern=re.search('\.\w+\.\w+\n',rodataLine)
                 SecondPattern=re.search('\.\w+\.\w+\.\w+\n',rodataLine)	
                 ThirdPattern=re.match('\s+QSR_STR\.\w+\.\w+\.\n',rodataLine)		
                 FourthPattern=re.match('\s+QSR_STR\.\w+\.\w+\..+\n',rodataLine)				 
                 if FirstPattern or SecondPattern or ThirdPattern or FourthPattern:
                       #print ('kjdhdssa: %s' % rodataLine)
                       line_number=line_number+1
                       ScanLine=lines[line_number]
                       CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)
                       if not CommonPattern:
                            CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)
                            if not CommonPattern:				                       
                                CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)								
                                if not CommonPattern:                            
                                   CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   
                                   if not CommonPattern:                            
                                      CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)	
                       #print (ScanLine)									  
                       if CommonPattern:
                                  #print (ScanLine)					   
                                  LibBaseAddr=CommonPattern.group(1)
                                  LibSize=CommonPattern.group(2)
                                  LibLevelComp=CommonPattern.group(3)
                                  LibLevel2Comp=CommonPattern.group(4)
                                  LibName=CommonPattern.group(5)
                                  LibBaseAddrDec=int(LibBaseAddr, 16)
                                  if RodataCheckFlag == 0:
                                        RodataCheckFlag = 1
                                        RodataAlignHole=LibBaseAddrDec-RodataBaseDec
                                        if RodataAlignHole != 0:
                                              RodataAlignName="Rodata_Align"
                                              libhash[RodataAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash1[RodataAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash[RodataAlignName][RodataIndex] = RodataAlignHole
                                              libhash1[RodataAlignName][CompIndex] = RodataAlignName
                                  LibSizeDec=int(LibSize, 16)
                                  if Rodataflag == 1:		
                                        if not LibNamePrev in libhash:
                                            #print (LibNamePrev)										
                                            libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]											
                                            libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                            if LibBaseAddrDec != 0: 
                                                    libhash[LibNamePrev][RodataIndex] = libhash[LibNamePrev][RodataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                                    Comp1 = 'Qualcomm'
                                                    Comp2 = 'avs'
                                                    Comp3 = 'core'
                                                    Comp4 = 'Sensors'													
                                                    if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                            LibLevelCompPrev = LibLevel2CompPrev
                                                    libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev									
                                        else:
                                            if LibBaseAddrDec != 0:
                                                    #print (LibNamePrev)
                                                    #print (LibBaseAddrDec)
                                                    #print (LibBaseAddrDecPrev)
                                                    libhash[LibNamePrev][RodataIndex] = libhash[LibNamePrev][RodataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                  Rodataflag=1; 
                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',rodataLine)
                 if not CommonPattern1:
                    CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',rodataLine)
                    if not CommonPattern1:
                        CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',rodataLine)
                        if not CommonPattern1:
                           CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',rodataLine)
                           if not CommonPattern1:
                              CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',rodataLine)							  
                              if not CommonPattern1:
                                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',rodataLine)								 
                                 if not CommonPattern1:
                                    CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',rodataLine)
                                    if not CommonPattern1:
                                       CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',rodataLine)
                                       if not CommonPattern1:
                                          CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',rodataLine)										  
                                          if not CommonPattern1:
                                             CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',rodataLine)
                 if CommonPattern1: 
                       #print (rodataLine)				 
                       LibBaseAddr=CommonPattern1.group(1)
                       LibSize=CommonPattern1.group(2)
                       LibLevelComp=CommonPattern1.group(3)
                       LibLevel2Comp=CommonPattern1.group(4)
                       LibName=CommonPattern1.group(5)
                       LibBaseAddrDec=int(LibBaseAddr, 16)
                       if RodataCheckFlag == 0:
                             RodataCheckFlag = 1
                             RodataAlignHole=LibBaseAddrDec-RodataBaseDec
                             if RodataAlignHole != 0:
                                    RodataAlignName="Rodata_Align"
                                    libhash[RodataAlignName] = [0, 0, 0, 0, 0, 0]
                                    libhash1[RodataAlignName] = [0, 0, 0, 0, 0, 0]
                                    libhash[RodataAlignName][RodataIndex] = RodataAlignHole
                                    libhash1[RodataAlignName][CompIndex] = RodataAlignName
                       LibSizeDec=int(LibSize, 16)					   
                       if Rodataflag == 1:								  
                            if not LibNamePrev in libhash:
                                #print (LibNamePrev)							
                                libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]								
                                if LibBaseAddrDec != 0:                                
                                        libhash[LibNamePrev][RodataIndex] = libhash[LibNamePrev][RodataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                        Comp1 = 'Qualcomm'
                                        Comp2 = 'avs'
                                        Comp3 = 'core'
                                        Comp4 = 'Sensors'										
                                        if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                LibLevelCompPrev = LibLevel2CompPrev
                                        libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev								                              
                            else:
                                if LibBaseAddrDec != 0:
                                        #print (LibNamePrev)
                                        #print (LibBaseAddrDec)
                                        #print (LibBaseAddrDecPrev)										
                                        libhash[LibNamePrev][RodataIndex] = libhash[LibNamePrev][RodataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                       Rodataflag = 1
                       LibSizeDec=int(LibSize, 16)
                 if LibBaseAddrDec != 0:
                    LibBaseAddrDecPrev = LibBaseAddrDec 
                    LibNamePrev=LibName
                    LibLevelCompPrev=LibLevelComp
                    LibLevel2CompPrev=LibLevel2Comp					
                 if nextsec or nextsec1 or nextsec3:
                       nextsecBase=Commonnextsec.group(2)
                       nextsecBaseDec=int(nextsecBase, 16)
                       RodataBaseDec=nextsecBaseDec
         libhash[LibNamePrev][RodataIndex] = libhash[LibNamePrev][RodataIndex] + (RodataOverallSize - LibBaseAddrDecPrev)
    if msmchipset == 'msm8996':
     data=re.search('^.data\s+(\w+)\s+(\w+)', to_line)
    else:
     data=re.search('^.data\s+(\w+)\s+(\w+)', to_line, re.IGNORECASE)
    if data:
         DataBase=data.group(1)
         DataSize=data.group(2)
         DataBaseDec=int(DataBase, 16)
         DataSizeDec=int(DataSize, 16)
         DataOverallSize=DataBaseDec+DataSizeDec
         line_number=line_number
         while DataBaseDec < DataOverallSize:
                 line_number=line_number+1
                 dataLine=lines[line_number]
                 #print (dataLine)				 
                 nextsec=re.search('^\.(\w+)\s+(\w+)\s+(\w+)', dataLine)
                 if nextsec:
                            Commonnextsec=nextsec
                 nextsec3=re.search('^(\w+)\s+(0x\w+)\s+(0x\w+)', dataLine)
                 if nextsec3:
                            Commonnextsec=nextsec3								
                 nextsec1=re.search('^\.(\w+)\_DEVCFG\_DATA\n', dataLine)		
                 if nextsec1:
                           line_number1=line_number+1
                           dataLine1=lines[line_number1]
                           nextsec2=re.search('(\s+)(\w+)\s+(\w+)', dataLine1)
                           Commonnextsec=nextsec2				 
                 FirstPattern=re.search('\.\w+\.\w+\n',dataLine)
                 SecondPattern=re.search('\.\w+\.\w+\.\w+\n',dataLine)				 	
                 if FirstPattern or SecondPattern:
                       line_number=line_number+1
                       ScanLine=lines[line_number]
                       CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)
                       if not CommonPattern:
                            CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)
                            if not CommonPattern:				                       
                                CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)								
                                if not CommonPattern:                            
                                   CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   
                                   if not CommonPattern:                            
                                      CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   									  
                       if CommonPattern:
                                  LibBaseAddr=CommonPattern.group(1)
                                  LibSize=CommonPattern.group(2)
                                  LibLevelComp=CommonPattern.group(3)
                                  LibLevel2Comp=CommonPattern.group(4)
                                  LibName=CommonPattern.group(5)
                                  LibBaseAddrDec=int(LibBaseAddr, 16)
                                  if DataCheckFlag == 0:
                                        DataCheckFlag = 1
                                        DataAlignHole=LibBaseAddrDec-DataBaseDec
                                        if DataAlignHole != 0:
                                              DataAlignName="Data_Align"
                                              libhash[DataAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash1[DataAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash[DataAlignName][DataIndex] = DataAlignHole
                                              libhash1[DataAlignName][CompIndex] = DataAlignName
                                  LibSizeDec=int(LibSize, 16)
                                  if Dataflag == 1:		
                                        if not LibNamePrev in libhash:
                                            libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]											
                                            libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                            if LibBaseAddrDec != 0:
                                                    libhash[LibNamePrev][DataIndex] = libhash[LibNamePrev][DataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                                    Comp1 = 'Qualcomm'
                                                    Comp2 = 'avs'
                                                    Comp3 = 'core'
                                                    Comp4 = 'Sensors'													
                                                    if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                            LibLevelCompPrev = LibLevel2CompPrev
                                                    libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev
                                        else:
                                            if LibBaseAddrDec != 0:
                                                    libhash[LibNamePrev][DataIndex] = libhash[LibNamePrev][DataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)                                            
                                  Dataflag=1; 
                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',dataLine)
                 if not CommonPattern1:
                    CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',dataLine)
                    if not CommonPattern1:
                        CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',dataLine)
                        if not CommonPattern1:
                           CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',dataLine)
                           if not CommonPattern1:
                              CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',dataLine)							  
                              if not CommonPattern1:
                                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',dataLine)								 
                                 if not CommonPattern1:
                                    CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',dataLine)
                                    if not CommonPattern1:
                                       CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',dataLine)
                                       if not CommonPattern1:
                                          CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',dataLine)										  
                                          if not CommonPattern1:
                                             CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',dataLine)											 
                 if CommonPattern1: 
                       LibBaseAddr=CommonPattern1.group(1)
                       LibSize=CommonPattern1.group(2)
                       LibLevelComp=CommonPattern1.group(3)
                       LibLevel2Comp=CommonPattern1.group(4)
                       LibName=CommonPattern1.group(5)
                       LibBaseAddrDec=int(LibBaseAddr, 16)
                       if DataCheckFlag == 0:
                            DataCheckFlag = 1
                            DataAlignHole=LibBaseAddrDec-DataBaseDec
                            if DataAlignHole != 0:
                                DataAlignName="Data_Align"
                                libhash[DataAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash1[DataAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash[DataAlignName][DataIndex] = DataAlignHole
                                libhash1[DataAlignName][CompIndex] = DataAlignName	
                       LibSizeDec=int(LibSize, 16)								
                       if Dataflag == 1:								  
                            if not LibNamePrev in libhash:
                                libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]								
                                if LibBaseAddrDec != 0:                                
                                        libhash[LibNamePrev][DataIndex] = libhash[LibNamePrev][DataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                        Comp1 = 'Qualcomm'
                                        Comp2 = 'avs'
                                        Comp3 = 'core'
                                        Comp4 = 'Sensors'										
                                        if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                LibLevelCompPrev = LibLevel2CompPrev
                                        libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev								                          
                            else:
                                if LibBaseAddrDec != 0:
                                        libhash[LibNamePrev][DataIndex] = libhash[LibNamePrev][DataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                       Dataflag = 1
                       LibSizeDec=int(LibSize, 16)
                 if LibBaseAddrDec != 0:
                    LibBaseAddrDecPrev = LibBaseAddrDec 
                    LibNamePrev=LibName
                    LibLevelCompPrev=LibLevelComp
                    LibLevel2CompPrev=LibLevel2Comp					
                 if nextsec or nextsec1 or nextsec3:
                       nextsecBase=Commonnextsec.group(2)
                       nextsecBaseDec=int(nextsecBase, 16)
                       DataBaseDec=nextsecBaseDec
         libhash[LibNamePrev][DataIndex] = libhash[LibNamePrev][DataIndex] + (DataOverallSize - LibBaseAddrDecPrev)
    if msmchipset == 'msm8996': 
     sdata=re.search('^.sdata\s+(\w+)\s+(\w+)', to_line)
    else:
     sdata=re.search('^.sdata\s+(\w+)\s+(\w+)', to_line, re.IGNORECASE)	
    if sdata:
         SdataBase=sdata.group(1)
         SdataSize=sdata.group(2)
         SdataBaseDec=int(SdataBase, 16)
         SdataSizeDec=int(SdataSize, 16)
         SdataOverallSize=SdataBaseDec+SdataSizeDec
         line_number=line_number
         while SdataBaseDec < SdataOverallSize:
                 line_number=line_number+1
                 sdataLine=lines[line_number]
                 nextsec=re.search('^\.(\w+)\s+(\w+)\s+(\w+)', sdataLine)
                 if nextsec:
                            Commonnextsec=nextsec
                 nextsec3=re.search('^(\w+)\s+(0x\w+)\s+(0x\w+)', sdataLine)
                 if nextsec3:
                            Commonnextsec=nextsec3								
                 nextsec1=re.search('^\.(\w+)\_DEVCFG\_DATA\n', sdataLine)		
                 if nextsec1:
                           line_number1=line_number+1
                           sdataLine1=lines[line_number1]
                           nextsec2=re.search('(\s+)(\w+)\s+(\w+)', sdataLine1)
                           Commonnextsec=nextsec2				 
                 FirstPattern=re.search('\.\w+\.\w+\n',sdataLine)
                 SecondPattern=re.search('\.\w+\.\w+\.\w+\n',sdataLine)				 	
                 if FirstPattern or SecondPattern:
                       line_number=line_number+1
                       ScanLine=lines[line_number]
                       CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)
                       if not CommonPattern:
                            CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)
                            if not CommonPattern:				                       
                                CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)								
                                if not CommonPattern:                            
                                   CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   
                                   if not CommonPattern:                            
                                      CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   									   
                       if CommonPattern:
                                  LibBaseAddr=CommonPattern.group(1)
                                  LibSize=CommonPattern.group(2)
                                  LibLevelComp=CommonPattern.group(3)
                                  LibLevel2Comp=CommonPattern.group(4)
                                  LibName=CommonPattern.group(5)
                                  LibBaseAddrDec=int(LibBaseAddr, 16)
                                  if SdataCheckFlag == 0:
                                        SdataCheckFlag = 1
                                        SdataAlignHole=LibBaseAddrDec-SdataBaseDec
                                        if SdataAlignHole != 0:
                                              SdataAlignName="Sdata_Align"
                                              libhash[SdataAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash1[SdataAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash[SdataAlignName][SdataIndex] = SdataAlignHole
                                              libhash1[SdataAlignName][CompIndex] = SdataAlignName
                                  LibSizeDec=int(LibSize, 16)
                                  if Sdataflag == 1:		
                                        if not LibNamePrev in libhash:
                                            libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]											
                                            libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                            if LibBaseAddrDec != 0:
                                                    libhash[LibNamePrev][SdataIndex] = libhash[LibNamePrev][SdataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                                    Comp1 = 'Qualcomm'
                                                    Comp2 = 'avs'
                                                    Comp3 = 'core'
                                                    Comp4 = 'Sensors'													
                                                    if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                            LibLevelCompPrev = LibLevel2CompPrev
                                                    libhash1[LibNamePrev][CompIndex] = LibLevelComp		
                                        else:
                                            if LibBaseAddrDec != 0:
                                                    libhash[LibNamePrev][SdataIndex] = libhash[LibNamePrev][SdataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)                                            
                                  Sdataflag=1; 
                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sdataLine)
                 if not CommonPattern1:
                    CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sdataLine)
                    if not CommonPattern1:
                        CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',sdataLine)
                        if not CommonPattern1:
                           CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',sdataLine)
                           if not CommonPattern1:
                              CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',sdataLine)							  
                              if not CommonPattern1:
                                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',sdataLine)								 
                                 if not CommonPattern1:
                                    CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sdataLine)
                                    if not CommonPattern1:
                                       CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sdataLine)
                                       if not CommonPattern1:
                                          CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sdataLine)										  
                                          if not CommonPattern1:
                                             CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sdataLine)											 
                 if CommonPattern1: 
                       LibBaseAddr=CommonPattern1.group(1)
                       LibSize=CommonPattern1.group(2)
                       LibLevelComp=CommonPattern1.group(3)
                       LibLevel2Comp=CommonPattern1.group(4)
                       LibName=CommonPattern1.group(5)
                       LibBaseAddrDec=int(LibBaseAddr, 16)
                       if SdataCheckFlag == 0:
                            SdataCheckFlag = 1
                            SdataAlignHole=LibBaseAddrDec-SdataBaseDec
                            if SdataAlignHole != 0:
                                SdataAlignName="Sdata_Align"
                                libhash[SdataAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash1[SdataAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash[SdataAlignName][SdataIndex] = SdataAlignHole
                                libhash1[SdataAlignName][CompIndex] = SdataAlignName	
                       LibSizeDec=int(LibSize, 16)								
                       if Sdataflag == 1:								  
                            if not LibNamePrev in libhash:
                                libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]								
                                if LibBaseAddrDec != 0:                                
                                        libhash[LibNamePrev][SdataIndex] = libhash[LibNamePrev][SdataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                        Comp1 = 'Qualcomm'
                                        Comp2 = 'avs'
                                        Comp3 = 'core'
                                        Comp4 = 'Sensors'										
                                        if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                LibLevelCompPrev = LibLevel2CompPrev
                                        libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev								                              
                            else:
                                if LibBaseAddrDec != 0:
                                        libhash[LibNamePrev][SdataIndex] = libhash[LibNamePrev][SdataIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                       Sdataflag = 1
                       LibSizeDec=int(LibSize, 16)
                 if LibBaseAddrDec != 0:
                    LibBaseAddrDecPrev = LibBaseAddrDec 
                    LibNamePrev=LibName
                    LibLevelCompPrev=LibLevelComp
                    LibLevel2CompPrev=LibLevel2Comp					
                 if nextsec or nextsec1 or nextsec3:
                       nextsecBase=Commonnextsec.group(2)
                       nextsecBaseDec=int(nextsecBase, 16)
                       SdataBaseDec=nextsecBaseDec
         libhash[LibNamePrev][SdataIndex] = libhash[LibNamePrev][SdataIndex] + (SdataOverallSize - LibBaseAddrDecPrev)
    sbss=re.search('^.sbss\s+(\w+)\s+(\w+)', to_line, re.IGNORECASE)
    if sbss:
         SbssBase=sbss.group(1)
         SbssSize=sbss.group(2)
         SbssBaseDec=int(SbssBase, 16)
         SbssSizeDec=int(SbssSize, 16)
         line_number=line_number
         if SbssSizeDec != 0:	 
			 SbssOverallSize=SbssBaseDec+SbssSizeDec
			 while SbssBaseDec < SbssOverallSize:
					 line_number=line_number+1
					 sbssLine=lines[line_number]
					 nextsec=re.search('^\.(\w+)\s+(\w+)\s+(\w+)', sbssLine)
					 if nextsec:
								Commonnextsec=nextsec	
					 nextsec3=re.search('^(\w+)\s+(0x\w+)\s+(0x\w+)', sbssLine)
					 if nextsec3:
								Commonnextsec=nextsec3									
					 nextsec1=re.search('^\.(\w+)\_DEVCFG\_DATA\n', sbssLine)		
					 if nextsec1:
							   line_number1=line_number+1
							   sbssLine1=lines[line_number1]
							   nextsec2=re.search('(\s+)(\w+)\s+(\w+)', sbssLine1)
							   Commonnextsec=nextsec2				 
					 FirstPattern=re.search('\.\w+\.\w+\n',sbssLine)
					 SecondPattern=re.search('\.\w+\.\w+\.\w+\n',sbssLine)				 	
					 if FirstPattern or SecondPattern:
						   line_number=line_number+1
						   ScanLine=lines[line_number]
						   CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)
						   if not CommonPattern:
						        CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)
						        if not CommonPattern:				                       
						            CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)									
						            if not CommonPattern:                            
						               CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   
						               if not CommonPattern:                            
						                  CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   										  
						   if CommonPattern:
									  LibBaseAddr=CommonPattern.group(1)
									  LibSize=CommonPattern.group(2)
									  LibLevelComp=CommonPattern.group(3)
									  LibLevel2Comp=CommonPattern.group(4)
									  LibName=CommonPattern.group(5)
									  LibBaseAddrDec=int(LibBaseAddr, 16)
									  if SbssCheckFlag == 0:
											SbssCheckFlag = 1
											SbssAlignHole=LibBaseAddrDec-SbssBaseDec
											if SbssAlignHole != 0:
												  SbssAlignName="Sbss_Align"
												  libhash[SbssAlignName] = [0, 0, 0, 0, 0, 0]
												  libhash1[SbssAlignName] = [0, 0, 0, 0, 0, 0]
												  libhash[SbssAlignName][SbssIndex] = SbssAlignHole
												  libhash1[SbssAlignName][CompIndex] = SbssAlignName
									  LibSizeDec=int(LibSize, 16)
									  if Sbssflag == 1:		
											if not LibNamePrev in libhash:
												libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]											
												libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]
												if LibBaseAddrDec != 0:
														libhash[LibNamePrev][SbssIndex] = libhash[LibNamePrev][SbssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
														Comp1 = 'Qualcomm'
														Comp2 = 'avs'
														Comp3 = 'core'
														Comp4 = 'Sensors'														
														if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
																LibLevelCompPrev = LibLevel2CompPrev
														libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev									
											else:
												if LibBaseAddrDec != 0:
														libhash[LibNamePrev][SbssIndex] = libhash[LibNamePrev][SbssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)												
									  Sbssflag=1; 
					 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sbssLine)
					 if not CommonPattern1:
						CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sbssLine)
						if not CommonPattern1:
							CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',sbssLine)
							if not CommonPattern1:
							   CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',sbssLine)
							   if not CommonPattern1:
								  CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',sbssLine)								  
								  if not CommonPattern1:
									 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',sbssLine)									 
									 if not CommonPattern1:
										CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sbssLine)
										if not CommonPattern1:
										   CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sbssLine)
										   if not CommonPattern1:
											  CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sbssLine)											  
											  if not CommonPattern1:
												 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',sbssLine)												 
					 if CommonPattern1:
						   LibBaseAddr=CommonPattern1.group(1)
						   LibSize=CommonPattern1.group(2)
						   LibLevelComp=CommonPattern1.group(3)
						   LibLevel2Comp=CommonPattern1.group(4)
						   LibName=CommonPattern1.group(5)
						   LibBaseAddrDec=int(LibBaseAddr, 16)
						   if SbssCheckFlag == 0:
								SbssCheckFlag = 1
								SbssAlignHole=LibBaseAddrDec-SbssBaseDec
								if SbssAlignHole != 0:
									SbssAlignName="Sbss_Align"
									libhash[SbssAlignName] = [0, 0, 0, 0, 0, 0]
									libhash1[SbssAlignName] = [0, 0, 0, 0, 0, 0]
									libhash[SbssAlignName][SbssIndex] = SbssAlignHole
									libhash1[SbssAlignName][CompIndex] = SbssAlignName	
						   LibSizeDec=int(LibSize, 16)								
						   if Sbssflag == 1:								  
								if not LibNamePrev in libhash:
									libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]
									libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]								
									if LibBaseAddrDec != 0:                                
											libhash[LibNamePrev][SbssIndex] = libhash[LibNamePrev][SbssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
											Comp1 = 'Qualcomm'
											Comp2 = 'avs'
											Comp3 = 'core'
											Comp4 = 'Sensors'
											if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
													LibLevelCompPrev = LibLevel2CompPrev
											libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev								                              
								else:
									if LibBaseAddrDec != 0:
											libhash[LibNamePrev][SbssIndex] = libhash[LibNamePrev][SbssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
						   Sbssflag = 1
						   LibSizeDec=int(LibSize, 16)
					 if LibBaseAddrDec != 0:
						LibBaseAddrDecPrev = LibBaseAddrDec 
						LibNamePrev=LibName
						LibLevelCompPrev=LibLevelComp
						LibLevel2CompPrev=LibLevel2Comp						
					 if nextsec or nextsec1 or nextsec3:
						   nextsecBase=Commonnextsec.group(2)
						   nextsecBaseDec=int(nextsecBase, 16)
						   SbssBaseDec=nextsecBaseDec
			 libhash[LibNamePrev][SbssIndex] = libhash[LibNamePrev][SbssIndex] + (SbssOverallSize - LibBaseAddrDecPrev)
    bss=re.search('^.bss\s+(\w+)\s+(\w+)', to_line, re.IGNORECASE)
    if bss:
         BssBase=bss.group(1)
         BssSize=bss.group(2)
         BssBaseDec=int(BssBase, 16)
         BssSizeDec=int(BssSize, 16)
         BssOverallSize=BssBaseDec+BssSizeDec
         line_number=line_number
         while BssBaseDec < BssOverallSize:
                 line_number=line_number+1
                 bssLine=lines[line_number]
                 nextsec=re.search('^\.(\w+)\s+(\w+)\s+(\w+)', bssLine)
                 if nextsec:
                            Commonnextsec=nextsec
                 nextsec3=re.search('^(\w+)\s+(0x\w+)\s+(0x\w+)', bssLine)
                 if nextsec3:
                            Commonnextsec=nextsec3								
                 nextsec4=re.search('(QSR_STRING)\s+(\w+)\s+(\w+)', bssLine)
                 if nextsec4:
                            Commonnextsec=nextsec4								
                 nextsec1=re.search('^\.(\w+)\_DEVCFG\_DATA\n', bssLine)		
                 if nextsec1:
                           line_number1=line_number+1
                           bssLine1=lines[line_number1]
                           nextsec2=re.search('(\s+)(\w+)\s+(\w+)', bssLine1)
                           Commonnextsec=nextsec2				 
                 FirstPattern=re.search('\.\w+\.\w+\n',bssLine)
                 SecondPattern=re.search('\.\w+\.\w+\.\w+\n',bssLine)	
                 TwenthPattern=re.search('\COMMON\.\w+\n',bssLine)
                 ThirtithPattern=re.search('\COMMON\.\w+\.\w+\n',bssLine)		
                 TwenthonePattern=re.search('\common\.\w+\n',bssLine)
                 ThirtithonePattern=re.search('\common\.\w+\.\w+\n',bssLine)				 
                 if FirstPattern or SecondPattern or TwenthPattern or ThirtithPattern or TwenthonePattern or ThirtithonePattern:
                       line_number=line_number+1
                       ScanLine=lines[line_number]
                       CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)
                       if not CommonPattern:
                            CommonPattern=re.search('(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)
                            if not CommonPattern:				                       
                                CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',ScanLine)								
                                if not CommonPattern:                            
                                   CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   
                                   if not CommonPattern:                            
                                      CommonPattern=re.search('(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',ScanLine)					   									  
                       if CommonPattern:
                                  LibBaseAddr=CommonPattern.group(1)
                                  LibSize=CommonPattern.group(2)
                                  LibLevelComp=CommonPattern.group(3)
                                  LibLevel2Comp=CommonPattern.group(4)
                                  LibName=CommonPattern.group(5)
                                  LibBaseAddrDec=int(LibBaseAddr, 16)
                                  if BssCheckFlag == 0:
                                        BssCheckFlag = 1
                                        BssAlignHole=LibBaseAddrDec-BssBaseDec
                                        if BssAlignHole != 0:
                                              BssAlignName="Bss_Align"
                                              libhash[BssAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash1[BssAlignName] = [0, 0, 0, 0, 0, 0]
                                              libhash[BssAlignName][BssIndex] = BssAlignHole
                                              libhash1[BssAlignName][CompIndex] = BssAlignName
                                  LibSizeDec=int(LibSize, 16)
                                  if Bssflag == 1:		
                                        if not LibNamePrev in libhash:
                                            libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]											
                                            libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                            if LibBaseAddrDec != 0:
                                                    libhash[LibNamePrev][BssIndex] = libhash[LibNamePrev][BssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                                    Comp1 = 'Qualcomm'
                                                    Comp2 = 'avs'
                                                    Comp3 = 'core'
                                                    Comp4 = 'Sensors'													
                                                    if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                            LibLevelCompPrev = LibLevel2CompPrev
                                                    libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev								
                                        else:
                                            if LibBaseAddrDec != 0:
                                                    libhash[LibNamePrev][BssIndex] = libhash[LibNamePrev][BssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)       
                                  Bssflag=1; 
                 CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                 if not CommonPattern1:
                    CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                    if not CommonPattern1:
                       CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)
                       if not CommonPattern1:
                          CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)
                          if not CommonPattern1:
                             CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)							 
                             if not CommonPattern1:			 
                                CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)								
                                if not CommonPattern1:
                                   CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                                   if not CommonPattern1:				 
                                      CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                                      if not CommonPattern1:
                                         CommonPattern1=re.search('\.\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)										 
                                         if not CommonPattern1:			 
                                            CommonPattern1=re.search('\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)											
                                            if not CommonPattern1:						
                                               CommonPattern1=re.search('\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                                               if not CommonPattern1:
                                                  CommonPattern1=re.search('\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                                                  if not CommonPattern1:
                                                     CommonPattern1=re.search('\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)
                                                     if not CommonPattern1:
                                                        CommonPattern1=re.search('\w+\.\w+\s+(\w+)\s+(\w+)\s+\.\.\/\.\.\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)
                                                        if not CommonPattern1:					
                                                           CommonPattern1=re.search('\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)														   
                                                           if not CommonPattern1:		 
                                                              CommonPattern1=re.search('\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+$',bssLine)															  
                                                              if not CommonPattern1:
                                                                 CommonPattern1=re.search('\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                                                                 if not CommonPattern1:				 
                                                                    CommonPattern1=re.search('\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/.+\/adsp_proc\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)
                                                                    if not CommonPattern1:
                                                                       CommonPattern1=re.search('\w+\.\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)																	   
                                                                       if not CommonPattern1:				 
                                                                          CommonPattern1=re.search('\w+\s+(\w+)\s+(\w+)\s+\w+\:\/(\w+)\/(\w+).+\/(.+)\.\w+\(.+\)',bssLine)																		  
                 if CommonPattern1:                  
                       LibBaseAddr=CommonPattern1.group(1)
                       LibSize=CommonPattern1.group(2)
                       LibLevelComp=CommonPattern1.group(3)
                       LibLevel2Comp=CommonPattern1.group(4)
                       LibName=CommonPattern1.group(5)
                       LibBaseAddrDec=int(LibBaseAddr, 16)
                       if BssCheckFlag == 0:
                            BssCheckFlag = 1
                            BssAlignHole=LibBaseAddrDec-BssBaseDec
                            if BssAlignHole != 0:
                                BssAlignName="Bss_Align"
                                libhash[BssAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash1[BssAlignName] = [0, 0, 0, 0, 0, 0]
                                libhash[BssAlignName][BssIndex] = BssAlignHole
                                libhash1[BssAlignName][CompIndex] = BssAlignName	
                       LibSizeDec=int(LibSize, 16)								
                       if Bssflag == 1:								  
                            if not LibNamePrev in libhash:
                                libhash[LibNamePrev] = [0, 0, 0, 0, 0, 0]
                                libhash1[LibNamePrev] = [0, 0, 0, 0, 0, 0]								
                                if LibBaseAddrDec != 0:                                
                                        libhash[LibNamePrev][BssIndex] = libhash[LibNamePrev][BssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                                        Comp1 = 'Qualcomm'
                                        Comp2 = 'avs'
                                        Comp3 = 'core'
                                        Comp4 = 'Sensors'										
                                        if Comp1 == LibLevelCompPrev or Comp2 == LibLevelCompPrev or Comp3 == LibLevelCompPrev or Comp4 == LibLevelCompPrev:
                                                LibLevelCompPrev = LibLevel2CompPrev
                                        libhash1[LibNamePrev][CompIndex] = LibLevelCompPrev								                              
                            else:
                                if LibBaseAddrDec != 0:
                                        libhash[LibNamePrev][BssIndex] = libhash[LibNamePrev][BssIndex] + (LibBaseAddrDec - LibBaseAddrDecPrev)
                       Bssflag = 1
                       LibSizeDec=int(LibSize, 16)
                 if LibBaseAddrDec != 0:
                    LibBaseAddrDecPrev = LibBaseAddrDec 
                    LibNamePrev=LibName
                    LibLevelCompPrev=LibLevelComp
                    LibLevel2CompPrev=LibLevel2Comp  					
                 if nextsec or nextsec1 or nextsec4 or nextsec3:
                       nextsecBase=Commonnextsec.group(2)
                       nextsecBaseDec=int(nextsecBase, 16)
                       if nextsecBaseDec != 0: 					   
                             BssBaseDec=nextsecBaseDec
                       else:
                             BssBaseDec=BssOverallSize					   
         libhash[LibNamePrev][BssIndex] = libhash[LibNamePrev][BssIndex] + (BssOverallSize - LibBaseAddrDecPrev)
    if toolsUsed <= 6:
     devcfgdata=re.search('^(\.\w+\_DEVCFG\_DATA)\s+\w+\s+(\w+)', to_line)
     if devcfgdata:		 
        Base8974=devcfgdata.group(1)
        Size8974=devcfgdata.group(2)	
        DevList.append(Base8974)
        DevIndex=DevIndex+1
        Size8974=int(Size8974, 16)
        DevList.append(Size8974)
        DevIndex=DevIndex+1	
     devdata=re.search('^(\.\w+)\n', to_line)
     devdata1=re.search('^(\w+)\n', to_line)
     devdata2=re.search('^(\w+\.\w+\..+)\n', to_line)	
     devdata3=re.search('^(\.\w+\.\w+.+)\n', to_line)
     if devdata:
       dev8974=devdata
     if devdata1:
       dev8974=devdata1
     if devdata2:
       dev8974=devdata2	  
     if devdata3:
       dev8974=devdata3	  	   
     if devdata or devdata1 or devdata2 or devdata3:   
         DevCfgData=dev8974.group(1) 
         #print DevCfgData			 		 
         DevCfgData1=re.search('\.debug.*', DevCfgData)
         DevCfgData2=re.search('\.comment.*', DevCfgData)		 
         if DevCfgData1 or DevCfgData2:
             iii=0
         else:
			 de8974line=lines[line_number]
			 dev8974cfg=re.search('\s+(\w+)\s+(\w+)$', de8974line)	 
			 if dev8974cfg:		 
				 Base8974=dev8974cfg.group(1)
				 Size8974=dev8974cfg.group(2)
				 #print DevCfgData
				 #print to_line
				 DevList.append(DevCfgData)
				 DevIndex=DevIndex+1
				 Size8974=int(Size8974, 16)
				 Size8974=float(Size8974/1024.0)
				 Size8974=round(Size8974,2)             			 
				 DevList.append(Size8974)
				 DevIndex=DevIndex+1	 
    ehframe1=re.search('^(\w+)\s+(0x\w+)\s+(0x\w+)$', to_line)	
    ehframe=re.search('^(\.\w+)\s+(\w+)\s+(\w+)$', to_line)	
    ehframe2=re.search('^(\.\w+\.\w+)\s+(\w+)\s+(\w+)$', to_line)
    if ehframe:
          Commpat=ehframe
    if ehframe1:
          Commpat=ehframe1		
    if ehframe2:
          Commpat=ehframe2			  
    if ehframe or ehframe1 or ehframe2:
         FiniBase=Commpat.group(1)
         FiniStart=Commpat.group(2)
         FiniSize=Commpat.group(3)
         # print FiniBase	
         if FiniBase == '.start':
             ImageStartBase=FiniStart
             ImageStartBase=int(ImageStartBase, 16)
         if FiniBase == '.bss':
             ImageEndBase=FiniStart
             ImageEndBase=int(ImageEndBase, 16)	
             ImageEndSize=FiniSize
             ImageEndSize=int(ImageEndSize, 16)
             ImageEnd1=ImageEndBase+ImageEndSize			 
         FiniBase1=re.search('\.debug.*', FiniBase)
         FiniBase2=re.search('\.comment.*', FiniBase)
         if toolsUsed >= 7:
          FiniBase4=re.search('\.shstrtab', FiniBase)
          FiniBase44=re.search('\.shstrtab.*', FiniBase)
          FiniBase5=re.search('\.symtab', FiniBase)
          FiniBase55=re.search('\.symtab.*', FiniBase)
          FiniBase6=re.search('\.strtab', FiniBase)
          FiniBase66=re.search('\.strtab.*', FiniBase)
          FiniBase7=re.search('\.hash', FiniBase)
          FiniBase77=re.search('\.hash.*', FiniBase)
          FiniBase8=re.search('\.dynsym', FiniBase)
          FiniBase88=re.search('\.dynsym.*', FiniBase)
          FiniBase9=re.search('\.dynstr', FiniBase)
          FiniBase99=re.search('\.dynstr.*', FiniBase)	
         FiniBase3=re.search('QSR_STRING*', FiniBase)
         if toolsUsed <= 6: 		 
          if FiniBase1 or FiniBase2 or FiniBase3:
              iii=0
          else:
             DevList.append(FiniBase)
             DevIndex=DevIndex+1
             #print FiniBase			 
             FiniSize=int(FiniSize, 16)
             FiniSize=float(FiniSize/1024.0)
             FiniSize=round(FiniSize,2) 				 
             DevList.append(FiniSize) 				 
             DevIndex=DevIndex+1
         if toolsUsed >= 7:
          if FiniBase1 or FiniBase2 or FiniBase3 or FiniBase4 or FiniBase44 or FiniBase5 or FiniBase55 or FiniBase6 or FiniBase66 or FiniBase7 or FiniBase77 or FiniBase8 or FiniBase88 or FiniBase9 or FiniBase99:
              iii=0
          else:
             DevList.append(FiniBase)
             DevIndex=DevIndex+1
             #print FiniBase			 
             FiniSize=int(FiniSize, 16)
             FiniSize=float(FiniSize/1024.0)
             FiniSize=round(FiniSize,2) 				 
             DevList.append(FiniSize) 				 
             DevIndex=DevIndex+1
csvout.writerow(("Library Name", ".text", ".rodata", ".data", ".sdata", ".sbss", ".bss", "Total Size KB", "ComponentName"))
for lib in libhash:
   LibAccum=libhash[lib][0]+libhash[lib][1]+libhash[lib][2]+libhash[lib][3]+libhash[lib][4]+libhash[lib][5]
   LibAccum=float(LibAccum/1024.0)
   LibAccum=round(LibAccum,2)
   csvout.writerow((lib, libhash[lib][0], libhash[lib][1], libhash[lib][2], libhash[lib][3], libhash[lib][4], libhash[lib][5], LibAccum, libhash1[lib][0]))
for lib in libhash:
    if not libhash1[lib][0] in comphash:
		  comphash[libhash1[lib][0]] = [0, 0, 0, 0, 0, 0]
		  comphash[libhash1[lib][0]][0] = comphash[libhash1[lib][0]][0]+libhash[lib][0]
		  comphash[libhash1[lib][0]][1] = comphash[libhash1[lib][0]][1]+libhash[lib][1]
		  comphash[libhash1[lib][0]][2] = comphash[libhash1[lib][0]][2]+libhash[lib][2]
		  comphash[libhash1[lib][0]][3] = comphash[libhash1[lib][0]][3]+libhash[lib][3]		  
		  comphash[libhash1[lib][0]][4] = comphash[libhash1[lib][0]][4]+libhash[lib][4]
		  comphash[libhash1[lib][0]][5] = comphash[libhash1[lib][0]][5]+libhash[lib][5]		  
    else:
		  comphash[libhash1[lib][0]][0] = comphash[libhash1[lib][0]][0]+libhash[lib][0]
		  comphash[libhash1[lib][0]][1] = comphash[libhash1[lib][0]][1]+libhash[lib][1]
		  comphash[libhash1[lib][0]][2] = comphash[libhash1[lib][0]][2]+libhash[lib][2]
		  comphash[libhash1[lib][0]][3] = comphash[libhash1[lib][0]][3]+libhash[lib][3]		  
		  comphash[libhash1[lib][0]][4] = comphash[libhash1[lib][0]][4]+libhash[lib][4]
		  comphash[libhash1[lib][0]][5] = comphash[libhash1[lib][0]][5]+libhash[lib][5]	
csvout.writerow("\n")		  
csvout.writerow(("Component Name", ".text", ".rodata", ".data", ".sdata", ".sbss", ".bss", "Total Size KB"))		  
for lib in comphash:
   CompAccum=comphash[lib][0]+comphash[lib][1]+comphash[lib][2]+comphash[lib][3]+comphash[lib][4]+comphash[lib][5]
   CompAccum=float(CompAccum/1024.0)
   CompAccum=round(CompAccum,2)
   csvout.writerow((lib, comphash[lib][0], comphash[lib][1], comphash[lib][2], comphash[lib][3], comphash[lib][4], comphash[lib][5], CompAccum))   
DevListLen=len(DevList)
TotalImageAccu=0
csvout.writerow("\n")
for i in range(0,DevListLen,2):
   secname=DevList[i]
   secsize=float(DevList[i+1])
   TotalImageAccu=TotalImageAccu+secsize
   if secsize != 0:
      csvout.writerow(('The Size of %s in KB:' %(secname),'%.2f' % (secsize)))
      #print 'The Size of %s in KB:' %(secname),'%.2f' % (secsize)
infile.close()
QSRName=0
#print TotalImageAccu
if PDType == 'CommonPD':
    #infile = open("%s" % mapfile, 'r')
	if crmexe:
		readfile = open("%s\\adsp_proc\\section_info.txt" % Location, 'r')
	else:
		readfile = open('section_info.txt','r')
	Seclines = readfile.readlines()			
	Secline_number = 0
	while Secline_number < len(Seclines):
	   Secto_line = Seclines[Secline_number]
	   Secline_number += 1
	   if toolsUsed <= 6:
	     StartSecInfo=re.search('\d+\s+(\.start)\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)  
	   if toolsUsed >= 7:
	     StartSecInfo=re.search('\d+\s+(\.start)\s+(\w+)\s+(\w+)\s+\w+\s+',Secto_line)
	   if StartSecInfo:
			 ImageStartBase=StartSecInfo.group(3)
			 ImageStartBase=int(ImageStartBase, 16)	
	   island=re.search('.+\.island\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)
	   if island:
			 BssStartBase=island.group(2)
			 BssStartSize=island.group(1)
			 BssStartBase=int(BssStartBase, 16)
			 BssStartSize=int(BssStartSize, 16)	
			 BssOverallSize=BssStartBase+BssStartSize
			 islandflag=1
	   if islandflag != 1:
			 if toolsUsed <= 6:			 
			   BssSecInfo=re.search('\d+\s+(\.bss)\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)  
			 if toolsUsed >= 7:
			   BssSecInfo=re.search('\d+\s+(\.bss)\s+(\w+)\s+(\w+)\s+\w+\s+',Secto_line)  
			 if BssSecInfo:
			     BssStartBase=BssSecInfo.group(3)
			     BssStartSize=BssSecInfo.group(2)
			     BssStartBase=int(BssStartBase, 16)
			     BssStartSize=int(BssStartSize, 16)	
			     BssOverallSize=BssStartBase+BssStartSize
	   if toolsUsed <= 6:
	     QsrSecInfo=re.search('\d+\s+(QSR\_STRING)\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)  
	   if toolsUsed >= 7:
	     QsrSecInfo=re.search('\d+\s+(QSR\_STRING)\s+(\w+)\s+(\w+)\s+\w+\s+',Secto_line)  
	   if QsrSecInfo:
			 QSRBase=QsrSecInfo.group(3)
			 QSRSize=QsrSecInfo.group(2)
			 QSRName=QsrSecInfo.group(1)
			 if QSRName == 'QSR_STRING':		 
			     QSRBase=int(QSRBase, 16)
			     QSRSize=int(QSRSize, 16)
			     if islandflag == 1:
			         ImageEnd=BssOverallSize
			     else:
			         ImageEnd=QSRBase+QSRSize
			     Overall=ImageEnd-ImageStartBase
			     #print ImageStartBase 
			     #print ImageEnd				 
			     QSRSize=float(QSRSize/1024.0)
			     QSRSize=round(QSRSize,2)			 
			     TotalImageAccu=TotalImageAccu+QSRSize
			     #print TotalImageAccu	 
			     Overall=float(Overall/1024.0)
			     Overall=round(Overall,2)
			     #print Overall
			     holesize=Overall-TotalImageAccu			 
			     csvout.writerow(('The Size of QSR_STRING in KB:' ,'%.2f' % (QSRSize)))
			     csvout.writerow(('Holes btw the sections in KB:' ,'%.2f' % (holesize)))
			     csvout.writerow(('The Total Image Size in KB:' ,'%.2f' % (Overall)))	
	if QSRName != 'QSR_STRING':
			Overall=BssOverallSize-ImageStartBase
			Overall=float(Overall/1024.0)
			Overall=round(Overall,2)
			holesize=Overall-TotalImageAccu
			csvout.writerow(('Holes btw the sections in KB:' ,'%.2f' % (holesize)))
			csvout.writerow(('The Total Image Size in KB:' ,'%.2f' % (Overall)))				  
else:
	#readfile = open('section_info.txt','r')
	if crmexe:
		readfile = open("%s\\adsp_proc\\section_info.txt" % Location, 'r')	
	else:
		readfile = open('section_info.txt','r')
	Seclines = readfile.readlines()			
	Secline_number = 0
	while Secline_number < len(Seclines):
	   Secto_line = Seclines[Secline_number]
	   Secline_number += 1
	   StartSecInfo=re.search('\d+\s+(\.start\..+\_SENSOR\.\w+)\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)  
	   if StartSecInfo:
			 ImageStartBase=StartSecInfo.group(3)
			 ImageStartBase=int(ImageStartBase, 16)	
	   island=re.search('.+\.island\..+\_SENSOR\.\w+\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)
	   if island:
			 BssStartBase=island.group(2)
			 BssStartSize=island.group(1)
			 BssStartBase=int(BssStartBase, 16)
			 BssStartSize=int(BssStartSize, 16)	
			 BssOverallSize=BssStartBase+BssStartSize
			 islandflag=1
	   if islandflag != 1:			 
			 BssSecInfo=re.search('\d+\s+(\.bss\..+\_SENSOR\.\w+)\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)  
			 if BssSecInfo:
			     BssStartBase=BssSecInfo.group(3)
			     BssStartSize=BssSecInfo.group(2)
			     BssStartBase=int(BssStartBase, 16)
			     BssStartSize=int(BssStartSize, 16)	
			     BssOverallSize=BssStartBase+BssStartSize
	   QsrSecInfo=re.search('\d+\s+(QSR\_STRING)\..+\_SENSOR\.\w+\s+(\w+)\s+\w+\s+(\w+)\s+',Secto_line)  
	   if QsrSecInfo:
			 QSRBase=QsrSecInfo.group(3)
			 QSRSize=QsrSecInfo.group(2)
			 QSRName=QsrSecInfo.group(1)
			 if QSRName == 'QSR_STRING':		 
			     QSRBase=int(QSRBase, 16)
			     QSRSize=int(QSRSize, 16)
			     if islandflag == 1:
			         ImageEnd=BssOverallSize
			     else:
			         ImageEnd=QSRBase+QSRSize
			     Overall=ImageEnd-ImageStartBase
			     #print ImageStartBase 
			     #print ImageEnd				 
			     QSRSize=float(QSRSize/1024.0)
			     QSRSize=round(QSRSize,2)			 
			     TotalImageAccu=TotalImageAccu+QSRSize
			     #print TotalImageAccu	 
			     Overall=float(Overall/1024.0)
			     Overall=round(Overall,2)
			     holesize=Overall-TotalImageAccu			 
			     csvout.writerow(('The Size of QSR_STRING in KB:' ,'%.2f' % (QSRSize)))
			     csvout.writerow(('Holes btw the sections in KB:' ,'%.2f' % (holesize)))
			     csvout.writerow(('The Total Image Size in KB:' ,'%.2f' % (Overall)))	
	if QSRName != 'QSR_STRING':
			Overall=BssOverallSize-ImageStartBase
			Overall=float(Overall/1024.0)
			Overall=round(Overall,2)
			holesize=Overall-TotalImageAccu
			csvout.writerow(('Holes btw the sections in KB:' ,'%.2f' % (holesize)))
			csvout.writerow(('The Total Image Size in KB:' ,'%.2f' % (Overall)))			
	
	

         
