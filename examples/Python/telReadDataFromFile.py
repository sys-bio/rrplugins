from rrplugins import *

try:

    rrDataHandle = createRoadRunnerDataFromFile("testData.dat")
    hdr = getRoadRunnerDataColumnHeader(rrDataHandle)
    npData = getNumpyData(rrDataHandle)
    print `hdr` + `npData`

    plotRoadRunnerData(npData, hdr)

    print "done"
except Exception as e:
    print 'Exception: ' + `e`
