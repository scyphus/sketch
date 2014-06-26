#
# $Id: Makefile.am,v 0c85687e370b 2010/07/18 06:35:55 Hirochika $
#
# Copyright (c) 2010 Scyphus Solutions Co.,Ltd. All rights reserved.
# Authors:
#      Hirochika Asai  <asai@scyphus.co.jp>
#

lib_LTLIBRARIES = libsketch.la
libsketch_la_SOURCES = hash.c hash.h

bin_PROGRAMS = sketch
sketch_SOURCES = sketch.c
sketch_LDFLAGS = -static $(top_builddir)/libsketch.la


EXTRA_DIST = LICENSE
CLEANFILES = *~
