libSBOL 2.0.1
======================================

[libSBOL](https://github.com/SynBioDex/libSBOL) is a C++ library for reading, writing, and constructing genetic designs according to the standardized specifications of the [Synthetic Biology Open Language (SBOL)](http://www.sbolstandard.org/).  

DOCUMENTATION
=============
[An API reference and Getting Started tutorial can be found here](http://synbiodex.github.io/libSBOL/#doxygen)

PLATFORMS
=========
Tested on Mac OSX Version 10.9.5 and Windows 7 Enterprise with Python 2.7.9 32 bit. Python 3 not currently supported.

DEPENDENCIES
============
Releases include precompiled binaries for libSBOL.

INSTALLATION
============
To compile libSBOL, you will need:
* git for downloading the source code
* CMake for generating platform-specific build instructions
* a C++ compiler, such as VisualStudio, g++, or MinGW

First, download them from the links above. Or if you're on Debian/Ubuntu this command should install /// everything:

```
sudo apt-get install git cmake-qt-gui build-essential libxml2-dev gcc-multilib g++-multilib python-dev
```

If you want to update the documentation you also need Doxygen, and to generate the Python wrapper you need SWIG. To install them on Debian/Ubuntu:

```
sudo apt-get install doxygen-gui swig
```

Then, clone the repository:

```
git clone git://github.com/SynBioDex/libSBOLc.git
```

This will create a libSBOLc directory with the code. Next, run CMake (cmake-qt-gui on linux). For "Where is the source code" enter the path to your libSBOLc folder. "Where to build the binaries" can technically be anywhere, but it's only been tested with libSBOLc/build.

Click Configure, and choose what type of compiler you want to generate instructions for. /// All the development has been done using "default native compilers" and MinGW on Windows or Unix makefiles on Mac/Linux. CMake should also be able to generate projects for Eclipse, Visual Studio, XCode, etc. However, that will probably involve adjusting some paths.

The first time you click Configure CMake will list variables, like CMAKE_BUILD_TYPE and LIBXML2_INCLUDE_DIR, in red. That means they've been updated. To build the main SBOL library, just click Configure again until the red goes away. This is also where you set up the optional targets: examples, tests, manual, and Python wrapper. To add them check the appropriate boxes (SBOL_BUILD_EXAMPLES, for example) and then Configure again to adjust the settings. There's one other SBOL-specific option: SBOL_DEBUG_STATEMENTS will cause libSBOLc to be compiled with some extra debugging statements. A lot of other options might be visibile too; checking Grouped at the top makes things more managable. Once it's all set, click Generate to create the compiler instructions.

The last step is to cd into the libSBOL/build folder and run the compiler.

```
make 
```

or

```
mingw32-make.exe
```

Binaries will be generated in the libSBOL/release folder.

EXAMPLE CODE
============
The example code below can be used to construct the biological design in the figure.  See the [Sequence Assembly tutorial here](http://synbiodex.github.io/libSBOL/sequences.html) to learn more about how libSBOL enables high-level design for synthetic biology.

![](gene_cassette.png)
 
**A diagram of a gene cassette, consisting of a promoter, ribosome binding site (RBS), coding sequence (CDS), and transcriptional terminator, expressed in SBOLVisual symbols. The design was programmatically generated with the code below, and then visualized with the SBOLDesigner tool.**
```c++
setHomespace("http://sys-bio.org");
Document& doc = *new Document();

ComponentDefinition& gene = *new ComponentDefinition("BB0001");
ComponentDefinition& promoter = *new ComponentDefinition("R0010");
ComponentDefinition& CDS = *new ComponentDefinition("B0032");
ComponentDefinition& RBS = *new ComponentDefinition("E0040");
ComponentDefinition& terminator = *new ComponentDefinition("B0012");

promoter.roles.set(SO_PROMOTER);
CDS.roles.set(SO_CDS);
RBS.roles.set(SO_RBS);
terminator.roles.set(SO_TERMINATOR);

doc.add<ComponentDefinition>(gene);
doc.add<ComponentDefinition>(promoter);
doc.add<ComponentDefinition>(CDS);
doc.add<ComponentDefinition>(RBS);
doc.add<ComponentDefinition>(terminator);

gene.assemble({ &promoter, &RBS, &CDS, &terminator});


Component& first = gene.getFirstComponent();
cout << first.identity.get() << endl;
Component& last = gene.getLastComponent();
cout << last.identity.get() << endl;

Sequence& promoter_seq = *new Sequence("R0010", "ggctgca");
Sequence& RBS_seq = *new Sequence("B0032", "aattatataaa");
Sequence& CDS_seq = *new Sequence("E0040", "atgtaa");
Sequence& terminator_seq = *new Sequence("B0012", "attcga");
Sequence& gene_seq = *new Sequence("BB0001");

doc.add<Sequence>({&promoter_seq, &CDS_seq, &RBS_seq, &terminator_seq, &gene_seq});

promoter.sequence.set(promoter_seq.identity.get());
CDS.sequence.set(CDS_seq.identity.get());
RBS.sequence.set(RBS_seq.identity.get());
terminator.sequence.set(terminator_seq.identity.get());
gene.sequence.set(gene_seq.identity.get());

gene_seq.assemble();
cout << gene_seq.elements.get() << endl;

doc.write("gene_cassette.xml");
```

ACKNOWLEDGEMENTS
================

Current support for the development of libSBOL is generously provided by the NSF through the [Synthetic Biology Open Language Resource](http://www.nsf.gov/awardsearch/showAward?AWD_ID=1355909) collaborative award.
