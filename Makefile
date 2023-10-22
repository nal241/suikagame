CXX = g++

BINDIR = ./bin
SRCDIR = ./src
INCLUDE = -I./include

LDLIBS = -lglut -lGL -lGLU
LDFLAGS = -L
CXXFLAGS = -MMD -MP -Wall

TARGET = $(BINDIR)/game

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SOURCES:.cpp=.o)
DEPENDS = $(OBJ:.o=.d)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

.PHONY:clean

clean:
	rm -f $(TARGET) $(DEPENDS) $(OBJ) $(SRCDIR)/*.d $(SRCDIR)/*.o


-include $(DEPENDS)