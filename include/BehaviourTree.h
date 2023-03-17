// Sourced from: https://cplusplus.com/forum/general/141582/
// Original code credited to prestokeys (https://cplusplus.com/user/prestokeys/)
// 
// Modified so it takes a time for each frame and runs a specific function defined by an Action
// Also made it so the whole tree is not evaluated every frame and only the current active node runs

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
	static enum class NodeStatus { FAILED, SUCCESS, RUNNING };

	class Node {  // This class represents each node in the behaviour tree.
	protected:
		BehaviourTree* tree;
	public:
		virtual NodeStatus run(float aTime) = 0;
		virtual void setTree(BehaviourTree* bt) { tree = bt; }
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
		void setTree(BehaviourTree* bt) override { tree = bt; for (Node* child : children) child->setTree(tree); }
	protected:
		std::vector<Node*> childrenShuffled() const { std::vector<Node*> temp = children;  std::shuffle(temp.begin(), temp.end(), std::default_random_engine(0));  return temp; }
	};

	class Selector : public CompositeNode {
	public:
		virtual NodeStatus run(float aTime) override {
			int index = 0;
			for (; index < getChildren().size(); index++)
			{
				NodeStatus status = getChildren()[index]->run(aTime); // If failed then keep running
				if (status == NodeStatus::SUCCESS) { tree->currentNodeStack.push_back(getChildren()[index]); return NodeStatus::SUCCESS; }  // If success then return status
				else if (status == NodeStatus::RUNNING) break; // If running then we will add all the remaining children to the stack
			}
			for (int i = getChildren().size() - 1; i >= index; i--) // Add in reverse order so that the last element is at bottom of stack and gets executed lsat from amongst the children
				tree->currentNodeStack.push_back(getChildren()[i]);
			/*for (Node* child : getChildren()) {  // The generic Selector implementation
				if (child->run(aTime) == NodeStatus::SUCCESS)  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
					return NodeStatus::SUCCESS;
			}*/
			return NodeStatus::FAILED;  // All children failed so the entire run() operation fails.
		}
	};

	class RandomSelector : public CompositeNode {  // RandomSelector operates as a Selector, but in a random order instead of from first child to last child.
	public:
		virtual NodeStatus run(float aTime) override {
			for (Node* child : childrenShuffled()) {  // The order is shuffled
				if (child->run(aTime) == NodeStatus::SUCCESS)
					return NodeStatus::SUCCESS;
			}
			return NodeStatus::FAILED;
		}
	};

	class Sequence : public CompositeNode {
	public:
		virtual NodeStatus run(float aTime) override {
			int index = 0;
			for (; index < getChildren().size(); index++) 
			{
				NodeStatus status = getChildren()[index]->run(aTime); // If success then keep checking the next child
				if (status == NodeStatus::FAILED) return NodeStatus::FAILED; // If failed then return status
				else if (status == NodeStatus::RUNNING) break; // If running then we will add all the remaining children to the stack
			}
			for (int i = getChildren().size() - 1; i >= index; i--) // Add in reverse order so that the last element is at bottom of stack and gets executed lsat from amongst the children
				tree->currentNodeStack.push_back(getChildren()[i]);
			tree->currentNodeStack.push_back(getChildren()[0]); // Since we returned a success status, the top most item in the stack gets popped, so we add a dummy node that will get popped instead
			return NodeStatus::SUCCESS;  // All children added to stack successfully
		}
	};

	class DecoratorNode : public Node {  // Function is either to transform the result it receives from its child node's status, to terminate the child, or repeat processing of the child, depending on the type of decorator node.
	private:
		Node* child;  // Only one child allowed
	protected:
		Node* getChild() const { return child; }
	public:
		void setChild(Node* newChild) { child = newChild; }
		void setTree(BehaviourTree* bt) override { tree = bt; child->setTree(bt); }
	};

	class Root : public DecoratorNode {
	private:
		friend class BehaviourTree;
		virtual NodeStatus run(float aTime) override { tree->currentNodeStack.push_back(getChild()); return getChild()->run(aTime); } // Child added to stack in case it is running, it is removed from stack if success
	};

	class Inverter : public DecoratorNode {  // Inverts the result of the child. A child fails and it will return success to its parent, or a child succeeds and it will return failure to the parent.
	private:
		virtual NodeStatus run(float aTime) override { NodeStatus status = getChild()->run(aTime); if (status == NodeStatus::FAILED) return NodeStatus::SUCCESS; else if (status == NodeStatus::SUCCESS) return NodeStatus::FAILED; return NodeStatus::RUNNING; }
	};

	class Repeater : public DecoratorNode {  // A repeater will reprocess its child node each time its child returns a result. These are often used at the very base of the tree, to make the tree to run continuously. Repeaters may optionally run their children a set number of times before returning to their parent.
	private:
		int numRepeats;
		static const int NOT_FOUND = -1;
		Repeater(int num = NOT_FOUND) : numRepeats(num) {}  // By default, never terminate.
		virtual NodeStatus run(float aTime) override {
			if (numRepeats == NOT_FOUND)
				while (true) getChild()->run(aTime);
			else {
				for (int i = 0; i < numRepeats - 1; i++)
					getChild()->run(aTime);
				return getChild()->run(aTime);
			}
		}
	};

	class ConditionalNode : public DecoratorNode {
	private:
		void* myContext;
		bool(*function)(float aTime, void* aContext);
		virtual NodeStatus run(float aTime) override {
			if (function(aTime, myContext)) { tree->currentNodeStack.push_back(getChild()); return getChild()->run(aTime); }
			else return NodeStatus::FAILED;
		}
	public:
		void setConditionalFunction(bool(*aFunction)(float time, void* context), void* aContext) { function = aFunction; myContext = aContext; }  // By default, condition is false so terminate.	
	};

private:
	Root* root;
	std::vector<Node*> currentNodeStack;

public:
	std::string name = "BT";
	BehaviourTree() : root(new Root) { currentNodeStack.push_back(root); }
	void setRootChild(Node* rootChild) const { root->setChild(rootChild); root->setTree(const_cast<BehaviourTree*>(this)); }
	bool run(float aTime)
	{
		NodeStatus status;
		do {
			status = currentNodeStack[currentNodeStack.size() - 1]->run(aTime);
			if (status == NodeStatus::FAILED)
			{
				currentNodeStack.clear();
				currentNodeStack.push_back(root);
			}
			else if (status == NodeStatus::SUCCESS)
			{
				if (currentNodeStack.size() > 1)
					currentNodeStack.pop_back();
			}
			else { break; }
		}
		while (status == NodeStatus::SUCCESS);
		return true;
	}
	void addToStack(Node* node) { currentNodeStack.push_back(node); }
};

class Action : public BehaviourTree::Node {
private:
	void* myContext;
	BehaviourTree::NodeStatus(*function)(float aTime, void* aContext);
public:
	Action(BehaviourTree::NodeStatus(*aFunction)(float time, void* context), void* aContext) : function(aFunction), myContext(aContext) {}
	void setTree(BehaviourTree* bt) { tree = bt; }
private:
	virtual BehaviourTree::NodeStatus run(float aTime) override {
		return function(aTime, myContext);
	}
};

#endif // BEHAVIOURTREE_H