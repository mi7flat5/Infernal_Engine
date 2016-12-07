# Infernal Engine
    This project is a learning tool for learning implementation of game engine architecture, 
    and the use and implemntation of Object Oriented design patterns.  The underlying design 
    is based on the design of the game engine desigend in Game Coding Complete by Mike CShaffry.
    This implementation, however; uses modern openGL therefore a lot of the code abstracted in 
    the GCC4 engine that uses DirectX will be or has been implemented by me.  An example of this 
    would be frustum culling. The DirectX used in GCC4 provides math functionality for plane sphere 
    intersection testing, but had to be implemented here. This engine also uses GLFW to handle windows
    rather than dealing directly with the windows API, which should make migration of platform easier. 
## Implemented
An incomplete list of features currently implemented at least in a simple form:
* 3D Model Loading utility
    * vertex, normal, tangent, bit tangent
    * Texture 2D and CubeMap\Environment map
* Scenegraph
* Extensible scenenode class
* Shader loading utilities, can load multiple configurations of pipeline. Vert->TES->TCS->Frag
* Multiple shaders ( found in shaders folder)
* Event system, using fast delegates, not yet concurrent. 
* Object creation (factory) and rendering component classes. 

## ToDo
An incomplete list of features that are planned for implementation soon:

* Add geometry shader functionality to shader loading class
* Load utility currently loads heirarchical models into one mesh, seperate into parent/children
* Add bounding sphere heirarchy to scenegraph parent/child objects, for frustum culling
* Add matrix stack handleing in scenegraph
* Add process manager class to handle multiple frame operations.

# Running Project
*  This project is for Visual Studio 2015
*  You will need Qt 5.7 installed, I also recommend using the Qt add in for Visual Studio 2015
* Unzip DLL_FOR_EXECUTABLE_FOLDER.rar into the Debug and Release folders that are in this directory. 
*  Open the solution in Visual Studio and run either configuration for any of the projects.
 