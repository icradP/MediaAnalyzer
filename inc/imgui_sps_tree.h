#pragma once

#include <stdio.h>      // sprintf, scanf
#include <stdint.h>     // uint8_t, etc.
#include <math.h>       // sqrtf, powf, cosf, sinf, floorf, ceilf

#if defined(_MSC_VER) || defined(_UCRT)
#define _PRISizeT   "I"
#define ImSnprintf  _snprintf
#else
#define _PRISizeT   "z"
#define ImSnprintf  snprintf
#endif

#if defined(_MSC_VER) || defined(_UCRT)
#pragma warning (push)
#pragma warning (disable: 4996) // warning C4996: 'sprintf': This function or variable may be unsafe.
#endif
 
inline void HelpMarker(const char *desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

extern SPSHelper spshelper;
void show_sps_info_windows(){
    //IMGUI_DEMO_MARKER("Configuration");
    if (ImGui::CollapsingHeader("SPS Tree"))
    {
        ImGuiIO& io = ImGui::GetIO();
        
      
        
        // if (ImGui::TreeNode("Configuration##2")) 
        // {
        //     ImGui::SeparatorText("General");
        //     ImGui::SeparatorText("Docking");
        //     { ImGui::Indent();
        //         ImGui::SeparatorText("General");
        //             ImGui::SeparatorText("Docking");
        //                         ImGui::Text("Also see Style->Rendering for rendering options.");
        //         ImGui::Unindent();
         
        //     }
        //     ImGui::SeparatorText("Error Handling");
        //     ImGui::SeparatorText("Debug");
        //     ImGui::TreePop();
        //     ImGui::Spacing();
        // }

        // if (ImGui::TreeNode("Backend Flags"))
        // {
        //     ImGui::TreePop();
        //     ImGui::Spacing();
        // }

        // if (ImGui::TreeNode("Style"))
        // {
        //     static bool test_style = false;
        //     ImGui::Checkbox("Style Editor", &test_style);
        //     ImGui::SameLine();
        //     HelpMarker("The same contents can be accessed in 'Tools->Style Editor' or by calling the ShowStyleEditor() function.");
        //     ImGui::TreePop();
        //     ImGui::Spacing();
        // }

        // if (ImGui::TreeNode("Capture/Logging"))
        // {
        //     HelpMarker(
        //         "The logging API redirects all text output so you can easily capture the content of "
        //         "a window or a block. Tree nodes can be automatically expanded.\n"
        //         "Try opening any of the contents below in this window and then click one of the \"Log To\" button.");
        //     ImGui::LogButtons();

        //     HelpMarker("You can also call ImGui::LogText() to output directly to the log without a visual output.");
        //     if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
        //     {
        //         ImGui::LogToClipboard();
        //         ImGui::LogText("Hello, world!");
        //         ImGui::LogFinish();
        //     }
        //     ImGui::TreePop();
        // }
    }
}
 