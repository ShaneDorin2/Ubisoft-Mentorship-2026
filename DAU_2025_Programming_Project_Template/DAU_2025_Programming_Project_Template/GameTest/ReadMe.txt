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





Template project README:

========================================================================
    CONSOLE APPLICATION : GameTest Project Overview
========================================================================

AppWizard has created this GameTest application for you.

This file contains a summary of what you will find in each of the files that
make up your GameTest application.


GameTest.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

GameTest.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

GameTest.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named GameTest.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
