#include "Image.hpp"
#include "debug/Debug.hpp"
#include "gl/ResourceManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace ui;
using namespace glm;

MAKE_TYPE(Crop);

const spec_t Image::CROP = MAKE_SPEC("Image::crop", Crop);
const spec_t Image::TEXTURE_OFFSET = MAKE_SPEC("Image::textureOffset", glm::vec2);
const spec_t Image::TEXTURE_SIZE = MAKE_SPEC("Image::textureSize", glm::vec2);

static const GLfloat quad[6][2] = {
    { 1.0f, 1.0f },
    { 0.0f, 1.0f },
    { 0.0f, 0.0f },

    { 1.0f, 1.0f },
    { 0.0f, 0.0f },
    { 1.0f, 0.0f },
};

Shader* Image::shader = nullptr;
GLuint Image::texAtlas = 0;
GLuint Image::vao = 0;
GLuint Image::vbo = 0;


Image::Image()
 : crop(Crop::NONE),
   texOffset(0.f),
   texSize(1.f)
{
    if (shader == nullptr) {
        shader = ResourceManager::getShader("image");
        texAtlas = ResourceManager::getTexture("imageAtlas");

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 2, quad, GL_STATIC_DRAW);
            glVertexAttribPointer(VERTEX_POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(VERTEX_POSITION);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            GLint texSampler = shader->getUniform("uTexture");
            glUniform1i(texSampler, 0);
            glActiveTexture(GL_TEXTURE0);
        }
        glBindVertexArray(0);

    }


}

Image::~Image() {
    ASSERT_GL_MAIN_THREAD();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Image::setProperty(prop_t prop) {
    if (prop.spec == Image::CROP) {
        setCrop(prop.value->get<Crop>());
    }
    else if (prop.spec == Image::TEXTURE_OFFSET) {
        setTextureOffset(prop.value->get<glm::vec2>());
    }
    else if (prop.spec == Image::TEXTURE_SIZE) {
        setTextureSize(prop.value->get<glm::vec2>());
    }
    else {
        Component::setProperty(prop);
    }
}

prop_t Image::getProperty(spec_t spec) const {
    if (spec == Image::CROP) {
        return make_property(spec, getCrop());
    }
    else if (spec == Image::TEXTURE_OFFSET) {
        return make_property(spec, getTextureOffset());
    }
    else if (spec == Image::TEXTURE_SIZE) {
        return make_property(spec, getTextureSize());
    }
    else {
        return Component::getProperty(spec);
    }
}

style_const_t Image::getDefaultStyle() const {
    static style_const_t style = Style::make_style(
        Component::getDefaultStyle(),
        make_property(Image::CROP, Crop::NONE),
        make_property(Image::TEXTURE_OFFSET, glm::vec2(0.0f)),
        make_property(Image::TEXTURE_SIZE, glm::vec2(1.0f))
    );
    return style;
}


void Image::draw() {
    shader->activate();
    shader->bindTexture(TEXTURE_COLOR, texAtlas);

    glm::mat4 model = computeModel();
    glm::mat4 textureCoords = computeTexture();

    glBindVertexArray(vao);
    glUniformMatrix4fv(shader->getUniform(MATRIX_MODEL), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shader->getUniform("m_texture"), 1, GL_FALSE, glm::value_ptr(textureCoords));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    Component::draw();
}

glm::mat4 Image::computeModel() {
    auto p1 = getAbsoluteOrigin();
    auto model = mat4(1.f);
    model = translate(model, vec3(p1, 0.f));
    model = scale(model, vec3(getAbsoluteSize(), 1.f));
    return model;
}

glm::mat4 Image::computeTexture() {

    glm::vec2 offset = getTextureOffset();
    glm::vec2 size = getTextureSize();
    calculateCropping(offset, size);

    auto texture = mat4(1.f);
    texture = translate(texture, glm::vec3(offset, 0.0f));
    texture = scale(texture, vec3(size, 1.f));
    return texture;
}

void Image::calculateCropping(glm::vec2& offset, glm::vec2& size) {
    if (crop != Crop::NONE) {
        int w, h;
        int miplevel = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);

        glm::vec2 absoluteSize = getAbsoluteSize();
        glm::vec2 newOffset = offset;
        glm::vec2 newSize = size;
        if (absoluteSize.x / absoluteSize.y < (w * size.x) / (h * size.y)) {
            newSize.x = absoluteSize.x * (h * size.y) / (absoluteSize.y * w);
        }
        else {
            newSize.y = absoluteSize.y * (w * size.x) / (absoluteSize.x * h);

        }
        if (crop == Crop::END)
            newOffset = offset + size - newSize;
        if (crop == Crop::CENTER)
            newOffset = offset + (size - newSize) / 2.0f;
        offset = newOffset;
        size = newSize;
    }
}
void Image::setCrop(Crop crop) {
    if (crop == this->crop) return;
    this->crop = crop;
    queueDraw();
}

Crop Image::getCrop() const {
    return crop;
}

void Image::setTextureOffset(glm::vec2 offset) {
    if (offset == this->texOffset) return;
    this->texOffset = offset;
    queueDraw();
}

glm::vec2 Image::getTextureOffset() const {
    return texOffset;
}

void Image::setTextureSize(glm::vec2 size) {
    if (size == this->texSize) return;
    this->texSize = size;
    queueDraw();
}

glm::vec2 Image::getTextureSize() const {
    return texSize;
}
