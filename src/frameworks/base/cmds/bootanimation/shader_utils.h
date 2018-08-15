
#ifndef _SHADER_UTILS_H
#define _SHADER_UTILS_H

#include <GLES3/gl31.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <string>
#include <vector>


GLuint CompileShader(GLenum type, const std::string &source)
{
	GLuint shader = glCreateShader(type);

	const char *sourceArray[1] = { source.c_str() };
	glShaderSource(shader, 1, sourceArray, nullptr);
	glCompileShader(shader);

	GLint compileResult;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == 0)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Info log length includes the null terminator, so 1 means that the info log is an empty
		// string.
		if (infoLogLength > 1)
		{
			std::vector<GLchar> infoLog(infoLogLength);
			glGetShaderInfoLog(shader, static_cast<GLsizei>(infoLog.size()), nullptr, &infoLog[0]);
			//std::cerr << "shader compilation failed: " << &infoLog[0];
		}
		else
		{
			//std::cerr << "shader compilation failed. <Empty log message>";
		}

		//std::cerr << std::endl;

		glDeleteShader(shader);
		shader = 0;
	}

	return shader;
}

GLuint CheckLinkStatusAndReturnProgram(GLuint program, bool outputErrorMessages)
{
    if (glGetError() != GL_NO_ERROR)
        return 0;

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == 0)
    {
        if (outputErrorMessages)
        {
            GLint infoLogLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

            // Info log length includes the null terminator, so 1 means that the info log is an
            // empty string.
            if (infoLogLength > 1)
            {
                std::vector<GLchar> infoLog(infoLogLength);
                glGetProgramInfoLog(program, static_cast<GLsizei>(infoLog.size()), nullptr,
                                    &infoLog[0]);

                //std::cerr << "program link failed: " << &infoLog[0];
            }
            else
            {
                //std::cerr << "program link failed. <Empty log message>";
            }
        }

        glDeleteProgram(program);
        return 0;
    }

    return program;
}

GLuint CompileProgramWithGSAndTransformFeedback(
    const std::string &vsSource,
    const std::string &gsSource,
    const std::string &fsSource,
    const std::vector<std::string> &transformFeedbackVaryings,
    GLenum bufferMode)
{
    GLuint program = glCreateProgram();

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

    if (vs == 0 || fs == 0)
    {
        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vs);
    glDeleteShader(vs);

    glAttachShader(program, fs);
    glDeleteShader(fs);

    if (!gsSource.empty())
    {
        GLuint gs = CompileShader(GL_GEOMETRY_SHADER_EXT, gsSource);
        if (gs == 0)
        {
            glDeleteShader(vs);
            glDeleteShader(fs);
            glDeleteProgram(program);
            return 0;
        }

        glAttachShader(program, gs);
        glDeleteShader(gs);
    }

    if (transformFeedbackVaryings.size() > 0)
    {
        std::vector<const char *> constCharTFVaryings;

        for (const std::string &transformFeedbackVarying : transformFeedbackVaryings)
        {
            constCharTFVaryings.push_back(transformFeedbackVarying.c_str());
        }

        glTransformFeedbackVaryings(program, static_cast<GLsizei>(transformFeedbackVaryings.size()),
                                    &constCharTFVaryings[0], bufferMode);
    }

    glLinkProgram(program);

    return CheckLinkStatusAndReturnProgram(program, true);
}

GLuint CompileProgramWithGS(const std::string &vsSource,
                            const std::string &gsSource,
                            const std::string &fsSource)
{
    std::vector<std::string> emptyVector;
    return CompileProgramWithGSAndTransformFeedback(vsSource, gsSource, fsSource, emptyVector,
                                                    GL_NONE);
}

GLuint CompileProgram(const std::string &vsSource, const std::string &fsSource)
{
    return CompileProgramWithGS(vsSource, "", fsSource);
}

#endif // _SHADER_UTILS_H
