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
	void addMember(std::unique_ptr <SceneMember> new_member, float pos_x, float pos_y);

public: // data

	std::vector< std::unique_ptr<SceneMember>> member_library;
};

