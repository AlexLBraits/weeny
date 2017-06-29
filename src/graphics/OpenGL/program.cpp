#include <program.h>
#include <graphics.h>
#include <base/debug.h>
#include <vector>
#include <list>

////////////////////////////////////////////////////////////////////////////////
///
///
static const
char* DEFAULT_VERTEX_SHADER = "attribute vec3 coords;\n"
                              "attribute vec2 uvs;\n"
                              "attribute vec4 colors;\n"
                              "uniform mat4 transform;\n"
                              "varying vec2 uv;\n"
                              "varying vec4 color;\n"
                              "void main(){\n"
                              "gl_Position=transform*vec4(coords,1.0);\n"
                              "uv=uvs;\n"
                              "color=colors;\n"
                              "}";

static const
char* DEFAULT_FRAGMENT_SHADER = "\n"
#ifdef BUILD_GENERIC
#else
                                "precision highp float;\n"
#endif
                                "varying vec2 uv;\n"
                                "varying vec4 color;\n"
                                "uniform sampler2D texture;\n"
                                "void main(){\n"
                                "vec4 vcolor=color;\n"
                                "vcolor.rgb*=vcolor.a;\n"
                                "gl_FragColor=vcolor*texture2D(texture,uv);\n"
                                "}";

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
std::map<unsigned int, Program*> Program::programs;
unsigned int Program::active_program = 0;
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
    Program::programs[m_program] = this;

    glAttachShader(m_program, vshader);
    glAttachShader(m_program, fshader);

    glLinkProgram(m_program);

    PROGRAM_LOG(m_program);
}

Program::~Program()
{
    Program::programs.erase(m_program);
    release();
}

unsigned int Program::getAttribId(const char *name) const
{
    unsigned int attrib_id = 0;
    auto ii = m_attrib_ids.find(name);
    if(ii == m_attrib_ids.end())
    {
        attrib_id = m_attrib_ids[name] = glGetAttribLocation(m_program, name);
    }
    else
    {
        attrib_id = ii->second;
    }
    return attrib_id;
}

unsigned int Program::getUniformId(const char *name) const
{
    unsigned int uniform_id = 0;
    auto ii = m_uniform_ids.find(name);
    if(ii == m_uniform_ids.end())
    {
        uniform_id = m_uniform_ids[name] = glGetUniformLocation(m_program, name);
    }
    else
    {
        uniform_id = ii->second;
    }
    return uniform_id;
}

bool Program::isActive() const
{
    return m_program && m_program == Program::active_program;
}

void Program::bind() const
{
    if(!isActive())
    {
        glUseProgram(Program::active_program = m_program);
    }
}

void Program::release() const
{
    if(isActive()) glUseProgram(0);
}

unsigned int Program::id() const
{
    return m_program;
}
///
/// \brief Program::dummy
/// \return
///
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
///
/// \brief Program::setUniformValue
/// \param name
/// \param value
///
void Program::setUniformValue(const char *name, int value)
{
    unsigned int uniform_id = getUniformId(name);
    auto ii = m_uniform_int_buffer.find(uniform_id);

    if(ii == m_uniform_int_buffer.end())
    {
        glUniform1i(uniform_id, value);
        m_uniform_int_buffer[uniform_id] = value;
    }
    else if(ii->second != value)
    {
        draw();

        glUniform1i(uniform_id, value);
        m_uniform_int_buffer[uniform_id] = value;
    }
}
///
/// \brief Program::setUniformValue
/// \param name
/// \param value
///
void Program::setUniformValue(const char *name, const glm::vec4 &value)
{
    unsigned int uniform_id = getUniformId(name);
    auto ii = m_uniform_vec4_buffer.find(uniform_id);

    if(ii == m_uniform_vec4_buffer.end())
    {
        glUniform4fv(uniform_id, 1, glm::value_ptr(value));
        m_uniform_vec4_buffer[uniform_id] = value;
    }
    else if(ii->second != value)
    {
        draw();

        glUniform4fv(uniform_id, 1, glm::value_ptr(value));
        m_uniform_vec4_buffer[uniform_id] = value;
    }
}
///
/// \brief Program::setUniformValue
/// \param name
/// \param value
///
void Program::setUniformValue(const char *name, const glm::mat4x4 &value)
{
    unsigned int uniform_id = getUniformId(name);
    auto ii = m_uniform_mat4x4_buffer.find(uniform_id);

    if(ii == m_uniform_mat4x4_buffer.end())
    {
        glUniformMatrix4fv(uniform_id, 1, GL_FALSE, glm::value_ptr(value));
        m_uniform_mat4x4_buffer[uniform_id] = value;
    }
    else if(ii->second != value)
    {
        draw();
        glUniformMatrix4fv(uniform_id, 1, GL_FALSE, glm::value_ptr(value));
        m_uniform_mat4x4_buffer[uniform_id] = value;
    }
}
///
/// \brief Program::addAttribValues - добавляет данные в буффер аттрибутов
/// \param name - имя аттрибута
/// \param size - длина аттрибута
/// \param count - количество добавляемых аттрибутов
/// \param data - указатель на начало данных
///
void Program::setAttribValues(
    const char *name,
    size_t size,
    size_t count,
    const float *data
)
{
    auto it = m_attribs_buffer.find(name);
    if (it ==  m_attribs_buffer.end())
    {
        auto ep = m_attribs_buffer.emplace(name, size);
        it = ep.first;
    }

    AttribBuffer& buf = it->second;
    if (buf.m_items_count + count > buf.m_capacity) draw();
    buf.add(count, data);
}
///
/// \brief Program::activeid
/// \return - возвращает идентификатор активной программы
///
unsigned int Program::activeid()
{
    GLint activeProgramId;
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgramId);
    return activeProgramId;
}
///
/// \brief Program::drawBuffers - отрисовывает информацию, накопленную
/// в буферах аттрибутов
///
void Program::draw()
{
    Program* program = 0;
    auto ii = Program::programs.find(Program::activeid());
    if(ii != Program::programs.end()) program = ii->second;

    if(program == 0) return;

    ////////////////////////////////////////////////////////////////////////////
    ///
    /// включаем именованные буферы аттрибутов
    ///
    /// накапливаем список идентификаторов в векторе attribIds
    /// для последующего выключения
    ///
    /// в разных буферах может содержаться разное количество вершин,
    /// поэтому подсчитываем количество вершин для рисования
    /// в переменной verticesCount
    /// это будет минимальное количество вершин из всех буферов
    ///
    std::vector<unsigned int> attribIds;
    attribIds.reserve(program->m_attribs_buffer.size());
    size_t verticesCount = SIZE_MAX;

    for(auto& vp : program->m_attribs_buffer)
    {
        unsigned int attrib_id = program->getAttribId(vp.first.c_str());
        glEnableVertexAttribArray(attrib_id);
        glVertexAttribPointer(attrib_id, vp.second.m_item_size, GL_FLOAT, GL_FALSE, 0, vp.second.data());
        attribIds.push_back(attrib_id);
        verticesCount = std::min(verticesCount, vp.second.m_items_count);
    }
    ///
    /// отрисовываем verticesCount вершин из включенных буферов аттрибутов
    ///
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    ///
    /// включаем буферы аттрибутов по идентификаторам из вектора attribIds
    ///
    for(const auto& id : attribIds)
    {
        glDisableVertexAttribArray(id);
    }
    ///
    /// уменьшаем количество вершин в буфферах
    /// на verticesCount - величину отрисованных вершин
    ///
    for(auto& vp : program->m_attribs_buffer)
    {
        vp.second.m_items_count -= verticesCount;
    }
}
