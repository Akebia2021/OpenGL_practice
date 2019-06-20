//#include <glad/glad.h>
//#include <glfw3.h>
//#include <iostream>
//
//using namespace std;
//
////vertex shaderのソースコード。Char型で格納
//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//
//
//void processInput(GLFWwindow *window)
//{
//	//指定されたキーの状態をGLFW_PRESSもしくはGLFW_RELEASEとして返す
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//int main() {
//
//	//GLFW を初期化。必ず最初に行う。Return Typeは int
//	glfwInit();
//
//	//プログラム終了時に登録された関数を実行
//	atexit(glfwTerminate);
//
//	//Windowを作成する。glfwCreateWindow() のReturn typeは Rendering context objectのポインタ
//	GLFWwindow * const window(glfwCreateWindow(640, 480, "Hello", NULL, NULL));
//	if (window == NULL) {
//		cout << "can't create glfw window." << endl;
//		glfwTerminate();
//		return 1;
//
//	}
//
//	//作成したWindowsを OpenGL の描画対象にする
//	glfwMakeContextCurrent(window);
//
//	//creating Vertex Buffer Object
//	unsigned int VBO;
//
//	//creating Vertex Shader Object
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Argumentに指定するのはShader type
//
//	//creating Frag shader object
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//	//creating Shader Program Object. ShaderProgramは複数のShaderをリンクしたもの
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//
//	
//	//三角形の頂点データセット
//	float vertices[] = {
//	-0.5f, -0.5f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f
//	};
//
//
//	//Render LOOP
//	while (!glfwWindowShouldClose(window)) {
//
//		//input
//		processInput(window);
//
//		//rendering
//		glClear(GL_COLOR_BUFFER_BIT); //Color buffer をクリア
//		glClearColor(1.0f, 1.0f, 0.0f, 0.0f); //
//
//		glGenBuffers(1, &VBO); //generate buffer
//		glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind buffer
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //VSOとShader sourceをアタッチ
//		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//		glCompileShader(vertexShader); //Shaderをコンパイル
//		glCompileShader(fragmentShader);
//
//		glAttachShader(shaderProgram, vertexShader); //Attach shaders to program
//		glAttachShader(shaderProgram, fragmentShader);
//		glLinkProgram(shaderProgram); //link shaders 
//
//
//		
//
//		//check and call events and swap color buffers
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//		
//
//	}
//}
//
//
//
//
//
////int main(void)
////{
////	GLFWwindow* window;
////
////	/* Initialize the library */
////	if (!glfwInit())
////		return -1;
////
////	/* Create a windowed mode window and its OpenGL context */
////	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
////	if (!window)
////	{
////		glfwTerminate();
////		return -1;
////	}
////
////	
////
////	/* Make the window's context current */
////	glfwMakeContextCurrent(window);
////
////	//viewport変換を行う関数
////	glViewport(0, 0, 320, 240);
////	//リサイズ時にglViewportを逐次呼ぶためのCallback関数プロトタイプ（定義はmain 外で）
////	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
////	//上のコールバックの登録
////	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
////
////	
////
////	/* Loop until the user closes the window */
////	while (!glfwWindowShouldClose(window))
////	{
////		/* Render here */
////		glClear(GL_COLOR_BUFFER_BIT);
////
////		/* Swap front and back buffers */
////		glfwSwapBuffers(window);
////
////		/* Poll for and process events */
////		glfwPollEvents();
////	}
////
////	glfwTerminate();
////	return 0;
////}
////
////
////void framebuffer_size_callback(GLFWwindow* window, int width, int height)
////{
////	glViewport(0, 0, width, height);
////	//debug 
////	cout << width << height << endl;
////}
