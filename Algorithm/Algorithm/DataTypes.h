#pragma once
namespace veda
{
	template<class DT>
	class Node 
	{
	public:
		DT data;
		Node* next;
	};

	template<class DT>
	class BidirectionNode 
	{
	public:
		DT data;
		BidirectionNode* next;
		BidirectionNode* pre;
	};
}
