#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#include <chrono>

using namespace std;

int bfs(vector<vector<int>> &adjList, int startNode)
{
    int vertices = adjList.size();
    vector<bool> visited(vertices, false);
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);

    int maxDistance = 0;

    while (!q.empty())
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i)
        {
            int currentNode = q.front();
            q.pop();

            for (int neighbour : adjList[currentNode])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
        maxDistance++; // Increment maxDistance after processing each level
    }

    return maxDistance - 1;
}

void addEdge(vector<vector<int>> &adjList, int u, int v)
{
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    ifstream input("./tests/server.i5");
    ofstream output("./tests/server.out");
    // ifstream input("server.in");
    // ofstream output("server.out");

    int minMaxDistance = 0;
    int tempDistance = 0;
    vector<int> servers;
    string line;

    getline(input, line);
    int vertices = stoi(line);
    vector<vector<int>> adjList(vertices + 1);

    while (getline(input, line))
    {
        if (line == "0 0")
        {
            break;
        }
        int u = stoi(line.substr(0, line.find(" ")));
        int v = stoi(line.substr(line.find(" ") + 1));
        addEdge(adjList, u, v);
    }

    // cout << "Adjacency List:" << endl;
    // for (int i = 0; i < adjList.size(); i++)
    // {
    //     cout << "Node " << i << ": ";
    //     for (int j = 0; j < adjList[i].size(); j++)
    //     {
    //         cout << adjList[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    minMaxDistance = bfs(adjList, 1);

    for (int v = 1; v < vertices + 1; v++)
    {
        tempDistance = bfs(adjList, v);
        cout << "Temp Distance: " << tempDistance << " for node " << v << endl;
        if ((tempDistance == minMaxDistance) && tempDistance != 0)
        {
            servers.push_back(v);
            minMaxDistance = tempDistance;
        }
        else if (tempDistance < minMaxDistance)
        {
            servers.clear();
            servers.push_back(v);
            minMaxDistance = tempDistance;
        }
    }

    cout << "MinMax Distance: " << minMaxDistance << endl;
    output << minMaxDistance << endl;
    cout << "Servers: ";
    for (int s : servers)
    {
        output << s << " ";
        cout << s << " ";
    }

    input.close();
    output.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}