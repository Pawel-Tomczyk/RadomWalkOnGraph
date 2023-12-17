#include "Graph.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


      //MAKING JSON FILE 
using namespace std;
using namespace rapidjson;

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1250);

    //int n = 90, f = 10, starting = 3, ending = 3;
    //string fileName = "test9";
    //vector<vector<double>> x = ImportJSON(fileName);
    //Graph g(x);
    //makingJSONfile(n, f, starting, ending, fileName);
    //g.klasycznaMetodaMacierzowa();
    vector<string> x;
    if (argc > 1) {
        for (int i = 1; i < argc; i++)
        {
            x.push_back(argv[i]);
        }
    }
    else {
        x = showMenu();
    }
    Graph* graph = graphFromSettings(x);
    actionFromSettings(x, graph);
}