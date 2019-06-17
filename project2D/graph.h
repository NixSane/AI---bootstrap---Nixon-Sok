#pragma once
#include <vector>
#include <list>
#include <algorithm>

#include "node.h"
#include "edge.h"


template<typename T>
class graph
{
public:
	graph<T>() 
	{
		for (auto node : m_nodes)
		{
			delete node;
		}
		for (auto edge : m_edges)
		{
			delete edge;
		}
	}
	~graph() {}

	// Makes a new node
	node<T>* create_node(const T& a_data)
	{
		node<T>* new_node = new node<T>(a_data);
		m_nodes.push_back(new_node);
		return new_node;
	}

	// Makes a new edge between two nodes
	edge<T>* create_edge(node<T>* a_node_A, node<T>* a_node_B) 
	{
		edge<T>* new_edge = new edge<T>(a_node_A, a_node_B);
		m_edges.push_back(new_edge);
		return new_edge;
	}

	// Removes a node from graph
	void remove_node(node<T>* a_node)
	{
		while (a_node->m_edges.size() > 0)
		{
			remove_edge(a_node->m_edges.at(0));
		}

		a_node->disconnect();
		auto iter = std::find(m_nodes.begin(), m_nodes.end(), a_node);
		delete (*iter);
		m_nodes.erase(iter);
	}

	// Removes the edge from graph
	void remove_edge(edge<T>* a_edge)
	{
		a_edge->m_nodes[0]->remove_edge(a_edge);
		a_edge->m_nodes[1]->remove_edge(a_edge);

		auto iter = std::find(m_edges.begin(), m_edges.end(), a_edge);
		delete(*iter);
		m_edges.erase(iter);
	}

//private:
	std::vector<node<T>*> m_nodes;
	std::vector<edge<T>*> m_edges;

	std::vector<node<T>*> m_path;

	std::vector<node<T>*>& calculate_path_dijkstras(node<T>* a_start_node, node<T>* a_other_node)
	{
		for (auto& a_node : m_nodes)
		{
			a_node->reset();
		}
		m_path.clear();

		// Validate the input
		if (!a_start_node || !a_other_node)
		{
			return m_path;
		}

		if (a_start_node == a_other_node)
		{
			m_path.push_back(a_start_node);
			return m_path;
		}

		std::list<node<T>*> open_list;
		std::list<node<T>*> closed_list;

		// Add startNode to openList
		open_list.push_back(a_start_node);

		node<T>* current_node;
		//while openList is not empty
		while (open_list.size())
		{
			current_node = open_list.front();
			open_list.pop_front();

			//Add currentNode to closeList
			closed_list.push_back(current_node);

			// For all connections c in currentNode
			for (auto& a_edges : current_node->get_edges())
			{
				node<T>* other_node = nullptr;
				if (a_edges->m_nodes[0] == current_node)
				{
					other_node = a_edges->m_nodes[1];
				}
				else
				{
					other_node = a_edges->m_nodes[0];
				}

				// 
				if (std::find(std::begin(closed_list), std::end(closed_list), other_node) == closed_list.end())
				{
					int current_g_score = current_node->m_g_score + 1;

						if (std::find(std::begin(open_list), std::end(open_list), other_node) == open_list.end())
						{
							// let c.target.gscore = gScore
							other_node->m_g_score = current_g_score;
							other_node->m_previous = current_node;
							open_list.push_back(other_node);
						}
						else if (current_g_score < other_node->m_g_score)
						{
							other_node->m_g_score = current_g_score;
							other_node->m_previous = current_node;
						}
				}
			}
		}
		node<T>* end_node = a_other_node;
		m_path.push_back(end_node);
		while (end_node != a_start_node)
		{
			end_node = end_node->m_previous;
			m_path.push_back(end_node);
		}
		return m_path;
	}
};

