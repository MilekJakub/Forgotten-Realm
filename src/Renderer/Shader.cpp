#include "Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const std::string& filePath) {
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::string errorMessage = "Could not open file: " + filePath;
        throw std::runtime_error(errorMessage);
    }

    std::stringstream stringStream;
    stringStream << fileStream.rdbuf(); // Read the file
    fileStream.close();

    return stringStream.str(); // Return the read content as a string
}

Shader::Shader(const char *vertexShaderFilePath, const char *fragmentShaderFilePath)
{
    // Get the current working directory (/Forgotten-Realm/cmake-build-debug)
    std::filesystem::path currentPath = std::filesystem::current_path();

    // Navigate up one directory from the current path (/Forgotten-Realm)
    std::filesystem::path projectRootPath = currentPath.parent_path();

    // Construct the path to the shaders directory relative to the project root
    std::filesystem::path shaderDir = projectRootPath / "src" / "Shaders";

    // Construct the full paths to the vertex and fragment shaders
    std::filesystem::path vertexShaderPath = shaderDir / vertexShaderFilePath;
    std::filesystem::path fragmentShaderPath = shaderDir / fragmentShaderFilePath;

    // Convert the paths to string for use with the file reading function
    std::string vertexShaderFullPath = vertexShaderPath.string();
    std::string fragmentShaderFullPath = fragmentShaderPath.string();

    // Read vertexFile and fragmentFile and store the strings
    std::string vertexShaderSourceCode = get_file_contents(vertexShaderFullPath);
    std::string fragmentShaderSourceCode = get_file_contents(fragmentShaderFullPath);

    // Convert the shader source strings into character arrays
    const char* vertexShaderSource = vertexShaderSourceCode.c_str();
    const char* fragmentShaderSource = fragmentShaderSourceCode.c_str();

    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    Id = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(Id, vertexShader);
    glAttachShader(Id, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(Id);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate() const
{
    glUseProgram(Id);
}

// Deletes the Shader Program
void Shader::Delete() const
{
    glDeleteProgram(Id);
}