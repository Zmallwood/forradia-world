#include "GUI_Button.h"

#include "Engine/Graphics.h"
#include "Input/Mouse_Input.h"

namespace FW
{
    GUI_Button::GUI_Button(const Graphics& graphics, Mouse_Input& mouseInput, std::string_view text, std::function<void()> action, float x, float y, float w, float h)
        : GUI_Component(graphics, x, y), m_mouseInput(mouseInput), m_text(text), m_action(action), m_size({w, h})
    {
    }

    void GUI_Button::UpdateDerived() {
        if (m_mouseInput.GetLeftMouseButtonRef().GetIsPressed())
        {
            m_action();
        }
    }

    void GUI_Button::RenderDerived() const {

        auto p = GetPosition();
        auto s = m_size;

        GetGraphicsRef().DrawImage(
            "GUIButtonDefaultBackground", p.x, p.y, s.w,
            s.h);
        }

    Rect_F GUI_Button::GetBounds() const {
        auto position = GetPosition();

        return {position.x, position.y, m_size.w, m_size.h};
    }
}
