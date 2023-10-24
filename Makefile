CXX = g++

BINDIR = ./bin
SRCDIR = ./src
INCLUDE = -I./include
TMPDIR = ./tmp

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

.PHONY:clean mvtmp bktmp

clean:
	rm -f $(TARGET) $(DEPENDS) $(OBJ) $(SRCDIR)/*.d $(SRCDIR)/*.o
mvtmp:
	mv $(SRCDIR)/*.d ./tmp
	mv $(SRCDIR)/*.o ./tmp
bktmp:
	mv ./tmp/*.d $(SRCDIR)
	mv ./tmp/*.o $(SRCDIR)



-include $(DEPENDS)