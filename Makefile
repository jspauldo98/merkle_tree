# Jared Spaulding
# 11/9/2017
# makefile for merkle tree project

output: vote.o bTREE.o pMT.o
	g++ -std=c++11 vote.o bTREE.o pMT.o -o vote
	make clean
	vote.exe

vote.o: vote.cpp
	g++ -c vote.cpp

bTREE.o: bTREE.cpp
	g++ -c bTREE.cpp

pMT.o: pMT.cpp
	g++ -c pMT.cpp

# del only works for windows machines
# use rm for linux and mac
clean:
	del *.o output
