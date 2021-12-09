SRCDIR=../src
BINDIR=.
OUTPUT_FILENAME=test.out
CFLAGS=-std=c++2a -lgtest -lgtest_main

main:
	g++-9 \
		test.cpp \
		$(SRCDIR)/GraphFactory.cpp \
		$(SRCDIR)/TGraph.cpp \
		$(SRCDIR)/CompleteGraph.cpp \
		$(SRCDIR)/SimpleGraph.cpp \
		$(SRCDIR)/WeightedGraph.cpp \
		$(SRCDIR)/BipartiteGraph.cpp \
		$(SRCDIR)/utils.cpp \
		$(SRCDIR)/graphUtils.cpp \
		$(SRCDIR)/graphValidation.cpp \
		-o $(BINDIR)/$(OUTPUT_FILENAME) \
		$(CFLAGS)
