#pragma once
#include <memory>
#include <vector>
class SceneMember;

class Scene
{
public: // constructors

	Scene(); // TODO: add filepath and/or 2D string parameter. 
	~Scene();

	// "rule of threes"
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

public: // logic

	void updateLogic(float delta_time);
	void draw();
	void drawGizmos();

public: // template

	template<typename T, typename... Args>
	void addMember(Args&&... args)
	{
		//assert(std::is_base_of<SceneMember, T>::value)

		auto obj = std::make_unique<T>(std::forward<Args>(args)...); // what does "forwards" and "..." mean in this context ? 
		member_library.push_back(std::move(obj));
	}

private: // data

	std::vector<std::unique_ptr<SceneMember>> member_library;
};

