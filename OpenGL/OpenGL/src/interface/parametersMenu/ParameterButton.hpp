#pragma once

#include <memory>
#include <string>

#include "ui/Box.hpp"
#include "ui/Button.hpp"
#include "ui/Text.hpp"

class Font;

class ParameterButton : public ui::Box {

public:
	static std::unique_ptr<Box> create(std::string parameterName, std::unique_ptr<ui::Button> inputComponent);

	virtual void draw() override;

	std::unique_ptr<ui::Button> button;

protected:
	ParameterButton(std::string parameterName, std::shared_ptr<const Font> font, std::unique_ptr<ui::Button> inputComponent);

private:
	std::unique_ptr<ui::Text> title;
};