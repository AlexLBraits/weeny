#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <map>
#include <string>
#include <vector>
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

    void setUniformValue(const char* name, int value);
    void setUniformValue(const char* name, const glm::vec4& value);
    void setUniformValue(const char* name, const glm::mat4x4& value);

    void setAttribValues(const char* name, size_t size, size_t count, const float* data);

    static void draw();
    static unsigned int activeid();

protected:
    unsigned int m_program;
    static ProgramPtr m_dummy;

    mutable std::map<std::string, unsigned int> m_uniform_ids;
    mutable std::map<std::string, unsigned int> m_attrib_ids;

    std::map<unsigned int, int> m_uniform_int_buffer;
    std::map<unsigned int, glm::vec4> m_uniform_vec4_buffer;
    std::map<unsigned int, glm::mat4x4> m_uniform_mat4x4_buffer;

    struct AttribBuffer
    {
        AttribBuffer(size_t item_size, size_t capacity = 30720)
            : m_item_size(item_size),
              m_capacity(capacity),
              m_items_count(0)
        {
            m_buffer = (float*)malloc(m_capacity * m_item_size * sizeof(float));
        }
        ~AttribBuffer()
        {
            free(m_buffer);
        }
        void add(size_t count, const void* data)
        {
            memcpy(
                   m_buffer + m_items_count * m_item_size,
                   data,
                   count * m_item_size * sizeof(float)
                   );
            m_items_count += count;
        }
        void* data() const
        {
            return m_buffer;
        }

        size_t m_item_size;
        size_t m_capacity;
        size_t m_items_count;

    private:
        float* m_buffer;
    };
    std::map<std::string, AttribBuffer> m_attribs_buffer;

    static std::map<unsigned int, Program*> programs;
    static unsigned int active_program;
};


#endif /* PROGRAM_H */
