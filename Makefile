CC 		= g++
CFLAGS 	= -g -Wall -std=c++17
# CFLAGS 	= -std=c++17 -O3
OBJDIR 	= build
SRCDIR 	= src

T_FLAGS		= -lgtest -lgtest_main -pthread
T_OBJDIR	= tests/build
T_SRCDIR	= tests/src
T_EXEMAIN	= tests/test_main.exe

B_CFLAGS 	= -std=c++17 -O3
B_FLAGS 	= -lbenchmark -lpthread
B_OBJDIR	= benchmark/build
B_SRCDIR	= benchmark/src
B_EXEMAIN	= benchmark/benchmark_main.exe

HFILES = $(shell find $(SRCDIR) -name "*.hpp")
CFILES = $(HFILES:$(SRCDIR)/%.hpp=$(OBJDIR)/%.cpp)
OFILES = $(HFILES:$(SRCDIR)/%.hpp=$(OBJDIR)/%.o)

T_CFILES = $(shell find $(T_SRCDIR) -name "*.cpp")
T_OFILES = $(T_CFILES:$(T_SRCDIR)/%.cpp=$(T_OBJDIR)/%.o)

B_CFILES = $(shell find $(B_SRCDIR) -name "*.cpp")
B_OFILES = $(B_CFILES:$(B_SRCDIR)/%.cpp=$(B_OBJDIR)/%.o)

.PHONY: run_tests build_tests build_benchmark clear

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(T_OBJDIR)/utils/%.o: $(T_SRCDIR)/utils/%.cpp $(T_SRCDIR)/utils/%.hpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(T_OBJDIR)/%.o: $(T_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(T_EXEMAIN): $(T_OFILES) $(OFILES)
	$(CC) $(CFLAGS) $(T_FLAGS) -o $@ $^ 

$(B_OBJDIR)/%.o: $(B_SRCDIR)/%.cpp
	$(CC) $(B_CFLAGS) -o $@ -c $<

$(B_EXEMAIN): $(B_OFILES) $(OFILES)
	$(CC) $(B_CFLAGS) $(B_FLAGS) -o $@ $^ 

build_tests: $(T_EXEMAIN)

build_benchmark: $(B_EXEMAIN)

run_tests: $(T_EXEMAIN)
	./$(T_EXEMAIN)

run_benchmark: $(B_EXEMAIN)
	./$(B_EXEMAIN)

clean:
	rm $(OFILES) $(T_OFILES) $(T_EXEMAIN) $(B_OFILES) $(B_EXEMAIN)
