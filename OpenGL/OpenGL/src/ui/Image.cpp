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

Shader*Image::shader = nullptr;
GLuint Image::texAtlas = 0;
GLuint Image::vao = 0;
GLuint Image::vbo = 0;


Image::Image()
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

            shader->activate();
            GLint uniform = shader->getUniform("uTexture");
            glUniform1i(uniform, 0);

            std::cout << uniform << " " << GL_TEXTURE0;
        }
        glBindVertexArray(0);

    }

    Image::getDefaultStyle()->apply(this);
}

Image::~Image() {
    ASSERT_GL_MAIN_THREAD();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Image::setStyle(prop_t const& prop) {
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
        Component::setStyle(prop);
    }
}

prop_t Image::getStyle(spec_t spec) const {
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
        return Component::getStyle(spec);
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
  glDisable(GL_CULL_FACE);
    glBindVertexArray(vao);
    shader->activate();
    GLint texSampler = shader->getUniform("uTexture");
    glUniform1i(texSampler, 0);
    glActiveTexture(GL_TEXTURE0);
    shader->bindTexture(TEXTURE_COLOR, texAtlas);

    glm::mat4 model = computeModel();
    glm::mat4 textureCoords = computeTexture();

    //std::cout << textureCoords << std::endl;
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
    auto p1 = getTextureOffset();
    auto texture = mat4(1.f);
    texture = translate(texture, glm::vec3(p1,0.0f));
    texture = scale(texture, vec3(getTextureSize(), 1.f));
    return texture;
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
