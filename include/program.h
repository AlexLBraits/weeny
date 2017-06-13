#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <map>
#include <string>
#include <types.h>

struct Program;
typedef std::shared_ptr<Program> ProgramPtr;

struct Program
{
    Program(const char *vsrc, int vlen, const char *fsrc, int flen);
    ~Program();

    unsigned int id() const;

    unsigned int getAttribId(const char* name) const;
    unsigned int getUniformId(const char* name) const;
    bool isActive() const;
    void bind() const;
    void release() const;

    static ProgramPtr dummy();

    void setUniformValue(const char* name, const glm::vec4& value);
    void setUniformValue(const char* name, const glm::mat4x4& value);

    void setAttribValues(const char* name, const std::vector<glm::vec2>& values);
    void setAttribValues(const char* name, const std::vector<glm::vec3>& values);
    void setAttribValues(const char* name, const std::vector<glm::vec4>& values);

    static void draw();
    static unsigned int activeid();

protected:
    unsigned int m_program;
    static ProgramPtr m_dummy;

    mutable std::map<std::string, unsigned int> m_uniform_ids;
    mutable std::map<std::string, unsigned int> m_attrib_ids;

    std::map<unsigned int, glm::vec4> m_uniform_vec4_buffer;
    std::map<unsigned int, glm::mat4x4> m_uniform_mat4x4_buffer;

    std::map<std::string, std::vector<glm::vec2>> m_attribs_vec2_buffer;
    std::map<std::string, std::vector<glm::vec3>> m_attribs_vec3_buffer;
    std::map<std::string, std::vector<glm::vec4>> m_attribs_vec4_buffer;

    static std::map<unsigned int, Program*> programs;
    static unsigned int active_program;
};


#endif /* PROGRAM_H */
