#include "GUI_Button.hpp"

#include "Engine/Graphics.hpp"
#include "Input/Mouse_Input.hpp"

namespace FW
{
    GUI_Button::GUI_Button(const Graphics& graphics, Mouse_Input& mouseInput, std::string_view text, std::function<void()> action, float x, float y, float w, float h)
        : GUI_Component(graphics, x, y), m_mouseInput(mouseInput), m_text(text), m_action(action), m_size({w, h})
    {
    }

    void GUI_Button::UpdateDerived() {
        auto bounds = GetBounds();
        auto mousePosition = m_mouseInput.GetMousePosition();

        if (bounds.Contains(mousePosition))
        {
            if (m_mouseInput.GetLeftMouseButtonRef().GetIsPressed())
            {
                m_action();
            }
        }
    }

    void GUI_Button::RenderDerived() const {

        auto bounds = GetBounds();

        GetGraphicsRef().DrawImage(
            "GUIButtonDefaultBackground", bounds.x, bounds.y, bounds.w,
            bounds.h);
        }

    Rect_F GUI_Button::GetBounds() const {
        auto position = GetPosition();

        return {position.x, position.y, m_size.w, m_size.h};
    }
}
