# set the include path for X, qt and KDE
INCLUDES = $(all_includes)

# these are the headers for your project
noinst_HEADERS = ksimopts.h ccelement.h chopupelement.h chopuplist.h \
	finalcost.h formulaelement.h formulalist.h netlist.h nodeelement.h nodelist.h \
	olelement.h rclelement.h scelement.h smatrix.h sparameter.h sparameterlist.h \
	velement.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/ksimopts.pot

KDE_ICON = ksimopts

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = ksimopts

# the application source, library search path, and link libraries
ksimopts_SOURCES = main.cpp ksimopts.cpp ccelement.cpp chopupelement.cpp \
	chopuplist.cpp finalcost.cpp formulaelement.cpp formulalist.cpp netlist.cpp \
	nodeelement.cpp nodelist.cpp olelement.cpp rclelement.cpp scelement.cpp smatrix.cpp \
	sparameter.cpp sparameterlist.cpp velement.cpp
ksimopts_LDFLAGS = $(KDE_RPATH) $(all_libraries)
ksimopts_LDADD = $(LIB_KDEUI)

# this is where the desktop file will go 
shelldesktopdir   = $(kde_appsdir)/Utilities
shelldesktop_DATA = ksimopts.desktop

# this is where the shell's XML-GUI resource file goes
shellrcdir   = $(kde_datadir)/ksimopts
shellrc_DATA = ksimoptsui.rc

