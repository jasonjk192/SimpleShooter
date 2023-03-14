// Sourced from: https://cplusplus.com/forum/general/141582/
// Modified so it takes a time for each frame and runs a specific function defined by an Action

#ifndef BEHAVIOURTREE_H
#define BEHAVIOURTREE_H

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

class BehaviourTree
{
public:
	class Node {  // This class represents each node in the behaviour tree.
	public:
		virtual bool run(float aTime) = 0;
	};

	
	class CompositeNode : public Node {  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
	private:
		std::vector<Node*> children;
	public:
		const std::vector<Node*>& getChildren() const { return children; }
		void addChild(Node* child) { children.emplace_back(child); }
		void addChildren(std::initializer_list<Node*>&& newChildren) { for (Node* child : newChildren) addChild(child); }
		template <typename CONTAINER>
		void addChildren(const CONTAINER& newChildren) { for (Node* child : newChildren) addChild(child); }
	protected:
		std::vector<Node*> childrenShuffled() const { std::vector<Node*> temp = children;  std::shuffle(temp.begin(), temp.end(), std::default_random_engine(0));  return temp; }
	};

	class Selector : public CompositeNode {
	public:
		virtual bool run(float aTime) override {
			for (Node* child : getChildren()) {  // The generic Selector implementation
				if (child->run(aTime))  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
					return true;
			}
			return false;  // All children failed so the entire run() operation fails.
		}
	};

	class RandomSelector : public CompositeNode {  // RandomSelector operates as a Selector, but in a random order instead of from first child to last child.
	public:
		virtual bool run(float aTime) override {
			for (Node* child : childrenShuffled()) {  // The order is shuffled
				if (child->run(aTime))
					return true;
			}
			return false;
		}
	};

	class Sequence : public CompositeNode {
	public:
		virtual bool run(float aTime) override {
			for (Node* child : getChildren()) {  // The generic Sequence implementation.
				if (!child->run(aTime))  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
					return false;
			}
			return true;  // All children suceeded, so the entire run() operation succeeds.
		}
	};

	class DecoratorNode : public Node {  // Function is either to transform the result it receives from its child node's status, to terminate the child, or repeat processing of the child, depending on the type of decorator node.
	private:
		Node* child;  // Only one child allowed
	protected:
		Node* getChild() const { return child; }
	public:
		void setChild(Node* newChild) { child = newChild; }
	};

	class Root : public DecoratorNode {
	private:
		friend class BehaviourTree;
		virtual bool run(float aTime) override { return getChild()->run(aTime); }
	};

	class Inverter : public DecoratorNode {  // Inverts the result of the child. A child fails and it will return success to its parent, or a child succeeds and it will return failure to the parent.
	private:
		virtual bool run(float aTime) override { return !getChild()->run(aTime); }
	};

	class Repeater : public DecoratorNode {  // A repeater will reprocess its child node each time its child returns a result. These are often used at the very base of the tree, to make the tree to run continuously. Repeaters may optionally run their children a set number of times before returning to their parent.
	private:
		int numRepeats;
		static const int NOT_FOUND = -1;
		Repeater(int num = NOT_FOUND) : numRepeats(num) {}  // By default, never terminate.
		virtual bool run(float aTime) override {
			if (numRepeats == NOT_FOUND)
				while (true) getChild()->run(aTime);
			else {
				for (int i = 0; i < numRepeats - 1; i++)
					getChild()->run(aTime);
				return getChild()->run(aTime);
			}
		}
	};

private:
	Root* root;

public:
	BehaviourTree() : root(new Root) {}
	void setRootChild(Node* rootChild) const { root->setChild(rootChild); }
	bool run(float aTime) const { return root->run(aTime); }
};

class Action : public BehaviourTree::Node {
private:
	void* myContext;
	void (*function)(float aTime, void* aContext);
public:
	Action(void(*aFunction)(float time, void* context), void* aContext) : function(aFunction), myContext(aContext) {}
private:
	virtual bool run(float aTime) override {
		function(aTime, myContext);
		return true;
	}
};

#endif // BEHAVIOURTREE_H