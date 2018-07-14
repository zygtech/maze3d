cmake_minimum_required (VERSION 2.8)
project(OgreTutorialsSample)

## [discover_ogre]
# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)
## [discover_ogre]

set(HDRS
        ./DotSceneLoader.h
        ./rapidxml.h
        ./CollisionTools.h
)

set(SRCS
        ./DotSceneLoader.cpp
        ./CollisionTools.cpp
        ./Bootstrap.cpp
)

add_executable(Maze Bootstrap.cpp ${HDRS} ${SRCS})
target_link_libraries(Maze ${OGRE_LIBRARIES})
