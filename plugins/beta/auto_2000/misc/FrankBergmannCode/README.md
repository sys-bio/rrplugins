# Auto-SBML
This project hosts a C++ library (libAuto) as well as C# interfaces and a graphical frontend for analyzing SBML models (using [RoadRunner](http://roadrunner.sf.net) and [libSBML](http://sbml.org/Software/libSBML)). 

## Background 
Back in 2009, I first dabbled in ceating a tool for [simplifying bifurcation analysis](http://frank-fbergmann.blogspot.de/2009/02/simplifying-bifurcation-analysis.html). By recompiling a version of [AUTO2000](http://indy.cs.concordia.ca/auto/) by Doedel et.al (the only ever C version of Auto) as library and interfacing it with RoadRunner, it is possible to directly open SBML files and have them run. 

## How to use
The frontend basically exposes all of AUTO's configuration parameters to be set. Currently it is only possible of finding the unstable regions, it won't perform continuations *yet*. 

![](http://lh5.ggpht.com/_LvzJ3dV9uLE/SamPxdkGShI/AAAAAAAAABw/RDlmPgojMho/image%5B4%5D.png?imgmax=800)  

As can be seen in the above, all you need to do is to open an SBML model, select the parameter you would like to investigate, select a simulation frame and press run. 

Another feature I'm rather proud off is that you can simply hold the control key while moving the cursor along the graph and you'll see simulations of the model with the selected parameter altered. A right click will let you sent the model to other SBW modules or save it as SBML model. 

## Using the library
New in this project is that the core c++ library uses [cmake](http://cmake.org). That hopefully makes it easier to use it across different operating systems. To create the library: 

	mkdir build
    cmake <location of ./libAuto>
    make

this will create `libAuto.dll|dylib|so` for use with the C# interface. Of course you could use the rather basic API as is demonstrated in the [example](./libAuto/example/AutoTestCPP.cpp)

## License

Copyright (c) 2009-2013, Frank T. Bergmann  
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.