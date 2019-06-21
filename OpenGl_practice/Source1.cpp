#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
///

using namespace std;

//shaderソース文字列を受け取り、コンパイルし、Object化してProgramにリンクする
GLuint createProgram(const char *vsrc, const char *fsrc) {

	//空のProgram object作成
	const GLuint program(glCreateProgram());

	if (vsrc != NULL)
	{
		//create vertex shader object
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);

		//Vertex shader objectをProgram objectに組み込む
		glAttachShader(program, vobj);
		glDeleteShader(vobj);

	}


	if (fsrc != NULL)
	{
		//create fragment shader object
		const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		//Fragment shader objectをProgram objectに組み込む
		glAttachShader(program, fobj);
		glDeleteShader(fobj);

	}

	// Program objectをリンクする
	glBindAttribLocation(program, 0, "vPos");
	glBindFragDataLocation(program, 0, "FragColor");
	glLinkProgram(program);

	return program;

}

//ファイルを読み込んでBufferに格納する(引数で渡して書き換える)関数
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
	//tellgで現在地を返すことでソースの文字数を取得する
	//static_cast は暗黙の変換が可能なときにその変換を明示する
	GLsizei length = static_cast<GLsizei>(file.tellg());

	//ファイルサイズ分のメモリ確保
	buffer.resize(length + 1);

	//ファイルを先頭から読み込む
	file.seekg(0L, ios::beg); //先頭にポインタ移動
	file.read(buffer.data(), length); //.data()は配列の先頭へのポインタを返す
	buffer[length] = '\0'; //末尾に代入

	if (file.fail()) {
		cerr << "ERROR : could not read source file: " << name << endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

GLuint loadProgram(const char *vert, const char *frag) {
	//Shaderソースファイル読み込み
	std::vector<GLchar> vsrc;
	const bool vstat(readShaderSource(vert, vsrc));
	std::vector<GLchar> fsrc;
	const bool fstat(readShaderSource(frag, fsrc));

	//Program Object　作成
	// condition ? true return : false return これは三項演算子
	// vstat, fstat両方がTrueなら Program objectを作成する
	return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
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

	//Program object作成
	const GLuint program(loadProgram("point.vert", "point.frag"));


	//Create and bind "Vertex buffer object"
	GLuint VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//MainLoop
	while (!glfwWindowShouldClose(window)) {

		//Drawing
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//バッファの入れ替えとイベント処理
		glfwSwapBuffers(window);
		glfwWaitEvents();

	}

	

	return 1;

}