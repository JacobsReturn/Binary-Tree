/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while(m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{
	TreeNode* node = new TreeNode(a_nValue);

	if (IsEmpty())
	{
		m_pRoot = node;
		return;
	}

	TreeNode* current = m_pRoot;

	TreeNode* parent = m_pRoot;

	while (current != nullptr)
	{
		if (current->GetData() == a_nValue) return;
		else if (current->GetData() > a_nValue)
		{
			if (current->GetLeft() == nullptr) parent = current;
			current = current->GetLeft();
		}
		else if (current->GetData() < a_nValue)
		{
			if (current->GetRight() == nullptr) parent = current;
			current = current->GetRight();
		}
	}

	if (a_nValue < parent->GetData()) parent->SetLeft(node);
	else parent->SetRight(node);
}

void BinaryTree::Insert(TreeNode* node)
{
	if (IsEmpty())
	{
		m_pRoot = node;
		return;
	}

	TreeNode* current = m_pRoot;

	TreeNode* parent = m_pRoot;

	while (current != nullptr)
	{
		if (current->GetData() == node->GetData()) return;
		else if (current->GetData() > node->GetData())
		{
			if (current->GetLeft() == nullptr) parent = current;
			current = current->GetLeft();
		}
		else if (current->GetData() < node->GetData())
		{
			if (current->GetRight() == nullptr) parent = current;
			current = current->GetRight();
		}
	}

	if (node->GetData() < parent->GetData()) parent->SetLeft(node);
	else parent->SetRight(node);
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = m_pRoot;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	while (ppOutNode != nullptr)
	{
		if (ppOutNode->GetData() == a_nSearchValue) return true;
		else
		{
			if (a_nSearchValue < ppOutNode->GetData())
			{
				ppOutParent = ppOutNode;
				ppOutNode = ppOutNode->GetLeft();
			}
			else
			{
				ppOutParent = ppOutNode;
				ppOutNode = ppOutNode->GetRight();
			}
		}
	}

	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	if (IsEmpty()) return;

	TreeNode* current = m_pRoot;
	TreeNode* parent = nullptr;
	
	// Find the node then store it above.
	if (FindNode(a_nValue, current, parent))
	{
		TreeNode* left = new TreeNode(0);
		left = current->GetLeft();
		TreeNode* right = new TreeNode(0);
		right = current->GetRight();

		current->SetLeft(nullptr);
		current->SetRight(nullptr);

		if (current == m_pRoot)
		{
			m_pRoot = nullptr;
		}
		else if (current->GetData() < parent->GetData()) parent->SetLeft(nullptr);
		else if (current->GetData() > parent->GetData()) parent->SetRight(nullptr);

		if (left != nullptr)
		{
			Insert(left);
		}

		if (right != nullptr)
		{
			Insert(right);
		}

		delete current;
	}
}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
    PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			
			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}