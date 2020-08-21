# Makefile for THAdventure
CXX = g++
CXXFLAGS = -g -Wall -pedantic

all: cApp.cpp cMain.cpp GameSetup.cpp GameState.cpp Item.cpp LoopTimer.cpp Map.cpp MapNode.cpp PerformanceTimer.cpp Player.cpp PlayerNode.cpp RestartDialog.cpp SoundOptions.cpp StartDialog.cpp
	$(CXX) $(CXXFLAGS) -o THAdventure cApp.cpp cMain.cpp GameSetup.cpp GameState.cpp Item.cpp LoopTimer.cpp Map.cpp MapNode.cpp PerformanceTimer.cpp Player.cpp PlayerNode.cpp RestartDialog.cpp SoundOptions.cpp StartDialog.cpp