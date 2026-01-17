CXX = g++

CXXFLAGS = -std=c++11 -Wall

OBJS = main.o hashtable.o rand.o tokenizer.o test.o

run : $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o : test.hpp
test.o : test.hpp
hashtable.o: hashtable.hpp
rand.o: rand.hpp
tokenizer.o: tokenizer.hpp
clean :
				rm $(OBJS)