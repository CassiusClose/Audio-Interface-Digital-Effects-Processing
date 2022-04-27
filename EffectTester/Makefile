CC=g++
CFLAGS=-Wall -Werror -std=c++11 
DEPS = effect.h tremolo.h delay.h
CPPS = tester.cpp

default: $(DEPS) $(CPPS)
	$(CC) -o EffectTester $(CFLAGS) $(CPPS) -lsndfile 
