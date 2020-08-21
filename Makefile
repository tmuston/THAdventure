# Makefile for THAdventure
CXX = g++
CXXFLAGS = -g -Wall -pedantic

all: cApp.cpp cMain.cpp GameSetup.cpp GameState.cpp Item.cpp LoopTimer.cpp Map.cpp MapNode.cpp PerformanceTimer.cpp Player.cpp PlayerNode.cpp RestartDialog.cpp SoundOptions.cpp StartDialog.cpp
	$(CXX) $(CXXFLAGS) -o THAdventure cApp.o cMain.o GameSetup.o GameState.o Item.o LoopTimer.o Map.o MapNode.o PerformanceTimer.o Player.o PlayerNode.o RestartDialog.o SoundOptions.o StartDialog.o