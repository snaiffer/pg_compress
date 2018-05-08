MODULE_big = compress--0.0.2

OBJS = compress.o \
	   compress_cpp.o \
	   bundle/bundle.o

EXTENSION = compress        # the extensions name

# script files to install
DATA = compress--0.0.2.sql

PG_CPPFLAGS += -fPIC
compress.o: override CFLAGS += -std=c99
compress_cpp.o: override CC = $(CXX)
bundle.o: override CC = $(CXX)

SHLIB_LINK += -lpthread -lstdc++

#REGRESS = compress_test     # our test script file (without extension)

# postgres build stuff
PG_CONFIG = pg_config

PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
