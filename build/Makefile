#############################################################################
#
# Makefile for building: railroad-diagram-generator
#
#############################################################################

####### Compiler, tools and options

CXX           = g++
LINK          = g++
CXXFLAGS      = -std=c++0x
LFLAGS        =
LIBS          =
DEL_FILE      = rm -f

####### Files

OBJECTS       = ./main.o \
                ./buffer.o \
                ./lexer.o \
                ./parser.o \
                ./placer.o \
                ./svg_generator.o
TARGET        = railroad-diagram-generator

####### Build rules

$(TARGET): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $(TARGET) $(LFLAGS) $(LIBS)

main.o: ../src/main.cpp
	$(CXX) -c $(CXXFLAGS) -o ./main.o ../src/main.cpp

buffer.o: ../src/lex/buffer.cpp
	$(CXX) -c $(CXXFLAGS) -o ./buffer.o ../src/lex/buffer.cpp

lexer.o: ../src/lex/lexer.cpp
	$(CXX) -c $(CXXFLAGS) -o ./lexer.o ../src/lex/lexer.cpp

parser.o: ../src/parse/parser.cpp
	$(CXX) -c $(CXXFLAGS) -o ./parser.o ../src/parse/parser.cpp

placer.o: ../src/svg/placer.cpp
	$(CXX) -c $(CXXFLAGS) -o ./placer.o ../src/svg/placer.cpp

svg_generator.o: ../src/svg/svg_generator.cpp
	$(CXX) -c $(CXXFLAGS) -o ./svg_generator.o ../src/svg/svg_generator.cpp

clean:
	$(DEL_FILE) $(OBJECTS)
