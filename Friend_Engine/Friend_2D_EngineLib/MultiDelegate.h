#pragma once
#include <vector>
#include <functional>
#include "Object.h"
#include "ObjectTable.h"

template<typename... Args>
class MultiDelegate {
	struct Slot
	{
		Object* instance;				    // �ݹ� ���п� ������	(GameObject, Component, Scene)
		std::function<void(Args...)> func;	// �ݹ� �Լ� ����Ʈ
	};
	std::vector<Slot> slots;

public:
	// Add Function
	void AddListener(Object* instance, const std::function<void(Args...)>& f)
	{
		slots.push_back({ instance, f });
	}

	// Remove Function (����� instacne Ȱ��)
	void Remove(Object* instance)
	{
		slots.erase(std::remove_if(slots.begin(), slots.end(),
			[instance](const Slot& s) { return s.instance == instance; }),
			slots.end());
	}

	// Claer Functions
	void Clear() { slots.clear(); }

	// ��ϵ� Functions Call
	void Invoke(Args... args) const
	{
		for (const auto& s : slots)
		{
			// Handle�� ���̺��� ��ȿ���� �˻�
			if (ObjectTable::Get().IsValid(s.instance))
				s.func(args...);
		}
	}
};
