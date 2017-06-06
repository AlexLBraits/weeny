#include <visualiser.h>
#include <universe.h>
#include <graphics.h>
///
/// Только здесь должны использоваться команды OpenGL
/// Только здесь должны быть видны типы OpenGL
///
void Visualiser::initialize()
{
}
void Visualiser::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}
void Visualiser::drawUniverse(const Universe& universe)
{
    for(auto& ul : universe) drawUniverseLayer(ul);
}
void Visualiser::drawUniverseLayer(UniverseLayerPtr ulayer)
{

    _clear(0, 1, 0, 1);

    if(ulayer->m_root) drawDrawingNode(ulayer->m_root.get());

}
void Visualiser::drawDrawingNode(DrawingNode* node)
{
    /// рисование нода
    _drawDrawingNode(node);
    /// рисование детей
    for(auto& cn : *node) drawDrawingNode((DrawingNode*)&cn);
}

void Visualiser::_clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Visualiser::_drawDrawingNode(DrawingNode* node)
{
    ////////////////////////////////////////////////////////////////////////////
    /// устанавливаем параметры рисования
    /// программу
    ///
    /// текстуру
    // glBindTexture(GL_TEXTURE_2D, node->m_texture->id());
    /// блендинг

    /// ???

    ////////////////////////////////////////////////////////////////////////////
    /// строим геометрию
    ///
    glm::mat4x4 M(1.0f);
    glm::mat4x4 V = glm::lookAt(
                glm::vec3(10.0f, 10.0f, 5.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
                );
    glm::mat4x4 P = glm::ortho(0.0f, 100.0f, 0.0f, 100.0f, -100.0f, 100.0f);
    glm::mat4x4 transform = P * V * M;

    glm::vec4 color = {1.0f, 0.0f, 1.0f, 1.0f};

    glm::vec3 vertices[] = {
        {0,0,0},
        {100,0,0},
        {100,100,0}
    };

    ////////////////////////////////////////////////////////////////////////////
    /// выводим геометрию
    ///
    node->m_program->bind();
    node->m_program->setUniformValue("color", color);
    node->m_program->setUniformValue("transform", transform);


    GLint Attrib_vertex = node->m_program->getAttribId("coord");
    glEnableVertexAttribArray(Attrib_vertex);
    glVertexAttribPointer(Attrib_vertex, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(Attrib_vertex);

}
