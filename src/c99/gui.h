#ifndef ARI_GUI_H
#define ARI_GUI_H

#include "macros.h"
#include "en.h"

struct ImVec2;

// System functions
CARI_API void* CreateGuiSystem();

// GUI...
CARI_COMPONENT_HANDLE(GuiHandle)
struct GuiMembers
{
    bool* SameLine;
	bool* Separator;
	bool* Visible;
};
CARI_API bool IsValidGui(uint32_t& _handle);
CARI_API GuiMembers GetGuiMembers(void* _node);

// Window
struct WindowMembers
{
    char	**	Name;
    bool	*	CloseButton,
            *   isOpen;
    ImVec2	*	Pos,
            *   Size;
    int     *	Flags;
};
CARI_API GuiHandle CreateWindowComponent();
CARI_API void AddWindowToWorld(void* _world, EntityHandle* _entity, GuiHandle* _node);
CARI_API void RemoveWindowFromWorld(void* _world, EntityHandle* _entity, GuiHandle* _node, bool _dispose);
CARI_API WindowMembers GetWindowMembers(void* _node);

// Script GUI
typedef bool(sgBeginRender)(void* _userData);
typedef void(sgEndRender)(void* _userData);

CARI_API GuiHandle CreateScriptGuiComponent();
CARI_API void AddScriptGuiToWorld(void* _world, EntityHandle* _entity, GuiHandle* _node);
CARI_API void RemoveScriptGuiFromWorld(void* _world, EntityHandle* _entity, GuiHandle* _node, bool _dispose);
CARI_API void InitScriptGuiMembers(void* _node, void* _userData, sgBeginRender* OnBegineRender, sgEndRender* OnEndRender);

#endif // ARI_GUI_H
