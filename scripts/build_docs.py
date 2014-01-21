import sys
import os
import subprocess
import datetime

from pbs import ls
from pbs import git


from os.path import *
try:
    originalWorkingDirectory = os.getcwd()
    buildFolder= os.path.dirname(os.path.realpath(__file__))
    repoFolder= join(buildFolder,'telPlugins')
    docsDir  = join(buildFolder,'ghPages', 'docs')
    cppDir= join(repoFolder,'source')
    cDir= join(repoFolder,'wrappers', 'c')
    pythonDir= join(repoFolder,'wrappers', 'python')

    #Change into repo folder
    os.chdir(repoFolder)

    #Check status
    print git("status")

    #Pull from origin
    #print git("pull")
    os.chdir(buildFolder)

    #Now update doxygen documentation
    #==== CPP DOCS ====
    os.chdir(cppDir)
    print 'Generating CPP Docs'
    docsOutput=join(buildFolder, docsDir,'cpp')
    cmd ='(type docs.doxy & echo OUTPUT_DIRECTORY='+ docsOutput + ' )| doxygen -'
    output = subprocess.check_output(cmd, shell=True)

    #==== C DOCS ====
    os.chdir(cDir)
    print 'Generating C Docs'
    docsOutput=join(buildFolder, docsDir,'c')
    cmd ='(type docs.doxy & echo OUTPUT_DIRECTORY='+ docsOutput + ' )| doxygen -'
    output = subprocess.check_output(cmd, shell=True)

    #==== Python DOCS ====
    os.chdir(pythonDir)
    print 'Generating Python Docs'
    docsOutput=join(buildFolder, docsDir, 'python')
    doxyFile = 'docs.doxy'
    cmd ='(type ' + doxyFile + ' & echo OUTPUT_DIRECTORY='+ docsOutput + ' )| doxygen -'
    output = subprocess.check_output(cmd, shell=True)

    print 'Generating Low Level Python Docs'
    docsOutput=join(buildFolder,docsDir,'python_c')
    doxyFile = 'docs_c_api.doxy'
    cmd ='(type ' + doxyFile + ' & echo OUTPUT_DIRECTORY='+ docsOutput + ' )| doxygen -'
    output = subprocess.check_output(cmd, shell=True)

    #Git add any new files


    #git push
    #print git("push")

except Exception as e:
   print e
##


