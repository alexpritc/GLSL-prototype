# COMP3015 C1: Initial GLSL Prototype - 30%

<!-- CONTACT -->
## Contact

Alex Pritchard - [@alexpritc](https://twitter.com/alexpritc) - hi@apritc.com

Project Link: [https://github.com/alexpritc/GLSL-prototype](https://github.com/alexpritc/GLSL-prototype)

![image](https://user-images.githubusercontent.com/23083779/159910370-97e0787c-d3c2-4ca5-8899-25d7eb0cdd33.png)

## How does it work?
This project works by loading and rendering .obj files with their respective .mtl information for material and texture binding. It uses OpenGL 4.x and C++. 

## How does your code fit together and how should a programmer navigate it?
All of the GLFW Window management is handled in it's own class, [OpenGLWindow.cpp](https://github.com/alexpritc/GLSL-prototype/blob/main/GLSL_Prototype/OpenGLWindow.cpp). Each window instance has it's own instances of [Model.cpp](https://github.com/alexpritc/GLSL-prototype/blob/main/GLSL_Prototype/Model.cpp) that loads the vertices, normals, indicies, material and texture information from an .obj file (path is specified). It binds this information to the shader program which is an instance of [Shader.cpp](https://github.com/alexpritc/GLSL-prototype/blob/main/GLSL_Prototype/Shader.cpp) which reads from and writes to fragment and vertex shaders. [basic.vert](https://github.com/alexpritc/GLSL-prototype/blob/main/GLSL_Prototype/shaders/basic.vert) handles the Model View Projection matrix and the [basic.frag](https://github.com/alexpritc/GLSL-prototype/blob/main/GLSL_Prototype/shaders/basic.frag) handles the colour of vertices, texturing and phong lighting. The colouring of vertices specifically isn't handled in the vertex shader to avoid fragment interpolation. This achieves a cartoony asethetic.

With further development, it could be used by:
* Game artists to render and inspect models.
* Game developers for prototyping games.

![image](https://user-images.githubusercontent.com/23083779/159910202-d0475ae7-66cd-48be-b402-300c0afe20d2.png)

## Which version Visual Studio and Operating System you used to test/write the code locally?
* Visual Studio 2019
* Windows 10

<!-- INSTALLATION -->
## Installation

_Follow the instructions below to setup the app. This project doesn't rely on any external dependencies or services._

1. Clone the repo
   ```sh
   git clone https://github.com/alexpritc/GLSL-prototype
   ```
2. Extract the latest build at [GLSL-prototype.zip]()

3. Run `GLSL_Prototype.exe`
   ```sh
   https://github.com/alexpritc/GLSL-prototype/GLSL_Prototype.exe
   ```
	
<!-- REQUIREMENTS -->
#### Requirements
* Windows 10+
* x64 bit OS
* A keyboard
* A mouse

<!-- How to use -->
## Controls
Here is the list of the keys that can be used to interact with the program
<table>
<tr><th colspan="2">Camera</th></tr>
	<tr><td><b>W</b></td><td>Move forward</td></tr>
	<tr><td><b>S</b></td><td>Move backward</td></tr>
	<tr><td><b>A</b></td><td>Move left</td></tr>
	<tr><td><b>D</b></td><td>Move right</td></tr>
	<tr><td><b>Mouse</b></td><td>Look around</td></tr>
	<tr><td><b>R</b></td><td>Zoom</td></tr>
	<tr><td><b>Left Shift</b></td><td>Move Down</td></tr>
	<tr><td><b>Space</b></td><td>Move Up</td></tr>
<tr><th colspan="2">Other</th></tr>
	<tr><td><b>ESC</b></td><td>Close the program</td></tr>
</table>

## Video
_Click to play developer walkthrough:_

[]()

<!-- LIBRARIES -->
## List of libraries used
* GL - OpenGL
* GLFW - OpenGL framework used for cross-platform window creation and input handling
* GLM - Mathematics library (vectors, matrices, quaternions etc.)

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Resources I found helpful and would like to give credit to:

* [Learn OpenGL Tutorials](https://github.com/JoeyDeVries/LearnOpenGL)
* [OpenGL Tutorials](https://github.com/michalbb1/opengl4-tutorials-mbsoftworks)

<p align="right">(<a href="#top">back to top</a>)</p>
