/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Tomislav Nikolov
* @idnumber 45211
* @task 4
* @compiler VC
*
*/
#ifndef __BINTREEBAL_HEADER_INCLUDED_
#define __BINTREEBAL_HEADER_INCLUDED_

#include <iostream>

template<class T>
class BinTree{
private:
	struct Node{
		T key;
		Node* Lefty;
		Node* Righty;
		Node(T k, Node* L = nullptr, Node* R = nullptr) :
			key(k),
			Lefty(L),
			Righty(R)
		{}
	};
	Node* Root;
	int lefts;
	int rights;
	bool Located;
public:
	BinTree() : Root(nullptr), lefts(0), rights(0), Located(false) {}
	~BinTree() { Delete(Root); }
	bool IsEmpty()const{ return (Root == nullptr); }
	void AddEntry(T&);
	bool RemoveEntry(T&);
	bool SearchEntry(T&);
	void Balance();
private:
	void Add(Node*&, T&);
	bool Remove(Node*&, T&);
	bool Search(Node*&, T&);
	void DeTree(Node*&);
	void CreateLeaf(Node*&, T&);
	void Delete(Node*&);
};

template<class T>
void BinTree<T>::AddEntry(T& el)
{
	Add(Root, el);
}

template<class T>
void BinTree<T>::Add(Node*& Last, T& el)
{
	if (IsEmpty())
	{
		CreateLeaf(Root, el);
		return;
	}
	if (el >= Last->key)
	{
		if (Last->Righty == nullptr)
		{
			CreateLeaf(Last->Righty, el);
			rights++;
			return;
		}
		else
		{
			Add(Last->Righty, el);
		}
	}
	else
	{
		if (Last->Lefty == nullptr)
		{
			CreateLeaf(Last->Lefty, el);
			lefts++;
			return;
		}
		else
		{
			Add(Last->Lefty, el);
		}
	}
}

template<class T>
bool BinTree<T>::RemoveEntry(T& el)
{
	return Remove(Root, el);
}

template<class T>
bool BinTree<T>::Remove(Node*& Last, T& el)
{
	if (Last == nullptr)
	{
		return false;
	}
	if (el == Last->key||Located)
	{
		Located = true;
		if (Last->Righty != nullptr&&Last->Lefty != nullptr)
		{
			Node* temp = Last->Lefty;
			while (temp->Righty != nullptr)
			{
				temp = temp->Righty;
			}
			Last->key = temp->key;
			return Remove(Last->Lefty, el);
		}
		else
		{
			Node* killer;
			if (Last->Lefty != nullptr)
			{
				Last->key = Last->Lefty->key;
				killer = Last;
				Last = Last->Lefty;
				DeTree(killer);
			}
			else if (Last->Righty != nullptr)
			{
				Last->key = Last->Righty->key;
				killer = Last;
				Last = Last->Righty;
				DeTree(killer);
			}
			else
			{
				DeTree(Last);
			}
			Located = false;						
			return true;							
		}				
	}
	if (el >= Last->key)
	{
		return Remove(Last->Righty, el);
	}
	if (el < Last->key)
	{
		return Remove(Last->Lefty, el);
	}
}

template<class T>
bool BinTree<T>::SearchEntry(T& el)
{
	return Search(Root, el);
}

template<class T>
bool BinTree<T>::Search(Node*& Last, T& el)
{
	if (Last == nullptr)
	{
		return false;
	}
	if (el == Last->key)
	{
		return true;
	}
	if (el >= Last->key)
	{
		return Search(Last->Righty, el);
	}
	if (el < Last->key)
	{
		return Search(Last->Lefty, el);
	}
}

template<class T>
void BinTree<T>::Balance()
{
	Node* help;
	Node* Last = Root;
	if (lefts != rights && (lefts + 1 != rights || lefts != rights + 1))
	{
		if (rights > lefts)
		{
			while (true)
			{
				help = Last->Righty;
				if (help->Righty == nullptr&&help->Lefty == nullptr)
				{
					Last = Root;
					break;
				}
				Last->Righty = help->Righty;
				Last = Last->Righty;
				help->Righty = nullptr;
				if (help->Lefty != nullptr&&Last->Lefty != nullptr)
				{
					help->Righty = Last->Lefty;
					Last->Lefty = help;
				}
				else if (Last->Lefty != nullptr)
				{
					if (Last->Lefty->Righty != nullptr)
					{
						Last->Lefty->Lefty = help;
					}
					else
					{
						help->Righty = Last->Lefty;
						Last->Lefty = help;
					}
				}
				else
				{
					Last->Lefty = help;
				}
			}
		}
		else
		{
			while (true)
			{
				help = Last->Lefty;
				if (help->Righty == nullptr&&help->Lefty == nullptr)
				{
					Last = Root;
					break;
				}
				Last->Lefty = help->Lefty;
				Last = Last->Lefty;
				help->Lefty = nullptr;
				if (help->Righty != nullptr&&Last->Righty != nullptr)
				{
					help->Lefty = Last->Righty;
					Last->Righty = help;
				}
				else if (Last->Righty != nullptr)
				{
					if (Last->Righty->Lefty != nullptr)
					{
						Last->Righty->Righty = help;
					}
					else
					{
						help->Lefty = Last->Righty;
						Last->Righty = help;
					}
				}
				else
				{
					Last->Righty = help;
				}
			}
		}
	}
}

template<class T>
void BinTree<T>::DeTree(Node*& Chosen)
{
	Node* killer = Chosen;
	delete killer;
	Chosen = nullptr;
}

template<class T>
void BinTree<T>::CreateLeaf(Node*& Chosen, T& el)
{
	Node* temp = new Node(el);
	Chosen = temp;
}

template<class T>
void BinTree<T>::Delete(Node*& Last)
{
	if (IsEmpty()) return;
	if (Last->Righty == nullptr&&Last->Lefty == nullptr)
	{
		DeTree(Last);
		Delete(Root);
	}
	else if (Last->Righty != nullptr)
	{
		Delete(Last->Righty);
	}
	else if (Last->Lefty != nullptr)
	{
		Delete(Last->Lefty);
	}
}

#endif