#-----------------------------------------compliler
CXX= g++

#-----------compile with warnings, debug, and optimization
CXXFLAGS= -Wall -g -O0

#-----------object file
OBJMOM=mainMom.o mom.o tools.o shared.hpp
OBJKID=mainKid.o child.o tools.o shared.hpp

#-----------------------linking command
p8MOM: $(OBJMOM) $(OBJKID)
	$(CXX) -o p8mom $(OBJMOM)
	$(CXX) -o p8kid $(OBJKID)

#-----------------------cleanup command
clean:
	rm -f $(OBJMOM) p8mom
	rm -f $(OBJKID) p8kid

depend:
	$(CXX) -MM *.cpp >> makefile


#-----------------------dependencies
mainMom.o: mainMom.cpp mom.hpp tools.hpp
mainKid.o: mainKid.cpp tools.hpp child.hpp
mom.o: mom.cpp mom.hpp shared.hpp child.hpp
child.o: child.cpp child.hpp shared.hpp
tools.o: tools.cpp tools.hpp

