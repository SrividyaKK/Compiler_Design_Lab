#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
using namespace std;

int nStates, nInputSymb;
int indexOf(char item, char states[]);
void findClosure(char states[], string transitions[][20], int start);

int main()
{
    int i, j;
    cout << "Enter the number of states: ";
    cin >> nStates;
    char states[nStates];
    cout << "Enter the states: ";
    for (i = 0; i < nStates; i++)
        cin >> states[i];

    cout << "Enter the number of input symbols (including epsilon): ";
    cin >> nInputSymb;
    char inputSymbs[nInputSymb];
    cout << "Enter the input symbols (excluding epsilon): ";
    for (i = 0; i < nInputSymb - 1; i++)
        cin >> inputSymbs[i];
    inputSymbs[i] = 'e';

    cout << "Enter the transitions: \n";
    cout << "States \t";
    for (i = 0; i < nInputSymb; i++)
        cout << inputSymbs[i] << "\t";
    cout << "\n-------------------------------------------------------------------\n";

    string transitions[nStates][20];
    string tranState;
    for (i = 0; i < nStates; i++)
    {
        cout << states[i] << "\t";
        for (j = 0; j < nInputSymb; j++)
        {
            cin >> tranState;
            transitions[i][j] = tranState;
        }
    }

    cout << "e-closures: \n----------------------------\n";
    for (i = 0; i < nStates; i++)
    {
        findClosure(states, transitions, i);
    }
    return 0;
}

int indexOf(char item, char states[])
{
    for (int i = 0; i < nStates; i++)
        if (states[i] == item)
            return i;
    return -1;
}

void findClosure(char states[], string transitions[][20], int start)
{
    vector<char> closure;
    stack<char> s;
    string trans;
    s.push(states[start]);
    unordered_set<char> visited;
    while (!s.empty())
    {
        char t = s.top();
        s.pop();
        if (visited.find(t) != visited.end())
        {
            // the node is visited, so stop
            continue;
        }
        visited.insert(t);
        trans = transitions[indexOf(t, states)][nInputSymb - 1];
        for (char x : trans)
            if (x != '-')
                s.push(x);
        closure.push_back(t);
    }
    cout << states[start] << ": \t";
    for (auto x : closure)
        cout << x << " ";
    cout << "\n";
}