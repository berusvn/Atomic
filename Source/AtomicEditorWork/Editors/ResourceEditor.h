// Copyright (c) 2014-2015, THUNDERBEAST GAMES LLC All rights reserved
// Please see LICENSE.md in repository root for license information
// https://github.com/AtomicGameEngine/AtomicGameEngine

#pragma once

#include <Atomic/Core/Object.h>

#include <Atomic/UI/UIButton.h>
#include <Atomic/UI/UITabContainer.h>

using namespace Atomic;
using namespace tb;

namespace AtomicEditor
{

class EditorTabLayout;

class ResourceEditor: public Object
{
    OBJECT(ResourceEditor);

public:

    ResourceEditor(Context* context, const String& fullpath, UITabContainer* container);

    virtual ~ResourceEditor();

    UIButton* GetButton() { return button_; }

    virtual bool HasUnsavedModifications() { return false; }

    virtual void SetFocus() {}
    virtual void Close(bool navigateToAvailableResource = true);

    virtual bool OnEvent(const TBWidgetEvent &ev) { return false; }

    virtual bool FindText(const String& text, unsigned flags) { return false; }
    virtual void FindTextClose() { }

    virtual bool RequiresInspector() { return false; }

    const String& GetFullPath() { return fullpath_; }

    UIWidget* GetRootContentWidget() { return rootContentWidget_; }

protected:

    String fullpath_;

    EditorTabLayout* editorTabLayout_;

    SharedPtr<UITabContainer> container_;
    SharedPtr<UIWidget> rootContentWidget_;
    SharedPtr<UIButton> button_;

private:

    void HandleFileChanged(StringHash eventType, VariantMap& eventData);

};

}