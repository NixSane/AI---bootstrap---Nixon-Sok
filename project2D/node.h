#pragma once
#include <vector>

template <typename T>
class edge;

template <typename T>
class node
{
public:
	node<T>(const T& a_data)  : m_data(a_data) 
	{}

	~node() {}

	void add_edge(edge<T>* a_edge)
	{
		m_edges.push_back(a_edge);
	}
	
	void remove_edge(edge<T>* a_edge)
	{
		auto iter = std::find(m_edges.begin(), m_edges.end(), a_edge);
		m_edges.erase(iter);
	}

	std::vector<edge<T>*>& get_edges()
	{
		return m_edges;
	}

	std::vector<edge<T>*> m_edges;
	T m_data;

	node<T>* m_previous = nullptr; // Added this for pathing
	int m_g_score = 0;			   // Weighted pathing

	void reset()				   // For clearing graph faster
	{
		m_previous = nullptr;
		m_g_score = 0;
	}
};

