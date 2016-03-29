# libSBOL
C++ implementation of libSBOL 2.0.0. 

libSBOL 2.0.1
======================================

**libSBOL** is a SWIG-Python wrapper around [libSBOL](https://github.com/SynBioDex/libSBOL), a module for reading, writing, and constructing genetic designs according to the standardized specifications of the [Synthetic Biology Open Language (SBOL)](http://www.sbolstandard.org/).  

USE CASE
========
![](crispr_repression2.png)

**Illustration of a hierarchical CRISPR-based repression module represented in SBOL 2.0 (adapted from Figure~1a in [this paper from *Nature Methods*](http://www.nature.com/nmeth/journal/v11/n7/full/nmeth.2969.html) by Kiani, *et al*. The inner Module consists of a CRISPR Repression Circuit that combines a Cas9 protein with a gRNA to form a complex (represented by the dashed arrows) that permanently inactivates a target gene by excising its promoter (represented by the arc with the T-shaped head).   The outer Module is a 3-color Characterization Circuit that expresses blue, yellow, and red fluorescent proteins. The characterization module is coupled to the characterization module in to produce a visual read of the state of the cell. Red is a control signal that calibrates the blue and yellow signals in relation to the bioenergetic state of the cell under different metabolic loads. The dashed lines connecting Modules show how FunctionalComponents in one Module correspond or map to FunctionalComponents in another.**

CODE EXAMPLE
============
For the full code, see CRISPR_example.py

```c++

```

INSTALLATION
============
CMake instructions

PLATFORMS
=========
Tested on Mac OSX Version 10.9.5 and Windows 7 Enterprise with Python 2.7.9 32 bit. Python 3 not currently supported.

DEPENDENCIES
============
Releases include precompiled binaries for libSBOL.


ACKNOWLEDGEMENTS
================

Current support for the development of libSBOL is generously provided by the NSF through the [Synthetic Biology Open Language Resource](http://www.nsf.gov/awardsearch/showAward?AWD_ID=1355909) collaborative award.
