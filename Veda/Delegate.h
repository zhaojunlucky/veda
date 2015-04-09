#pragma once
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
template <typename... Params>
class Delegate {
private:
	typedef std::function<void(Params...)> Handler;
	
	vector<Handler> m_handlers;
public:
	typedef typename vector<Handler>::const_iterator cookie;

	cookie connect(Handler&& func) {
		m_handlers.push_back(std::move(func));
		return m_handlers.cbegin();// +(m_handlers.size() - 1);
	}

	template <typename... BindArgs, typename Sfinae = typename std::enable_if<(sizeof...(BindArgs)>1), void>::type>
	cookie connect(BindArgs&&... args) {
		return connect(Handler(std::bind(std::forward<BindArgs>(args)...)));
	}

	void disconnect(cookie which) {
		m_handlers.erase(which);
	}

	template <typename ... Args> void operator()(Args...args) {
		for (auto const& handler : m_handlers)
			handler(args...);
	}
};