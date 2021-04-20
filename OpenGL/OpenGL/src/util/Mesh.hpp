#ifndef Mesh_H
#define Mesh_H

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <vector>

class Mesh
{
public:
    Mesh(std::vector<GLfloat> const& positions,
         std::vector<GLfloat> const& normals,
         std::vector<GLfloat> const& textureCoords,
         std::vector<GLuint>  const& indices);

    Mesh(GLuint vao, GLuint vbo, GLuint ebo, GLuint vertCount);
    ~Mesh();

    Mesh(Mesh const&) = delete;
    Mesh& operator=(Mesh const&) = delete;

    GLuint getVAO() const;
    GLuint getVertexCount() const;

    glm::mat4 model = glm::mat4(1.f);

private:
    GLuint myVAO;
    GLuint myVBO;
    GLuint myEBO;
    GLuint myVertCount;
};

#endif // Mesh_H