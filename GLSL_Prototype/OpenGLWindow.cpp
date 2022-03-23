#include "OpenGLWindow.h"

// Settings
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 100.0f;

// Lighting
glm::vec3 lightPos(0.0f, 100.0f, 0.0f);

const glm::vec3 sceneScale(1.0f, 1.25f, 1.0f);

Model plantModel;
Model floorModel;

// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

OpenGLWindow::OpenGLWindow()
{
}

bool OpenGLWindow::createOpenGLWindow(const std::string& windowTitle, bool showFullscreen)
{
	glfwInit();

	const auto primaryMonitor = glfwGetPrimaryMonitor();
	const auto videoMode = glfwGetVideoMode(primaryMonitor);

	_window = glfwCreateWindow(videoMode->width, videoMode->height, windowTitle.c_str(), showFullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (_window == nullptr)
	{
		return false;
	}

	glfwGetWindowSize(_window, &_screenWidth, &_screenHeight);

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(_window, cursor_position_callback);

	// Tell GLFW to capture the mouse
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(_window);
	glewInit();

	_sceneCamera = Camera(glm::vec3(0.0f, 5.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_shaderProgram = Shader("shaders/basic.vert", "shaders/basic.frag");
	plantModel.loadFromFile("media/HousePlantScene.obj", "media/HousePlantScene.mtl");
	floorModel.loadFromFile("media/Floor.obj", "media/Floor.mtl", true);

	if (!showFullscreen)
	{
		glfwMaximizeWindow(_window);
		glfwGetWindowSize(_window, &_screenWidth, &_screenHeight);
	}

	return true;
}

void OpenGLWindow::runApp()
{
	glfwGetWindowSize(_window, &_screenWidth, &_screenHeight);

	lastX = _screenWidth / 2;
	lastY = _screenHeight / 2;

	// Render loop
	while (!glfwWindowShouldClose(_window))
	{
		// Input
		processInput(_window);

		// Render heightmap
		renderScene();
	}
}

void OpenGLWindow::renderScene() {

	// Rendering commands here
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glClearDepth(1.0f);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Get delta time
	float _currentFrame = static_cast<float>(glfwGetTime());
	_deltaTime = _currentFrame - _lastFrame;
	_lastFrame = _currentFrame;

	// Get window info
	glfwGetWindowSize(_window, &_screenWidth, &_screenHeight);

	// Update camera based on input
	_sceneCamera.setYaw(yaw);
	_sceneCamera.setPitch(pitch);
	_sceneCamera.setFOV(fov);

	_sceneCamera.processInput(_window, _deltaTime);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, sceneScale);

	plantModel.draw();
	floorModel.draw();

	// Process shader
	_shaderProgram.updateModelViewProjection(model, _sceneCamera.getViewMatrix(), _sceneCamera.getProjectionMatrix());
	_shaderProgram.use();

	_shaderProgram.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	_shaderProgram.setFloat("lightIntensity", 0.25f);
	_shaderProgram.setVec3("lightPos", lightPos);
	_shaderProgram.setVec3("viewPos", _sceneCamera.getPosition());

	// Check and call events and swap the buffers
	glfwPollEvents();
	glfwSwapBuffers(_window);
}

void OpenGLWindow::closeApp() {
	_shaderProgram.deleteShader();

	glfwDestroyWindow(_window);

	glfwTerminate();
}

// Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// Close application
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// Zoom in
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
		fov = 60.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		fov = 10.0f;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
}
