CC 		= g++
CFLAGS 	= -g -Wall -std=c++17
OBJDIR 	= build
SRCDIR 	= src

T_FLAGS		= -lgtest -lgtest_main -pthread
T_OBJDIR	= tests/build
T_SRCDIR	= tests/src
T_EXEMAIN	= tests/test_main.exe

HFILES = $(shell find $(SRCDIR) -name "*.hpp")
CFILES = $(HFILES:$(SRCDIR)/%.hpp=$(OBJDIR)/%.cpp)
OFILES = $(HFILES:$(SRCDIR)/%.hpp=$(OBJDIR)/%.o)

T_CFILES = $(shell find $(T_SRCDIR) -name "*.cpp")
T_OFILES = $(T_CFILES:$(T_SRCDIR)/%.cpp=$(T_OBJDIR)/%.o)

.PHONY: run_tests build_tests

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(T_OBJDIR)/%.o: $(T_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(T_EXEMAIN): $(T_OFILES) $(OFILES)
	$(CC) $(CFLAGS) $(T_FLAGS) -o $@ $^ 

build_tests: $(T_EXEMAIN)

run_tests: $(T_EXEMAIN)
	./$(T_EXEMAIN)

