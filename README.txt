===========================================================================================================
===GITHUB URL:https://github.com/JanssensRobbe/JanssensRobbe_2DAE07_Engine_Programming4/tree/Development===
===========================================================================================================


+=========+
|controls:|
|=========+===============================+
|== WASD for moving first character	==|
|== IJKL for moving second character	==|
|== k to press button in menu		==|
|== press WS to go up and down in menu	==|
+=========================================+

================
About my engine:
================
I have made the game loop just like we are used to with DeltaTime given in every Update.

=================
Component System:
=================
The engine is made by different components as that was the Requirement of the assignment.
It is not the only reason i choose for the component system because i think it has a lot of great futures.
I am used to unity and working with components is the biggest future in unity.

==============
State Machine:
==============
The state Machine is based on the Finit state machine from gameplay programming and has a few files.
The conditions, the actions, the transitions, the states and of course the statemachine.
The conditions are just conditions for an actions, conditions are combined with actions in the transitions 
to get the enemies in the right states.
You have a few different actions, entery actions for when you enter a state, normal actions for when you are in a state
and ExitActions.

=============
InputManager:
=============
InputManager works with InputActions these are Actions together with commands.
This makes when you press a button a certian command will be executed.
These commands will trigger.

===============
AgentComponent:
===============
AgentComponent is just the component that uses the Statemachine to controle the enemies.

===================
CharacterComponent:
===================
CharacterComponent is the component that uses the inputManager and the commands too make the player work.

============
LevelEditor:
============
I just made a little LevelEditor that was based on a few tricks.
This levelEditor cant really be used by other people but you can just make add tunnels in a bin file.
This file can be loaded into the engine and so you can create digdug exclusive maps as the layer itself is already in the engine.
So when there is an empty file read into the engine there will be a normal level without tunnels.

=====================
Scene + SceneManager:
=====================
You have a SceneManager where you can Load in every scene.
You can just make new scene and override the LoadScene.
Here you can Make all the inputActions and add all components to the scene.

===================
CollisionComponent:
===================
Here you can add your CollisionRectangles and give it a tag.
If you call the checkCollision with a certain CollisionRectangles and a tag you will check the rectangle 
with every collisionBox with the tag.

===============
LevelComponent:
===============
Here the level is created and the stones are added.

===============
StoneComponent:
===============
The component with the stone logic.

=======
Score:
=======
This is only displayed in the output.
using std::cout and 

===============
ServiceLocator:
===============
Here you can register tiles, agents and players.
So the other components can just ask for there information.

========
Structs:
========
Here are self created structs and enums.




