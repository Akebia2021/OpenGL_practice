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

	//locationはVertex shaderのソースコードで指定した
	//glBindAttribLocation(program, 0, "vPos");
	//glBindFragDataLocation(program, 0, "FragColor");
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

	//glViewport(100, 50, 300, 300);


	//triangle vertices
	GLfloat points[] = {
		0.5f, -0.5f, 0.0f,  //右下 1
		0.5f, 0.5f, 0.0f, // 2
		-0.5f, 0.5f, 0.0f, // 3
		//-0.5f, -0.5f, 0.0f	 //左下 4
		-0.5f, -0.5f, 0.0f,
		-0.75f, 0.5f, 0.0f,
		-1.0f, -0.5f, 0.0f
	};
	GLuint indices[] = {
		0,1,2,  //first triangle
		0,2,3  //second triangle
	};

	//Program object作成
	const GLuint program(loadProgram("point.vert", "red.frag"));
	const GLuint program2(loadProgram("point.vert", "yellow.frag"));

	//create empty int object
	GLuint VBO, VAO, EBO;

	//Create and bind "Vertex array object"
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	//最初にVAOをバインドする
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			
	//set the pointer to vertex attribute(vertex attribute will be extracted from shader)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//MainLoop
	while (!glfwWindowShouldClose(window)) {

		//Drawing
		glClear(GL_COLOR_BUFFER_BIT);

		//shader programの読み込み
		glUseProgram(program);

		//時間を乱数生成に利用してUniform変数を更新し色を変化させる
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//uniform変数のLocationを取得してglUniform関数に指定できるようにする
		int vertexColorLocation = glGetUniformLocation(program, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glBindVertexArray(0);



		//バッファの入れ替えとイベント処理
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	

	return 1;

}