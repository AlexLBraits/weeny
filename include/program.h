#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <map>
#include <string>
#include <vector>
#include <types.h>

enum struct AttributeType {
    UNKNOWN,
    BYTE,
    UNSIGNED_BYTE,
    SHORT,
    UNSIGNED_SHORT,
    INT,
    UNSIGNED_INT,
    FLOAT,
    DOUBLE
};

struct AttribBuffer
{
    AttribBuffer(AttributeType type, size_t item_size, size_t capacity)
        : m_type_id(type),
          m_item_size(item_size),
          m_capacity(capacity),
          m_items_count(0)
    {
    }
    virtual ~AttribBuffer() {}
    virtual void add(size_t count, const void* data) = 0;
    virtual void* data() const = 0;

    AttributeType m_type_id;
    size_t m_item_size;
    size_t m_capacity;
    size_t m_items_count;
};
typedef std::shared_ptr<AttribBuffer> AttribBufferPtr;

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

    void setUniformValue(const char* name, int value);
    void setUniformValue(const char* name, const glm::vec4& value);
    void setUniformValue(const char* name, const glm::mat4x4& value);

    void setAttribValues(const char* name, AttributeType type, size_t size,
                         size_t count, const float* data);

    static void drawBuffers();
    static unsigned int activeid();

private:
    size_t _enableAttribBuffers();
    void _disableAttribBuffers(size_t verticesCount);

protected:
    unsigned int m_program;
    static ProgramPtr m_dummy;

    mutable std::map<std::string, unsigned int> m_uniform_ids;
    mutable std::map<std::string, unsigned int> m_attrib_ids;

    std::map<unsigned int, int> m_uniform_int_buffer;
    std::map<unsigned int, glm::vec4> m_uniform_vec4_buffer;
    std::map<unsigned int, glm::mat4x4> m_uniform_mat4x4_buffer;

    std::map<std::string, AttribBufferPtr> m_attribs_buffer;

    static std::map<unsigned int, Program*> programs;
    static unsigned int active_program;
};


#endif /* PROGRAM_H */
