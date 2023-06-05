# maze3d
Maze in Ogre3D (collision detect + dotScene import)

Startup game engine based on Ogre3D for game creation with collision detection and scene import from Blender exporter.

1. Install libogre and libois: sudo apt-get install libogre-1.12-dev libois-dev
2. Open file CMakeLists.txt in QtCreator.
3. In files CollisionTools.cpp and DotSceneImporter.cpp are ready scripts for collision detection and loading Blender exported scene.
4. After compiling and building copy folder Level and file resources.cfg to build location (usually release or debug).
5. Try out demo level and start editing Bootstrap.cpp to create your game. 
6. Optionally: use Blender to Ogre exporter with your own Level map.
