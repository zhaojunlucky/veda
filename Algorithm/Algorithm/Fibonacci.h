#pragma once
#include <hash_map>
namespace al
{
	/*
	 * a class to calculate Fibonacci number,
	 * use dynamic prog
	 */
	class Fibonacci
	{
	public:
		Fibonacci();
		~Fibonacci();

		/*
		 * calculate Fibonacci number by a given number.
		 * F£¨0£©=0£¬F£¨1£©=1£¬F£¨n£©=F(n-1)+F(n-2)£¨n¡Ý2£¬n¡ÊN*£©
		 */
		int fibonacci(int num);
	private:
		int _fibonacci(int num);
	private:
		std::hash_map<int, int> mCache;
	};
}


