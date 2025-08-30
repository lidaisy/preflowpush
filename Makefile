CXX=g++
CXXFLAGS=-std=c++23 -MMD
OBJECTS=main.o node.o graph.o arc.o screenshot.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=pfp
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}