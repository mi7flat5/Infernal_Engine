# Infernal Engine
This project is a learning tool for learning implementation of game engine architecture, 
and the use and implementation of Object Oriented design patterns.  The underlying design 
is based on the design of the game engine designed in Game Coding Complete by Mike McShaffry.
This implementation, however; uses modern openGL therefore a lot of the code abstracted in 
the GCC4 engine that uses DirectX will be or has been implemented by me.  An example of this 
would be frustum culling. The DirectX used in GCC4 provides math functionality for plane sphere 
Intersection testing, but had to be implemented here. The engine will eventually be a library which does not provide an openGL context on its own
The application that uses it will provide its own context. This solution has a prototyper project that uses the GLFW library for creating a context. I've also begun work on an editor GUI using Qt which provides it's own context.
The library shares most of the source with the prototyper and is built for and utilized by the editor.
## Implemented
An incomplete list of features currently implemented at least in a simple form:
* 3D Model Loading utility
    * Vertex, normal, tangent, bit tangent
    * Texture 2D and Cube Map\Environment map
* Scenegraph
* Extensible scenenode class
* Shader loading utilities, can load multiple configurations of pipeline. Vert->TES->TCS->Frag
* Multiple shaders (found in shaders folder)
* Event system, using fast delegates, not yet concurrent. 
* Object creation (factory) and rendering component classes. 

## ToDo
An incomplete list of features that are planned for implementation soon:

* Add geometry shader functionality to shader loading class
* Load utility currently loads hierarchical models into one mesh, separate into parent/children
* Add bounding sphere hierarchy to scenegraph parent/child objects, for frustum culling
* Add matrix stack handling in scenegraph
* Add process manager class to handle multiple frame operations.

# Running Project
*  This project is for Visual Studio 2015
*  You will need Qt 5.7 installed(for the editor, protyper and library build will work without), I also recommend using the Qt add in for Visual Studio 2015
*  Project will only build under x86 Debug and Release configurations.
*  Unzip DLL_FOR_EXECUTABLE_FOLDER.rar into the Debug and Release folders that are in this directory. You may have to attempt to build under each configuration or the folders wont be there. 
*  Open the solution in Visual Studio and run either configuration for any of the projects.


