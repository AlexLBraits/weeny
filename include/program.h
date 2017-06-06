#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <types.h>

struct Program;
typedef std::shared_ptr<Program> ProgramPtr;

struct Program
{
    Program();
    Program(const unsigned char* vsrc, unsigned int vlen,
            const unsigned char* fsrc, unsigned int flen);
    ~Program();

    unsigned int id() const;

    unsigned int getAttribId(const char* name) const;
    unsigned int getUniformId(const char* name) const;
    bool isActive() const;
    bool bind() const;
    void release() const;

    static ProgramPtr dummy();

    void setUniformValue(unsigned int id, const glm::vec4& value);
    void setUniformValue(unsigned int id, const glm::mat4x4& value);
    void setUniformValue(const char* name, const glm::vec4& value);
    void setUniformValue(const char* name, const glm::mat4x4& value);

private:
    unsigned int m_id;
    static ProgramPtr m_dummy;
};

#endif /* PROGRAM_H */
