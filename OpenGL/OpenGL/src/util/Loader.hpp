#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <memory>
#include <string>

#include "GL/glew.h"
#include "Mesh.hpp"

typedef std::unique_ptr<Mesh> ptr2mesh;


class Loader
{
public:
    ~Loader();

    // TODO: see if we keep those or not. Currently the mesh ctor manages this.
    // ptr2mesh loadToVAO(const std::vector<GLfloat>& positions,
    //     const std::vector<GLuint>& indices,
    //     const std::vector<GLfloat>& texture);
    //
    // ptr2mesh loadToVAO(const std::vector<GLfloat>& positions,
    //     const std::vector<GLfloat>& texture);

    GLuint loadTexture(const std::string& fileName);
    GLuint loadCubeMap(std::vector<std::string> faces);


private:
    void bindIndexBuffer(const std::vector<GLuint>& indices);

    GLuint createVAO();
    GLuint createVBO(GLenum type);
    void unbindVAO();

    template<typename T>
    GLuint storeDataInAttributeList(int attributeID, int coordCount, const std::vector<T>& data)
    {
        GLuint vbo = createVBO(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(attributeID, coordCount, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(attributeID);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vbo;

    }

    std::vector<GLuint> textureList;
};

#endif // LOADER_H
