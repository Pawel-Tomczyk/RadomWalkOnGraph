#pragma once
#include "Graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


Graph bruteMakeAndShow(int n, int f, int staring, int ending);
void bruteShow(Graph& g);
void makingJSONfile(int n, int f, int staring, int ending, std::string fileName);
std::vector<std::vector<double>> ImportJSON(std::string fileName);
bool endsWithJSON(const std::string& str);

std::vector<std::string> showMenu();
Graph* graphFromSettings(std::vector<std::string> settings);
void actionFromSettings(std::vector<std::string> settings, Graph* graph);
