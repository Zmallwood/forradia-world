#pragma once

#include "GUI_Component.hpp"

namespace FW
{
    class Mouse_Input;

    class GUI_Button : public GUI_Component
    {
        public:
            GUI_Button(const Graphics& graphics, Mouse_Input& mouseInput, std::string_view text, std::function<void()> action, float x, float y, float w, float h);

            void UpdateDerived() override;

            void RenderDerived() const override;

        private:
            Rect_F GetBounds() const;

            // State
            Size_F m_size {0.0f, 0.0f};
            std::string m_text;
            std::function<void()> m_action;

            // Dependencies
            Mouse_Input& m_mouseInput;
    };
}
