# Ubisoft-Mentorship-2026

Project submission for the 2026 Develop At Ubisoft mentorship program.

Mentee: Shane Dorin
Mentor: Vincent Leclercq

Git repository link: https://github.com/ShaneDorin2/Ubisoft-Mentorship-2026
Video demonstration: https://youtu.be/2weslaBR6dE 

Project summary: Create a custom game engine using c++ and a template provided by Vincent Leclercq.

Gameplay description:
Top-down 2D game.
The player character is a demon with enochlophobia (fear of crowded spaces). This character must make her way through a crowded courtyard.

Player movement controls:
w - up
a - left
s - down
d - right

NPC movement is handled by the Boid algorithm.

Know bugs:
Re-sizing or re-positioning the window will cause npcs to travel through / get stuck in wall colliders.


Main script: GameTest.cpp

Scripts I created:

Engine Code:
- CircleCollider2D
- Collider2D
- ColliderLibrary
- CollisionDetection
- EventManager
- EventNames
- InputManager
- Movable
- Positionable
- RayCastCollider2D
- RectangleCollider2D
- Scene
- SceneMember

Game Code:
- AngelDetectionZone
- Boid
- BoidFlock
- Player
- WallTile