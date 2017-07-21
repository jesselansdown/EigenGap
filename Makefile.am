#
# EigenGap: Use the Eigen C++ Library within GAP
#
# This file is part of the build system of a GAP kernel extension.
# Requires automake.
#
ACLOCAL_AMFLAGS = -I m4

BINARCHDIR = bin/$(GAPARCH)
GAPINSTALLLIB = $(BINARCHDIR)/EigenGap.so

lib_LTLIBRARIES = EigenGap.la

EigenGap_la_SOURCES = src/EigenGap.cc
EigenGap_la_CPPFLAGS = $(GAP_CPPFLAGS) -DCONFIG_H $(EIGEN_CPPFLAGS)
EigenGap_la_LDFLAGS = -L$(EIGEN_LDPATH) -module -avoid-version
if SYS_IS_CYGWIN
EigenGap_la_LDFLAGS += -no-undefined -version-info 0:0:0 
EigenGap_la_LDFLAGS += -Wl,$(GAPROOT)/bin/$(GAPARCH)/gap.dll
endif

all-local: $(GAPINSTALLLIB)

$(GAPINSTALLLIB): EigenGap.la
	$(mkdir_p) $(BINARCHDIR)
if SYS_IS_CYGWIN
	cp .libs/EigenGap.dll $(GAPINSTALLLIB)
else
	cp .libs/EigenGap.so $(GAPINSTALLLIB)
endif

clean-local:
	rm -f $(GAPINSTALLLIB)

distclean-local:
	rm -rf bin/*

doc:
	($(GAPROOT)/bin/gap.sh -A makedoc.g)
