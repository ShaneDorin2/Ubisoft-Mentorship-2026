#pragma once
#include <memory>
#include <vector>
#include <string>
class SceneMember;

class Scene
{
public: // constructors

	Scene(); 
	Scene(std::string file_path);  
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

private: // logic

	void detectTypeAndAdd(char character, int row, int col);

private: // data

	std::vector<std::unique_ptr<SceneMember>> member_library;
};

/*

wwwwwwwwww
w........w
w........w
w........w
w........w
w........w
wwwwwwwwww

*/

