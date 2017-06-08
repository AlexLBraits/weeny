#include <program.h>
#include <graphics.h>
#include <debug.h>

////////////////////////////////////////////////////////////////////////////////
///
///
static const
char* DEFAULT_VERTEX_SHADER = "attribute vec3 coord;\n"
                              "uniform mat4 transform;\n"
                              "void main() {\n"
                              " gl_Position = transform * vec4(coord, 1.0);\n"
                              "}\n";

static const
char* DEFAULT_FRAGMENT_SHADER = "\n"
#ifdef BUILD_GENERIC
#else
                                "precision highp float;\n"
#endif
                                "uniform vec4 color;\n"
                                "void main() {\n"
                                " gl_FragColor = color;\n"
                                "}\n";

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
///
////////////////////////////////////////////////////////////////////////////////

ProgramPtr Program::m_dummy;

Program::Program(const char *vsrc, int vlen,
                 const char *fsrc, int flen)
{
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vsrc, vlen ? &vlen : 0);
    glCompileShader(vshader);
    SHADER_LOG(vshader);

    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fsrc, flen ? &flen : 0);
    glCompileShader(fshader);
    SHADER_LOG(fshader);

    m_program = glCreateProgram();

    glAttachShader(m_program, vshader);
    glAttachShader(m_program, fshader);

    glLinkProgram(m_program);

    PROGRAM_LOG(m_program);
}

unsigned int Program::getAttribId(const char *name) const
{
    return glGetAttribLocation(m_program, name);
}

unsigned int Program::getUniformId(const char *name) const
{
    return glGetUniformLocation(m_program, name);
}

bool Program::isActive() const
{
    GLint activeProgramId;
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgramId);
    return m_program && m_program == activeProgramId;
}

bool Program::bind() const
{
    bool alreadyActive = isActive();
    if(alreadyActive == false)
    {
        glUseProgram(m_program);
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
    return m_program;
}

ProgramPtr Program::dummy()
{
    if(!m_dummy)
    {
        m_dummy = ProgramPtr(
                      new Program(
                          DEFAULT_VERTEX_SHADER, 0,
                          DEFAULT_FRAGMENT_SHADER, 0
                      )
                  );
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

void Program::setUniformValue(const char* name, const glm::vec4 &value)
{
    setUniformValue(getUniformId(name), value);
}

void Program::setUniformValue(const char* name, const glm::mat4x4 &value)
{
    setUniformValue(getUniformId(name), value);
}

void Program::drawTriangles(unsigned int id, const glm::vec3* vertices, size_t size)
{
    glEnableVertexAttribArray(id);
    glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glDisableVertexAttribArray(id);
}

void Program::drawTriangles(const char *name, const glm::vec3* vertices, size_t size)
{
    drawTriangles(getAttribId(name), vertices, size);
}
