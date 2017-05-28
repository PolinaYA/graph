// wave_find_path.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

// ��������� ��� ������������� ������� ����� � ���� ������� ���������. 
// ������ � ��������� ���� �� �� ���������� �������.
struct Graph
{
	int    size;  
	char **names; 
	int  **matrix; 
};

//  ���� �� ������� ������ � ����� 
// ��� ���������� ����� ���������  vertex.
// for (int vertex = 0; vertex < graph->size; ++vertex) {
     // ���������� ������� � ������� vertex �� ����� graph
// }
// ����� �������� ��:
// foreach_vertex (vertex, graph) {
//     // ���������� ������� � ������� vertex �� ����� graph
// }
#define foreach_vertex(vertex, graph) for (int vertex = 0; vertex < graph->size; ++vertex)

// ��������� ���� �� ���������� ����� � ����� path.
Graph *load_graph(const char *path)
{
	FILE *in = fopen(path, "r");
	if (!in) {
		printf("Error: Cannot open file '%s'.\n", path);
		exit(1);
	}

	Graph *graph = new Graph;

	// ��������� ���������� ������.
	fscanf(in, "%d", &graph->size);

	// ��������� ����� ������.
	graph->names = new char*[graph->size];
	foreach_vertex(i, graph) {
		char buf[60];
		fscanf(in, "%s", buf);
		graph->names[i] = strdup(buf);
	}

	// ������� ������� ���������.
	graph->matrix = new int*[graph->size];
	foreach_vertex(i, graph) {
		graph->matrix[i] = new int[graph->size];
	}

	// ��������� ������� ���������.
	foreach_vertex(i, graph) {
		foreach_vertex(j, graph) {
			fscanf(in, "%d", &graph->matrix[i][j]);
		}
	}

	return graph;
}


void delete_graph(Graph *graph)
{
	foreach_vertex(i, graph) {
		delete[] graph->names[i];
		delete[] graph->matrix[i];
	}
	delete[] graph->names;
	delete[] graph->matrix;
}

// ����� � ����� ����������� ������ ������� � ������ name.
int find_vertex(Graph *graph, const char *name)
{
	foreach_vertex(i, graph)
		if (!strcmp(graph->names[i], name))
			return i;
	return -1;
}

// ����� �� ���������������.
void print_spaces(int count)
{
	for (int i = 0; i < count; ++i)
		printf(" ");
}

// ������� �� ������� ���� 
void print_graph(const Graph *graph)
{
	// ��������� ������������ ����� ����� �������.
	int max_name_len = 0;
	foreach_vertex(i, graph) {
		int name_len = strlen(graph->names[i]);
		if (name_len > max_name_len)
			max_name_len = name_len;
	}

	// ������� ����� ������ � ��������� ������� ���������.
	print_spaces(max_name_len + 1);
	foreach_vertex(i, graph)
		printf("%s ", graph->names[i]);
	printf("\n");

	// ����� ����� ������� ���������.
	//
	foreach_vertex(i, graph) {
		printf("%s", graph->names[i]);
		print_spaces(max_name_len - strlen(graph->names[i]) + 1);

		foreach_vertex(j, graph) {
			printf("%d", graph->matrix[i][j]);
			print_spaces(strlen(graph->names[j]));
		}

		printf("\n");
	}
}
///////////////////----------------------------------------------------------------------------------------------------------

void Diametr(Graph *graph, int number, const char *graph_file) {
	//load_graph(graph_file); ������������� �����������, ���� ���� � ������� �������?
	int **edge = new int *[graph->size];  //����������� ������� ��������� � ����������
	for (int i = 0; i < graph->size;  i++) {
		edge[i] = new int [graph->size];
	}
	for (int i = 0;i < graph->size; i++) {
		for (int j = 0; j< graph->size; j++) {
			edge[i][j] = graph->matrix[i][j];
			if (!edge[i][j]) {
				edge[i][j] = 100000;
			}
		}
	}//�������� �������������
	 //������� ���������� ���������� ����� ����� ������ ������
	for (int k = 0; k < (graph->size); k++) {   //�������� ������
		for (int i = 0; i  < graph->size; i++) {
			for (int j = 0; j < graph->size; j++) {
				if (i != j)
					edge[i][j] = min(edge[i][j], edge[i][k] + edge[k][j]);    //�� ������ ���� �������� ���������� ������� 
			}
		}
	}//���. �������� ����� ���������� ����� ����� ����� ��������� �����. ����� ������� ��������� ������� ����������� ������� ���� �����.
	printf("Distances:\n","\n");
	//cout� << "����������:�" << endl;
	for (int i = 0; i  < graph->size; i++) {
		for (int j = 0; j  < graph->size; j++) {
			if (edge[i][j] == 100000)
				edge[i][j] = 0;
			printf("%d", edge[i][j]);
		//	cout� << edge[i][j] << "�";����//����� ������� ����������
		}
		printf("\n");
	}
	int max, diameter, i, j, imax, jmax;
	diameter = -1;
	for (i = 0; i < graph->size; i++) {
		max = -1;
		for ( j = 0; j < graph->size; j++) {
			if (i != j)
			{
				if (edge[i][j] > max)//���� �����>�max
				{
					max = edge[i][j];
				}
				if (edge[i][j] > diameter) {
					imax = i;
					jmax = j;
					diameter = edge[i][j];
				}
			}
		}
	}
	printf("Diameter: ");
	printf("%d", diameter);
	printf("\n");
	printf("peripheral tops :  ");
	cout << endl << graph->names[imax] << " " << graph->names[jmax] << endl;
}

// number     ���������� ����� ��������� �������.
void run_testcase(int number, const char *graph_file)
{
	printf("\n\n[Testcase %d]\n", number);

    Graph *graph = load_graph(graph_file);


	printf("Graph: \n");
	print_graph(graph);


	Diametr(graph, number, graph_file);
	
	
	delete_graph(graph);
}

int main()
{

	run_testcase(1, "graph1.txt");
	run_testcase(2, "graph2.txt");
	run_testcase(3, "graph3.txt");
	run_testcase(4, "graph4.txt");
	run_testcase(5, "graph5.txt");

	return 0;
}

