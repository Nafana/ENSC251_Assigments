#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

template <typename S, typename T>
struct Tuple
{
    S first;
    T second;
};

struct DataSetColumn
{
    string classification;
    vector<float> *values;
};

struct DataTreeNode;
struct DecisionTreeNode
{
    int attributeId;
    float attributeCutoff;
    DataTreeNode *smallerNode = nullptr;
    DataTreeNode *biggerEqualNode = nullptr;
};

struct DataTreeNode
{
    vector<DataSetColumn *> *dataSet = nullptr;
    DecisionTreeNode *nextDecision = nullptr;
};

void print_dataset(vector<DataSetColumn *> *dataSet);
void fill_dataset(vector<DataSetColumn *> *dataSet, ifstream &inputStream, char delimiter);
Tuple<string, string> *get_dataset_classifiers(vector<DataSetColumn *> *dataSet);
Tuple<int, int> *get_dataset_classifierQuantity(vector<DataSetColumn *> *dataSet, Tuple<string, string> *datasetClassifiers);
float id3_calcEntropy(vector<DataSetColumn *> *dataSet, Tuple<int, int> *classifiersQuantity);
Tuple<int, int> *get_attributesplit_quantity(vector<DataSetColumn *> *dataSet, int attributeId, float splitValue);
float _half_entropy(float ratio);
float calc_entropy(Tuple<int, int> *classifiersQuantity);
float id3_get_systemEntropy(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers);
Tuple<int, float> *id3_find_bestSplitAttribute(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers);
float id3_calc_entropyAfterSplit(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers, int attributeId, float maximumSplitValue);
float calc_weighted_entropy(Tuple<int, int> *firstFactor, Tuple<int, int> *secondFactor, float firstEntropy, float secondEntropy);
float calc_entropy(float first, float second);
bool id3_is_nodeHomogeneous(vector<DataSetColumn *> *dataSet);
void id3(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers, DecisionTreeNode *rootDecision);
void id3_splitNode(vector<DataSetColumn *> *dataSet, DecisionTreeNode *toSplitAt, int attributeId, float splitValue);
string get_tree_spaces(int leafLevel);
void id3_print_choiceTree(DecisionTreeNode *rootDecision, int leafLevel, Tuple<string, string> *datasetClassifiers);

int main(int argc, char **argv)
{
    char dataDelimiter = ',';
    char *fileName = new char[25];
    vector<DataSetColumn *> *dataSet = new vector<DataSetColumn *>();
    Tuple<string, string> *systemClassifiers = new Tuple<string, string>();
    DecisionTreeNode *mainNode = new DecisionTreeNode();
    float systemEntropy = 0;

    fileName = argv[1];

    ifstream inputStream;
    inputStream.open(fileName);

    // Fill the dataset with all the data
    fill_dataset(dataSet, inputStream, dataDelimiter);
    // Get the system classifiers
    systemClassifiers = get_dataset_classifiers(dataSet);

    id3(dataSet, systemClassifiers, mainNode);
    id3_print_choiceTree(mainNode, 0, systemClassifiers);

    delete fileName, dataSet, systemClassifiers, mainNode;
    fileName, dataSet, systemClassifiers, mainNode = nullptr;
}

void print_dataset(vector<DataSetColumn *> *dataSet)
{
    for (int i = 0; i < dataSet->size(); i++)
    {
        DataSetColumn *column = dataSet->at(i);
        cout << column->classification << " ";
        for (int i = 0; i < column->values->size(); i++)
        {
            cout << column->values->at(i) << " ";
        }
        cout << endl;
    }
}

void fill_dataset(vector<DataSetColumn *> *dataSet, ifstream &inputStream, char delimiter)
{
    string currentLine = "";
    string currentString = "";
    int lineLength = -1;
    while (getline(inputStream, currentLine))
    {
        lineLength = currentLine.length();
        DataSetColumn *addedColumn = new DataSetColumn();
        addedColumn->values = new vector<float>();

        for (int i = 0; i < lineLength; i++)
        {
            if (currentLine.at(i) == delimiter)
            {
                addedColumn->values->push_back(stof(currentString));
                currentString = "";
            }
            else if (i == (lineLength - 1))
            {
                currentString += currentLine.at(i);
                addedColumn->classification = currentString;
                currentString = "";
            }
            else
            {
                currentString += currentLine.at(i);
            }
        }

        dataSet->push_back(addedColumn);
    }
}

// Gets the classifiers for the dataset, our implementation assumes two classifiers
Tuple<string, string> *get_dataset_classifiers(vector<DataSetColumn *> *dataSet)
{
    Tuple<string, string> *classifiers = new Tuple<string, string>();
    if (dataSet->size() < 2)
    {
        throw "Cannot classify a dataset with 1 or less classifiers.";
    }
    classifiers->first = dataSet->at(0)->classification;
    for (int i = 0; i < dataSet->size(); i++)
    {
        if (dataSet->at(i)->classification != classifiers->first)
        {
            classifiers->second = dataSet->at(i)->classification;
            return classifiers;
        }
    }
    throw "Only found one type of classifier, a second classifier needs to be present.";
}

Tuple<int, int> *get_dataset_classifierQuantity(vector<DataSetColumn *> *dataSet, Tuple<string, string> *datasetClassifiers)
{
    Tuple<int, int> *classifiersQuantity = new Tuple<int, int>();
    classifiersQuantity->first, classifiersQuantity->second = 0;
    for (int i = 0; i < dataSet->size(); i++)
    {
        if (dataSet->at(i)->classification == datasetClassifiers->first)
        {
            classifiersQuantity->first++;
        }
        else if (dataSet->at(i)->classification == datasetClassifiers->second)
        {
            classifiersQuantity->second++;
        }
    }
    return classifiersQuantity;
}

// The first part of the tupple is the less than, the second part is the greater or equal to
Tuple<int, int> *get_attributesplit_quantity(vector<DataSetColumn *> *dataSet, int attributeId, float splitValue)
{
    Tuple<int, int> *attributeSplit = new Tuple<int, int>();
    attributeSplit->first = 0;
    attributeSplit->second = 0;
    for (int i = 0; i < dataSet->size(); i++)
    {
        if (dataSet->at(i)->values->at(attributeId) < splitValue)
        {
            attributeSplit->first++;
        }
        else
        {
            attributeSplit->second++;
        }
    }
    return attributeSplit;
}

float _half_entropy(float ratio)
{
    if (ratio == 0.0f)
    {
        return 0.0f;
    }
    else
    {
        return -ratio * log2f(ratio);
    }
}

float calc_entropy(Tuple<int, int> *classifiersQuantity)
{
    int totalElements = classifiersQuantity->first + classifiersQuantity->second;
    float ratio_first = classifiersQuantity->first == 0.0f ? 0.0f : (float)(classifiersQuantity->first) / (float)(totalElements);
    float ratio_second = classifiersQuantity->second == 0.0f ? 0.0f : (float)(classifiersQuantity->second) / (float)(totalElements);
    return _half_entropy(ratio_first) + _half_entropy(ratio_second);
}

float calc_entropy(float first, float second)
{
    float total = first + second;
    return _half_entropy(first / total) + _half_entropy(second / total);
}

float id3_get_systemEntropy(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers)
{
    return calc_entropy(get_dataset_classifierQuantity(dataSet, systemClassifiers));
}

float calc_weighted_entropy(Tuple<int, int> *firstFactor, Tuple<int, int> *secondFactor, float firstEntropy, float secondEntropy)
{
    int firstSum = firstFactor->first + firstFactor->second;
    int secondSum = secondFactor->first + secondFactor->second;
    int total = firstSum + secondSum;
    return ((float)firstSum / (float)total) * firstEntropy + ((float)secondSum / (float)total) * secondEntropy;
}

// Counts classifiers after split
float id3_calc_entropyAfterSplit(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers, int attributeId, float maximumSplitValue)
{
    float entropySmaller = 0;
    float entropyBiggerEqual = 0;
    Tuple<int, int> *smaller_ratio = new Tuple<int, int>();
    Tuple<int, int> *biggerEqual_ratio = new Tuple<int, int>();
    for (int i = 0; i < dataSet->size(); i++)
    {
        if (dataSet->at(i)->values->at(attributeId) < maximumSplitValue)
        {
            if (dataSet->at(i)->classification == systemClassifiers->first)
            {
                smaller_ratio->first++;
            }
            else
            {
                smaller_ratio->second++;
            }
        }
        else
        {
            if (dataSet->at(i)->classification == systemClassifiers->first)
            {
                biggerEqual_ratio->first++;
            }
            else
            {
                biggerEqual_ratio->second++;
            }
        }
    }

    entropySmaller = calc_entropy(smaller_ratio->first, smaller_ratio->second);
    entropyBiggerEqual = calc_entropy(biggerEqual_ratio->first, biggerEqual_ratio->second);
    return calc_weighted_entropy(smaller_ratio, biggerEqual_ratio, entropySmaller, entropyBiggerEqual);
}

Tuple<int, float> *id3_find_bestSplitAttribute(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers)
{
    float systemEntropy = id3_get_systemEntropy(dataSet, systemClassifiers);
    float currentEntropy = 0;
    float splitEntropy = 0;
    Tuple<int, float> *bestSplit = new Tuple<int, float>();
    bestSplit->first = -1;
    bestSplit->second = 0.0f;
    for (int i = 0; i < dataSet->size(); i++)
    {
        for (int j = 0; j < dataSet->at(i)->values->size(); j++)
        {
            splitEntropy = systemEntropy - id3_calc_entropyAfterSplit(dataSet, systemClassifiers, j, dataSet->at(i)->values->at(j));
            if (splitEntropy > currentEntropy)
            {
                bestSplit->first = j;
                bestSplit->second = dataSet->at(i)->values->at(j);
                currentEntropy = splitEntropy;
            }
        }
    }
    return bestSplit;
}

bool id3_is_nodeHomogeneous(vector<DataSetColumn *> *dataSet)
{
    if (dataSet->size() == 1)
    {
        return true;
    }
    string firstValue = dataSet->at(0)->classification;
    for (int i = 0; i < dataSet->size(); i++)
    {
        if (dataSet->at(i)->classification != firstValue)
        {
            return false;
        }
    }
    return true;
}

void id3_splitNode(vector<DataSetColumn *> *dataSet, DecisionTreeNode *toSplitAt, int attributeId, float splitValue)
{
    vector<DataSetColumn *> *smallerSplit = new vector<DataSetColumn *>();
    vector<DataSetColumn *> *largerSplit = new vector<DataSetColumn *>();
    DataTreeNode *smallerNode = new DataTreeNode();
    DataTreeNode *largerNode = new DataTreeNode();
    smallerNode->nextDecision = new DecisionTreeNode();
    largerNode->nextDecision = new DecisionTreeNode();
    for (int i = 0; i < dataSet->size(); i++)
    {
        if (dataSet->at(i)->values->at(attributeId) < splitValue)
        {
            smallerSplit->push_back(dataSet->at(i));
        }
        else
        {
            largerSplit->push_back(dataSet->at(i));
        }
    }
    smallerNode->dataSet = smallerSplit;
    largerNode->dataSet = largerSplit;
    toSplitAt->attributeCutoff = splitValue;
    toSplitAt->attributeId = attributeId;
    toSplitAt->smallerNode = smallerNode;
    toSplitAt->biggerEqualNode = largerNode;
}

void id3(vector<DataSetColumn *> *dataSet, Tuple<string, string> *systemClassifiers, DecisionTreeNode *rootDecision)
{
    if (!id3_is_nodeHomogeneous(dataSet))
    {
        Tuple<int, float> *bestSplit = id3_find_bestSplitAttribute(dataSet, systemClassifiers);
        rootDecision->attributeId = bestSplit->first;
        rootDecision->attributeCutoff = bestSplit->second;
        id3_splitNode(dataSet, rootDecision, bestSplit->first, bestSplit->second);
        id3(rootDecision->smallerNode->dataSet, systemClassifiers, rootDecision->smallerNode->nextDecision);
        id3(rootDecision->biggerEqualNode->dataSet, systemClassifiers, rootDecision->biggerEqualNode->nextDecision);
    }
}

string get_tree_spaces(int leafLevel)
{
    string spaces = "";
    for (int i = 0; i < leafLevel; i++)
    {
        spaces += " ";
    }
    return spaces;
}

void id3_print_choiceTree(DecisionTreeNode *rootDecision, int leafLevel, Tuple<string, string> *datasetClassifiers)
{
    if (rootDecision->smallerNode == nullptr || rootDecision->smallerNode == nullptr)
    {
        return;
    }
    int nextLevel = leafLevel + 2;
    cout << get_tree_spaces(leafLevel) << "Decision: Attribute(" << rootDecision->attributeId << ") >= " << rootDecision->attributeCutoff << endl;
    Tuple<int, int> *biggerNodeQuantities = get_dataset_classifierQuantity(rootDecision->smallerNode->dataSet, datasetClassifiers);
    cout << get_tree_spaces(leafLevel) << "  '" << datasetClassifiers->second << "': " << biggerNodeQuantities->first << endl;
    cout << get_tree_spaces(leafLevel) << "  '" << datasetClassifiers->first << "': " << biggerNodeQuantities->second << endl;
    id3_print_choiceTree(rootDecision->smallerNode->nextDecision, nextLevel, datasetClassifiers);

    cout << get_tree_spaces(leafLevel) << "Decision: Attribute(" << rootDecision->attributeId << ") < " << rootDecision->attributeCutoff << endl;
    Tuple<int, int> *smallerNodeQuantities = get_dataset_classifierQuantity(rootDecision->biggerEqualNode->dataSet, datasetClassifiers);
    cout << get_tree_spaces(leafLevel) << "  '" << datasetClassifiers->second << "': " << smallerNodeQuantities->first << endl;
    cout << get_tree_spaces(leafLevel) << "  '" << datasetClassifiers->first << "': " << smallerNodeQuantities->second << endl;
    id3_print_choiceTree(rootDecision->biggerEqualNode->nextDecision, nextLevel, datasetClassifiers);

    delete biggerNodeQuantities, smallerNodeQuantities;
    biggerNodeQuantities, smallerNodeQuantities = nullptr;
}
