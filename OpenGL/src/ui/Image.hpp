#pragma once

#include <GL/glew.h>
#include <memory>
#include <glm/glm.hpp>

#include "ui/Component.hpp"
#include "ui/style/Property.hpp"
#include "ui/style/Specification.hpp"
#include "ui/style/Style.hpp"

class Shader;

enum class Crop { NONE, BEGIN, CENTER, END, REPEAT };


namespace ui {

	class Image : public Component {

	protected:
		Image(glm::ivec2 offset, glm::ivec2 size);

	public:
		static std::unique_ptr<Image> create(glm::ivec2 offset, glm::ivec2 size);
		virtual ~Image();

		void draw() override;

		static const spec_t CROP;
		static const spec_t TEXTURE_OFFSET;
		static const spec_t TEXTURE_SIZE;
		static const spec_t TEXTURE_DIMENSIONS;

		virtual void setProperty(prop_t prop) override;
		virtual prop_t getProperty(spec_t spec) const override;
		virtual style_const_t getDefaultStyle() const override;

		void setCrop(Crop crop);
		Crop getCrop() const;

		void setTextureOffset(glm::ivec2 offset);
		glm::ivec2 getTextureOffset() const;

		void setTextureSize(glm::ivec2 size);
		glm::ivec2 getTextureSize() const;

		void setTextureDimensions(glm::vec2 dimensions);
		glm::vec2 getTextureDimensions() const;

		void setMagFilter(GLint param);
		void setMinFilter(GLint param);
	private:
		glm::mat4 computeModel();
		glm::mat4 computeTexture();
		void calculateCropping(glm::ivec2& offset, glm::ivec2& size);
		static Shader* shader;
		static GLuint texAtlas;

		GLint minFilter;
		GLint magFilter;

		static GLuint vao, vbo;
	};

}; // namespace ui
