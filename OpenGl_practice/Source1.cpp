#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
///

using namespace std;

Gluint createProgram(const char *vsrc, const char *fsrc) {

}


bool readShaderSource(const char *name, vector<GLchar> &buffer) {

	if (name == NULL) return false;

	//bynaryモードでファイルを読み込む
	ifstream file(name, ios::binary);
	//fileの読み込みに失敗した場合はエラーコード出力
	if (file.fail()) {
		cerr << "ERROR : can't open source file: " << name << endl;
		return false;
	}

	//ファイルの末尾に移動し、tellgで現在位置を変数に格納することでファイルサイズを得る
	//seekg関数は第一引数に基準からのオフセット、第二引数に基準位置(3パターン)
	//ここではios::endから０のオフセット、つまりはファイル終端へポインタ移動
	file.seekg(0L, ios::end);
	//GLsizeiは整数型 tellg関数は現在のポインタ位置を整数で返す関数
	//static_cast は暗黙の変換が可能なときにその変換を明示する
	GLsizei length = static_cast<GLsizei>(file.tellg());

	buffer.resize(length + 1);

	file.seekg(0L, ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail()) {
		cerr << "ERROR : could not read source file: " << name << endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}


int main() {
	

	//glfw 初期化
	if (!glfwInit()) {
		cerr << "can't initialize glfw" << endl;
		return 1;
	}
	//atexitにterminateを登録し、終了時に自動的にCallする
	atexit(glfwTerminate);

	//windowの特性を設定する
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//windowを作成しそのContext を Currentに設定する	
	GLFWwindow* window = glfwCreateWindow(640, 480, "window 1", NULL, NULL);
	if (!window) {
		cerr << "could not create a window" << endl;
		return 1;
	}
	glfwMakeContextCurrent(window);

	//glad 初期化　おまじない？？これでgl関数が利用できるようになる
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//GPUの情報をglGetString()で取得してみる。
	const GLubyte* renderer = glGetString(GL_RENDERER);
	cout << "renderer :" << renderer << endl;

	//背景色の指定 描画命令はglClearが行う
	glClearColor(0.3f, 0.3f, 0.4f, 1);

	//triangle vertices
	GLfloat points[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	//Create and bind "Vertex buffer object"
	GLuint VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//MainLoop
	while (!glfwWindowShouldClose(window)) {

		//Drawing
		glClear(GL_COLOR_BUFFER_BIT);

		
		//バッファの入れ替えとイベント処理
		glfwSwapBuffers(window);
		glfwWaitEvents();

	}

	

	return 1;

}