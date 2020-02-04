PROGS= plot main

all= $(PROGS)


plot: plot.o EF2d-base.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

main: main.o maillage.o
	g++ -Wall main.cpp maillage.cpp EF2d-base.cpp -o main

testt: main.o maillage.o
	g++ -Wall test.cpp maillage.cpp EF2d-base.cpp -o test
	
clean:
	-rm *.o $(PROGS)

# les dependances
plot.o:EF2d-base.hpp
EF2d-base.o:EF2d-base.hpp