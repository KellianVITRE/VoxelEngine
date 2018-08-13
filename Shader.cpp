#include "Shader.h"

std::string readFromFile(const char* pathToFile)
{
	std::string content;
	std::ifstream fileStream(pathToFile, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;

}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
	m_program = glCreateProgram();
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexSource1 = readFromFile(vertexFile);
	std::string fragmentSource1 = readFromFile(fragmentFile);

	const char* vertexSource = vertexSource1.c_str();
	const char* fragmentSource = fragmentSource1.c_str();

	glShaderSource(m_vertexShader, 1, &vertexSource, NULL);

	glCompileShader(m_vertexShader);

	GLint vertexstatus;

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &vertexstatus);

	if (vertexstatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(m_vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(m_vertexShader, infoLogLength, NULL, strInfoLog);

		std::cout << "Vertex shader compilation failed: " << strInfoLog << std::endl;
		delete[] strInfoLog;
		glfwTerminate();
	}

	glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(m_fragmentShader);

	GLint fragmentstatus;

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &fragmentstatus);

	if (fragmentstatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(m_fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(m_fragmentShader, infoLogLength, NULL, strInfoLog);

		std::cout << "Fragment shader compilation failed: " << strInfoLog << std::endl;
		delete[] strInfoLog;
		glfwTerminate();
	}

	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);

	glLinkProgram(m_program);
}

ShaderProgram::~ShaderProgram() {
	glDetachShader(m_program, m_vertexShader);
	glDetachShader(m_program, m_fragmentShader);

	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_program);
}

void ShaderProgram::Bind() {
	glUseProgram(m_program);
}

void ShaderProgram::Unbind() {
	glUseProgram(0);
}

void ShaderProgram::SetUniformMat4(glm::mat4 matrix, const char* location)
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, location), 1, GL_FALSE, &matrix[0][0]);
}