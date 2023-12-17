#include "menu.h"

int index = 0;


bool endsWithJSON(const std::string& str) {
    std::string jsonExtension = ".JSON";
    if (str.length() >= jsonExtension.length()) {
        return (str.compare(str.length() - jsonExtension.length(), jsonExtension.length(), jsonExtension) == 0);
    }
    else {
        return false;
    }
}

std::vector<std::string> showMenu()
{

    using namespace std;
    cout << "Projekt \"Spacer Losowy po Grafie\"" << endl << endl;
    cout << "Podawane argumenty:" << endl;
    printf("Przyk³ad 1: aaa testUltimate.JSON\n");
    printf("Przyk³ad 2: baa 20 5 5 8\n\n");
    cout << "Wybierz formê wprowadzenia grafu[char]:" << endl;
    cout << "a(1): Nazw¹ pliku.(typu JSON)" << endl;
    cout << "b(2): Specyfikacjami do loswania grafu." << endl;
    std::vector<std::string> menuSettings;
    menuSettings.push_back("");
    menuSettings.push_back("");
    char m = '0';
    int n,f,p,k;


    while (m != 'a' && m != 'b')
    {
        cin >> m;
        if (m < 97) {
            m += 48;
        }
    }
    menuSettings[0] += m;
    if (m == 'a')
    {   
        cout << endl << "WprowadŸ nazwê pliku[std::string]: ";
        cin >> menuSettings[1];
        cout << endl;
    }
    else
    {
        cout << endl << "WprowadŸ specyfikacje: " << endl;
        cout << "Wielkoœæ grafu[int]: ";
        cin >> n;
        menuSettings[1] = (to_string(n));
        cout << "Iloœæ ³uków(iloœæ ta prawdopodobnie siê zmniejszy, poniewa¿ z grafu usuwane cykle)[int]: ";
        cin >> f;
        menuSettings.push_back(to_string(f));
        cout << "Iloœæ wierzcho³ków pocz¹tkowych(takich bez ³uków wejœciowych)[int]: ";
        cin >> p;
        menuSettings.push_back(to_string(p));
        cout << "Iloœæ wierzcho³ków koñcowych(takich bez ³uków wyjœciowych)[int]: ";
        cin >> k;
        menuSettings.push_back(to_string(k));
        if (p + k > n) {
            cout << "\tPodana wielkoœæ grafu, jest mniejsza ni¿ suma wierzcho³ków pocz¹tkowych i koñcowych." << endl;
            n = p + k;
            menuSettings[1] = to_string(n);
            cout << "\tNowa wielkoœæ grafu to " << n << ". Iloœæ wierzcho³ków pocz¹tkowych i koñcowych pozosta³a bez zmian" << endl;
        }
    }

    m = '0';
    cout << endl << "Wybierz pytanie na które pytanie chcesz uzyskaæ odpowiedŸ[char]:" << endl;
    cout << "a(1): Jakie jest prawdopodobieñstwo dostania siê do ka¿dego z wierzcho³ków koñcowych?" << endl;
    cout << "b(2): Do jakiego wierzcho³ka koñcowego dostanê siê najprawdopodobniej?" << endl;
    while (m != 'a' && m != 'b')
    {   
        cin >> m;
        if (m < 97) {
            m += 48;
        }       
    }
    menuSettings[0] += m;
    m = '0';
    cout << endl << "Wybierz sposób uzyskania odpowiedzi[char]:" << endl;
    if (menuSettings[0][1] == 'a')
    {
        cout << "a(1): Klasyczna metoda macierzowa." << endl;
        cout << "b(2): Brute Force(algorytm pe³nego przegl¹du rozwi¹zañ)." << endl;
        while (m != 'a' && m != 'b')
        {
            cin >> m;
            if (m < 97) {
                m += 48;
            }
        }
    }
    else
    {
        cout << "a(1): Klasyczna metoda macierzowa." << endl;
        cout << "b(2): Brute Force(algorytm pe³nego przegl¹du rozwi¹zañ)." << endl;
        cout << "c(3): Algorytm zach³anny(wybiera zawsze najbardziej prawdopodobny krok w danym momencie)." << endl;
        while (m != 'a' && m != 'b' && m != 'c')
        {
            cin >> m;
            if (m < 97) {
                m += 48;
            }
        }
    }
    menuSettings[0] += m;

    return menuSettings;
}

Graph* graphFromSettings(std::vector<std::string> settings)
{
    index = 0;
    Graph* graph = nullptr;
    if (settings[index][0] == 'a')
    {
        index += 1;
        try {
            graph = new Graph(ImportJSON(settings[index]));
        }
        catch (...)
        {
            std::cout << "Sth went wrong, sorry :(\n";
            exit(0);
        }
        index += 1;
    }
    else
    {
        index += 1;
        try {
            int n = stoi(settings[index++]),
                f = stoi(settings[index++]),
                s = stoi(settings[index++]),
                k = stoi(settings[index++]);
            graph = new Graph(graphGenerator(n, f, s, k));

        }
        catch (...)
        {
            std::cout << "Sth went wrong, sorry :(\n";
            exit(0);
        }
    }
    return graph;
}

void actionFromSettings(std::vector<std::string> settings, Graph* graph)
{
    double suma;
    std::vector<std::vector<double>> ansMatrix;
    std::vector<double> valVector;
    std::vector<int> ansVector;
    switch (settings[0][1])
    {
    case 'a':
        switch (settings[0][2])
        {
        case 'a':
            ansMatrix = graph->klasycznaMetodaMacierzowa();
            
            break;
        case 'b':
            for (int i = 0; i < graph->size - graph->endNodes.size(); i++)
            {
                ansMatrix.push_back(graph->bruteForceStart(&graph->nodes[i]));
            }
            break;

        default:
            exit(0);
            break;
        }
        for (int i = 0; i < ansMatrix.size(); i++)
        {
            suma = 0;
            std::cout << std::endl << "Z wierzcho³ka " << i << ":\n";
            for (int j = 0; j < ansMatrix[i].size(); j++)
            {
                std::cout << "\tdo " << graph->endNodes[j]->index << ": " << ansMatrix[i][j] << "\n";
                suma += ansMatrix[i][j];
            }
            std::cout << "\t\tsuma:" << suma << std::endl;
        }
        break;

    case 'b':
        switch (settings[0][2])
        {
        case 'a':
            ansMatrix = graph->klasycznaMetodaMacierzowa();
            for (int i = 0; i < ansMatrix.size(); i++)
            {
                valVector.push_back(ansMatrix[i][0]);
                ansVector.push_back(graph->endNodes[0]->index);
                for (int j = 0; j < ansMatrix[i].size(); j++)
                {
                    if (ansMatrix[i][j] > valVector[i]) {
                        valVector[i] = ansMatrix[i][j];
                        ansVector[i] = graph->endNodes[j]->index;
                    }
                }
            }
            break;
        case 'b':
            for (int i = 0; i < graph->size - graph->endNodes.size(); i++)
            {
                ansMatrix.push_back(graph->bruteForceStart(&graph->nodes[i]));
                valVector.push_back(ansMatrix[i][0]);
                ansVector.push_back(graph->endNodes[0]->index);
                for (int j = 0; j < ansMatrix[i].size(); j++)
                {
                    if (ansMatrix[i][j] > valVector[i]) {
                        valVector[i] = ansMatrix[i][j];
                        ansVector[i] = graph->endNodes[j]->index;
                    }
                }
            }
            break;
        case 'c':
            for (int i = 0; i < graph->size - graph->endNodes.size(); i++)
            {
                ansVector.push_back(graph->greedyAnswer(&graph->nodes[i]));
            }
            break;
        default:
            exit(0);
            break;
        }

        for (int i = 0; i < ansVector.size(); i++)
        {
            std::cout << i << " -> " << ansVector[i] << "\n";
        }

        break;
    default:
        exit(0);
    }
}

Graph bruteMakeAndShow(int n, int f, int staring, int ending)
{
    using namespace std;

    vector<vector<double>> x = graphGenerator(n, f, staring, ending);
    Graph g(x);
    for (int i = 0; i < g.size - g.endNodes.size(); i++)
    {
        g.bruteForceStart(&g.nodes[i]);
        cout << endl;
    }
    return g;
}

void bruteShow(Graph& g)
{
    using namespace std;
    for (int i = 0; i < g.size - g.endNodes.size(); i++)
    {
        cout << "---------------" << i << "---------------\n";
        g.bruteForceStart(&g.nodes[i]);
        cout << endl;
    }
}

void makingJSONfile(int n, int f, int staring, int ending, std::string fileName)
{
    using namespace std;
    using namespace rapidjson;
    if (!endsWithJSON(fileName))
        fileName += ".JSON";
   

    vector<vector<double>> x = graphGenerator(n, f, staring, ending);

    Document document;
    document.SetObject();

    // Tworzenie tablicy 2D w formacie JSON
    Value matrix(kArrayType);
    n = x.size();
    for (int i = 0; i < n; i++) {
        Value row(kArrayType);
        for (int j = 0; j < n; j++) {
            row.PushBack(x[i][j], document.GetAllocator());
        }
        matrix.PushBack(row, document.GetAllocator());
    }

    // Dodawanie tablicy 2D do obiektu JSON
    document.AddMember("matrix", matrix, document.GetAllocator());

    // Zapisywanie danych JSON do pliku
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    // Zapis do pliku
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << buffer.GetString() << endl;
        outputFile.close();
        cout << "Dane zosta³y zapisane do pliku: " << fileName << endl;
    }
    else {
        cout << "Nie mo¿na otworzyæ pliku do zapisu." << endl;
    }
}

std::vector<std::vector<double>> ImportJSON(std::string fileName)
{
    using namespace std;
    using namespace rapidjson;
    if (!endsWithJSON(fileName))
        fileName += ".JSON";

    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Cannot open file ." << fileName << endl;
        exit(0);
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string jsonString = buffer.str();

    Document document;
    document.Parse(jsonString.c_str());

    if (document.HasParseError()) {
        cout << "B³¹d parsowania pliku JSON." << endl;
        exit(0);
    }

    if (!document.HasMember("matrix") || !document["matrix"].IsArray()) {
        cout << "Brak elementu 'matrix' lub nie jest to tablica." << endl;
        exit(0);
    }

    const Value& matrix = document["matrix"];

    vector<vector<double>> x;
    for (SizeType i = 0; i < matrix.Size(); ++i) {
        if (!matrix[i].IsArray()) {
            cout << "Element " << i << " w 'matrix' nie jest tablic¹." << endl;
            exit(0);
        }

        vector<double> row;
        for (SizeType j = 0; j < matrix[i].Size(); ++j) {
            if (!matrix[i][j].IsFloat()) {
                cout << "Element " << i << "," << j << " w 'matrix' nie jest liczb¹ zmiennoprzecinkow¹." << endl;
                exit(0);
            }
            row.push_back(matrix[i][j].GetFloat());
        }
        x.push_back(row);
    }

    return x;
}
