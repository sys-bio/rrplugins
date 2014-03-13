from telplugins import *

try:
    rrDataHandle = createTelluriumDataFromFile("testData.dat")
    hdr = getTelluriumDataColumnHeader(rrDataHandle)
    npData = getNumpyData(rrDataHandle)
    print `hdr` + `npData`

    plotTelluriumData(npData, hdr)
    print "done"
except Exception as e:
    print 'Exception: ' + `e`
