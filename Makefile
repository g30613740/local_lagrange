CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -Iinclude
LDFLAGS =

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/lagrange

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	./$(TARGET)
