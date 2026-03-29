
# Pensylvania Pathways

This project is a C++ pathfinding and graph analysis tool designed to evaluate routing efficiency on Pensylvania road network data. It implements and compares Dijkstra’s algorithm and A* search algorithm to determine optimal paths between nodes. The system processes large datasets with over 1 million nodes, exports results to CSV, and enables further analysis and visualization through Python. This allows for clear performance comparisons and intuitive exploration of how each algorithm behaves across different scenarios.



## Installation

In terminal run:
```bash
  pip install cosmograph pandas
```
Now install these two extensions(You can do this in the extension tab as well in vscode)
```bash
code --install-extension ms-python.python
code --install-extension ms-toolsai.jupyter
```

## Running Tests

Build and Run on Mac/Git CodeSpace:

```bash
  ./run.sh
```
Build and Run on Windows
```bash
  ./run.bat
```
Console Input(Enter Start and End Node):\
![Console Input](/resources/Console_Input.png)
-

Output:\
Terminal will print A* and Dijkstra:
- All Explored Nodes
- Explored Nodes Count
- Shortest Path Length
- Shortest Path Count

Output File Updated:\
![Output Files](/resources/Output_pathways.png)
-

## Visualization
Locate Visualize.py file in the Visualization folder\
Click on Run Cell\
![Run Cell](/resources/Options_pathways.png)

At the top Enter\
1 for A*\
2 for Dijkstra\
Let it Load (If longer than 30s restart close popup and re-run)

## Output - Displays 100k Most Relevant Nodes 
All Paths Displayed
![Output](/resources/All_Paths.png)
-
Explored Path Displayed
![Output](/resources/Explored_Path.png)
-
Shortest Path Displayed
![Output](/resources/Shortest_Path.png)
-

## Support

For support, email evanlowther12@gmail.com
