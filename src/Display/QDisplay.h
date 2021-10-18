#pragma once

#include "../QLogger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

/*
 * Singleton display class, mainly used for initialisation
 */
class QDisplay {
public:
	static QDisplay &GetInstance() {
		static QDisplay display;
		return display;
	}

	GLFWwindow* getWindow() {
		return window;
	}

private:
	GLFWwindow *window;
	std::string glsl_version;

	std::string programName = "QBackTest";
	float highDPIscaleFactor = 1.0;
	int windowWidth = 1200;
	int windowHeight = 800;

	float backgroundR = 0.45f;
	float backgroundG = 0.44f;
	float backgroundB = 0.48f;

	static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	/*
	 * Cleans up all GL variables for clean exit
	 */
	void CleanupDisplay() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		if (window != nullptr) {
			glfwDestroyWindow(window);
		}
		glfwTerminate();
	}

	QDisplay() {
		if (!glfwInit()) {
			QLogger::GetInstance().Error("Couldn't initialize GLFW");
		} else {
			QLogger::GetInstance().Info("GLFW initialized");
		}

		// setup GLFW window
		glfwWindowHint(GLFW_DOUBLEBUFFER , 1);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_STENCIL_BITS, 8);

		glfwWindowHint(
				GLFW_OPENGL_PROFILE,
				GLFW_OPENGL_CORE_PROFILE
		);

		#ifdef __APPLE__
				// GL 3.2 + GLSL 150
						glsl_version = "#version 150";
						glfwWindowHint( // required on Mac OS
							GLFW_OPENGL_FORWARD_COMPAT,
							GL_TRUE
							);
						glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
						glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		#elif __linux__
				// GL 3.2 + GLSL 150
				glsl_version = "#version 150";
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		#elif _WIN32
				// GL 3.0 + GLSL 130
						glsl_version = "#version 130";
						glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
						glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		#endif

		#ifdef _WIN32
				// if it's a HighDPI monitor, try to scale everything
						GLFWmonitor *monitor = glfwGetPrimaryMonitor();
						float xscale, yscale;
						glfwGetMonitorContentScale(monitor, &xscale, &yscale);
						if (xscale > 1 || yscale > 1)
						{
							highDPIscaleFactor = xscale;
							glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
						}
		#elif __APPLE__
				// to prevent 1200x800 from becoming 2400x1600
						glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
		#endif

		window = glfwCreateWindow(
				windowWidth,
				windowHeight,
				programName.c_str(),
				nullptr,
				nullptr
		);

		if (!window) {
			QLogger::GetInstance().Error("Couldn't create a GLFW window");
			CleanupDisplay();
		}

		// watch window resizing
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwMakeContextCurrent(window);

		// VSync
		glfwSwapInterval(1);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version.c_str());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			QLogger::GetInstance().Error("Couldn't initialize GLAD");
			CleanupDisplay();
		} else {
			QLogger::GetInstance().Info("GLAD initialized");
		}

		int actualWindowWidth, actualWindowHeight;
		glfwGetWindowSize(window, &actualWindowWidth, &actualWindowHeight);
		glViewport(0, 0, actualWindowWidth, actualWindowHeight);
		glClearColor(backgroundR, backgroundG, backgroundB, 1.0f);
	}

	~QDisplay() {
		CleanupDisplay();
	}
};