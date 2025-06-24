#pragma once
#include <vector>
#include <functional>

template<typename... Args>
class MultiDelegate {
	struct Slot
	{
		void* instance;		// 콜백 구분용 포인터(주로 this)
		std::function<void(Args...)> func;	// 
	};
	std::vector<Slot> slots;

public:
	// Add Function
	void AddListener(void* instance, const std::function<void(Args...)>& f)
	{
		slots.push_back({ instance, f });
	}

	// Remove Function (등록한 instacne 활용)
	void Remove(void* instance)
	{
		slots.erase(std::remove_if(slots.begin(), slots.end(),
			[instance](const Slot& s) { return s.instance == instance; }),
			slots.end());
	}

	// Claer Functions
	void Clear() { slots.clear(); }

	// 등록된 Functions Call
	void Invoke(Args... args) const
	{
		for (const auto& s : slots)
			if (s.func) s.func(args...);
	}
};
