#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct ValueNode
{
    int nodeId;
    int payload;
    ValueNode *nextNode = nullptr;
};

struct Clause
{
    ValueNode *rootValue;
};

int readNextValue(ifstream &stream, string &stringBuffer, int &intBuffer);
bool _verifyFileSyntaxType(ifstream &stream);
void generateProposedSolution(int *solutionSet, const int solutionSetSize);
void insertProposedSolution(int *solutionSet, const int solutionSetSize, vector<Clause *> *problemSet);
bool verifyProposedSolution(int *solutionSet, const int solutionSetSize, vector<Clause *> *problemSet);

int main()
{
    const int DEF_PAYLOAD = 0;
    int NUM_CLAUSES = 0;
    int NUM_VARIABLES = 0;

    bool satSolved = false;

	char* satFile = new char[50];
    string currentInput = "";
    int currentInputBuffer = 0;

    int *proposedSolution = new int[NUM_VARIABLES];
    vector<Clause *> *satClauses = new vector<Clause *>;
	
	cout << "Please enter the name of the file (ex.. data.cnf): " << endl;
	cout << "~ NOTE: File names should contain no more than 50 characters, some versions of the g++ compiler complain about writing into std::string" << endl;
	cin >> satFile;

    ifstream satStream;
    satStream.open(satFile);

    _verifyFileSyntaxType(satStream);
    NUM_VARIABLES = readNextValue(satStream, currentInput, currentInputBuffer);
    NUM_CLAUSES = readNextValue(satStream, currentInput, currentInputBuffer);

    if (NUM_VARIABLES == 0 || NUM_CLAUSES == 0) {
        cout << "No solution to this SAT problem." << endl;
        satStream.close();
        delete [] proposedSolution;
        proposedSolution = nullptr;
        delete satClauses;
        satClauses == nullptr;
    }

    for (int i = 0; i < NUM_CLAUSES; i++)
    {
        Clause *addedClause = new Clause();
        while (readNextValue(satStream, currentInput, currentInputBuffer) != 0 && !satStream.eof())
        {
            ValueNode *addedClauseVariable = new ValueNode;
            addedClauseVariable->nodeId = currentInputBuffer;
            addedClauseVariable->payload = DEF_PAYLOAD;
            addedClauseVariable->nextNode = addedClause->rootValue;
            addedClause->rootValue = addedClauseVariable;
        }
        satClauses->push_back(addedClause);
    }
	
	cout << endl << "Searching for a solution..." << endl;

    while (!satSolved)
    {
        generateProposedSolution(proposedSolution, NUM_VARIABLES);
        insertProposedSolution(proposedSolution, NUM_VARIABLES, satClauses);
        satSolved = verifyProposedSolution(proposedSolution, NUM_VARIABLES, satClauses);
    }

    satStream.close();

    cout << endl
         << "Found Proposed Solution..." << endl;
    for (int i = 0; i < NUM_VARIABLES; i++)
    {
        cout << "X(" << (i + 1) << ")=" << proposedSolution[i] << endl;
    }

    cout << endl;
	
	delete [] satFile, proposedSolution;
	delete satClauses;
	satFile, proposedSolution, satClauses = nullptr;

    return 0;
}

int readNextValue(ifstream &stream, string &stringBuffer, int &intBuffer)
{
    stream >> stringBuffer;
    intBuffer = stoi(stringBuffer);
    return intBuffer;
}

bool _verifyFileSyntaxType(ifstream &stream)
{
    string input = "";
    string fileType = "";
    stream >> input;
    stream >> fileType;
    return input != "p" && fileType != "cnf" ? true : false;
}

// 0 is false, 1 is true
void generateProposedSolution(int *solutionSet, const int solutionSetSize)
{
    for (int i = 0; i < solutionSetSize; i++)
    {
        solutionSet[i] = rand() % 2;
    }
}

void insertProposedSolution(int *solutionSet, const int solutionSetSize, vector<Clause *> *problemSet)
{
    for (int i = 0; i < problemSet->size(); i++)
    {
        Clause *clause = problemSet->at(i);
        ValueNode *valueNode = clause->rootValue;
        while (valueNode != nullptr)
        {
            valueNode->payload = solutionSet[abs(valueNode->nodeId) - 1];
            valueNode = valueNode->nextNode;
        }
    }
}

bool verifyProposedSolution(int *solutionSet, const int solutionSetSize, vector<Clause *> *problemSet)
{
    bool foundClauseSolution = false;
    for (int i = 0; i < problemSet->size(); i++)
    {
        ValueNode *rootValue = problemSet->at(i)->rootValue;
        while (rootValue != nullptr)
        {
            switch (rootValue->nodeId > 0)
            {
            case true:
                // Positive value, need 1
                foundClauseSolution = solutionSet[abs(rootValue->nodeId) - 1] == 1 ? true : false;
                break;
            case false:
                // Positive value, need 0
                foundClauseSolution = solutionSet[abs(rootValue->nodeId) - 1] == 0 ? true : false;
                break;
            }
            if (foundClauseSolution)
                break;
            rootValue = rootValue->nextNode;
        }
        if (!foundClauseSolution)
        {
            return false;
        }
        else
        {
            foundClauseSolution = false;
        }
    }
    return true;
}