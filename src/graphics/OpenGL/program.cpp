#include <program.h>
#include <graphics.h>
#include <debug.h>

#define SHADER_LOG(shader) {\
    char logbuf[1024];\
    int logLen;\
    glGetShaderInfoLog(shader, 1024, &logLen, logbuf);\
    if(logLen) LOGD("ShaderLog: %s\n", logbuf);\
}

#define PROGRAM_LOG(program) {\
    int link_ok;\
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);\
    if(!link_ok) LOGD("error attach shaders \n");\
}

ProgramPtr Program::m_dummy;

Program::Program()
    : m_id(0)
{

}

Program::Program(const unsigned char* vsrc, unsigned int vlen,
                 const unsigned char* fsrc, unsigned int flen)
    : Program()
{

}

unsigned int Program::getAttribId(const char *name) const
{
    return glGetAttribLocation(m_id, name);
}

unsigned int Program::getUniformId(const char *name) const
{
    return glGetUniformLocation(m_id, name);
}

bool Program::isActive() const
{
    GLint activeProgramId;
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgramId);
    return m_id && m_id == activeProgramId;
}

bool Program::bind() const
{
    bool alreadyActive = isActive();
    if(alreadyActive == false)
    {
        glUseProgram(m_id);
        alreadyActive = isActive();
    }
    return alreadyActive;
}

void Program::release() const
{
    if(isActive()) glUseProgram(0);
}

Program::~Program()
{
    release();
}

unsigned int Program::id() const
{
    return m_id;
}

ProgramPtr Program::dummy()
{
    if(!m_dummy)
    {
        m_dummy = ProgramPtr(new Program());

        const char* vsource = "attribute vec3 coord;\n"
                              "uniform mat4 transform;\n"
                              "void main() {\n"
                              " gl_Position = transform * vec4(coord, 1.0);\n"
                              "}\n";

        const char* fsource = ""
#ifdef BUILD_GENERIC
#else
                              "precision highp float;\n"
#endif
                              "uniform vec4 color;\n"
                              "void main() {\n"
                              " gl_FragColor = color;\n"
                              "}\n";

        GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vshader, 1, &vsource, NULL);
        glCompileShader(vshader);
        SHADER_LOG(vshader);

        GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fshader, 1, &fsource, NULL);
        glCompileShader(fshader);
        SHADER_LOG(fshader);

        GLuint program = glCreateProgram();

        glAttachShader(program, vshader);
        glAttachShader(program, fshader);

        glLinkProgram(program);

        PROGRAM_LOG(program);

        m_dummy->m_id = program;
    }
    return m_dummy;
}

void Program::setUniformValue(unsigned int id, const glm::vec4 &value)
{
    glUniform4fv(id, 1, glm::value_ptr(value));
}

void Program::setUniformValue(unsigned int id, const glm::mat4x4 &value)
{
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::setUniformValue(const char *name, const glm::vec4 &value)
{
    setUniformValue(getUniformId(name), value);
}

void Program::setUniformValue(const char *name, const glm::mat4x4 &value)
{
    setUniformValue(getUniformId(name), value);
}
