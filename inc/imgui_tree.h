#pragma once

#include <stdio.h>      // sprintf, scanf
#include <stdint.h>     // uint8_t, etc.

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
 

void show_tree_windows(){

 int nLeafNum = 30000;
 ImGui::Begin("Large Tree Optimaize");
 if (ImGui::TreeNodeEx("Large Tree"))
 {
     //query window and node info
     ImVec2  vLastItem = ImGui::GetItemRectMax();
     ImVec2  vItemSize = ImGui::GetItemRectSize();
     ImVec2  vWindowPos = ImGui::GetWindowPos();
     ImVec2  vWindowSize = ImGui::GetWindowSize();

    //measure the number of node to draw
     int nLeafStart = std::max(int((vWindowPos.y - vLastItem.y) / vItemSize.y), 0);
     int nLeafCanDraw = std::min(int(vWindowSize.y / vItemSize.y), (int)nLeafNum - nLeafStart);

     //blank rect for those node beyond window
     if (nLeafStart > 0 && nLeafCanDraw > 0)
     {
         ImGui::Dummy(ImVec2(10.0f, float(nLeafStart) * vItemSize.y));
     }

    //all the node we could see
     int nDrawLeaf = nLeafStart;
     while (nDrawLeaf < nLeafCanDraw+ nLeafStart && nDrawLeaf < nLeafNum)
     {
         auto strLeafName = std::to_string(nDrawLeaf);
         bool bIsKey = nDrawLeaf % 10 == 0;
         ImGui::PushID(0); ImGui::PushStyleColor(ImGuiCol_Text, bIsKey ? ImVec4(1.0f, 0.0f, 0.0f, 1.0f) : ImVec4(0.5f, 0.5f, 0.5f, 0.8f));
         if (ImGui::TreeNodeEx(strLeafName.c_str(), ImGuiTreeNodeFlags_Leaf))
         {
             ImGui::TreePop();
         }
         ImGui::PopStyleColor(1); ImGui::PopID();
         nDrawLeaf++;
     }

     //blank rect for those node exceed window bottom
     if (nDrawLeaf < nLeafNum)
     {
         ImGui::Dummy(ImVec2(10.0f, float(nLeafNum - nDrawLeaf) * vItemSize.y));
     }
     ImGui::TreePop();
 }
 ImGui::End();
}
 