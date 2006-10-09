## Makefile.am for ksimopts

# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = ksimopts ksimopts_client

# set the include path for X, qt and KDE
INCLUDES         = $(all_includes)

# the library search path. 
ksimopts_LDFLAGS = $(KDE_RPATH) $(all_libraries)

# the libraries to link against.
ksimopts_LDADD   = $(LIB_KFILE) $(LIB_KDEPRINT)

# which sources should be compiled for ksimopts
ksimopts_SOURCES = main.cpp ksimopts.cpp ksimoptsview.cpp pref.cpp \
	ksimoptsiface.skel sparameter.cpp sparameterlist.cpp netlist.cpp finalcost.cpp smatrix.cpp \
	rclelement.cpp ccelement.cpp velement.cpp scelement.cpp olelement.cpp nodelist.cpp \
	nodeelement.cpp chopuplist.cpp chopupelement.cpp formulalist.cpp formulaelement.cpp

# these are the headers for your project
noinst_HEADERS = ksimopts.h ksimoptsview.h pref.h sparameter.h \
	sparameterlist.h netlist.h finalcost.h smatrix.h rclelement.h ccelement.h velement.h \
	scelement.h olelement.h nodelist.h nodeelement.h chopuplist.h chopupelement.h \
	formulalist.h formulaelement.h

# client stuff
ksimopts_client_LDFLAGS = $(KDE_RPATH) $(all_libraries)
ksimopts_client_LDADD   = $(LIB_KDECORE)
ksimopts_client_SOURCES = ksimopts_client.cpp

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(EXTRACTRC) `find . -name \*.ui -o -name \*.rc` > rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/ksimopts.pot

KDE_ICON = AUTO

# this is where the kdelnk file will go 
kdelnkdir   = $(kde_appsdir)/Utilities
kdelnk_DATA = ksimopts.desktop

# this is where the XML-GUI resource file goes
rcdir = $(kde_datadir)/ksimopts
rc_DATA = ksimoptsui.rc
