#pragma once

#include "Scene/GameObject.hpp"
#include "Core/Functor.hpp"
#include "Graphics/RenderContext.hpp"
#include "UI/UIElementConfig.hpp"
#include "UI/UIUtils.hpp"

class Renderer;
class UIGroup;

class UIElement;

using UIElementCallback = SFun<void(UIElement *uiElement)>;

CLASS(FunctorUIElement, Functor<UIElementCallback>)
{
	PUB(UIElement, NONE, UIElement *)

public:

	VIR void execute() OVR
	{
		if (mCallback)
		{
			mCallback(mUIElement);
		}
	}

	COPY(FunctorUIElement)
	{
		DO_COPY(UIElement)
		Functor<UIElementCallback>::copy(other);
	}
};

CLASS(UIElement, GameObject)
{
	PRO(Config, GETREF_CONST_SET, UIElementConfig)

	PRO(OnPressedFunctor, NONE, FunctorUIElement)
	PRO(OnReleasedFunctor, NONE, FunctorUIElement)

	PRO(OnScrollFunctor, NONE, FunctorUIElement)

	PRO(OnTextChangedFunctor, NONE, FunctorUIElement)
	PRO(OnFocusLostFunctor, NONE, FunctorUIElement)

	PRO(Renderer, GET, Renderer *)
	//PRI(Collider, GET, Collider*)
	PRO(InputString, GET, SStr)
	PRO(ConsumeInput, GET_SET, bool)
	PRO(Pressed, GET, bool)
	PRO(CanToggle, GET, bool)
	PRO(ReleaseOnSameGroupPressed, GET, bool)
	PRO(Toggled, GET, bool)

	void press();
	void executePressAndRelease(bool force = false);
	void release(bool force = false);

public:
	VIR void init() OVR;
	VIR void initFromConfig(CNS UIElementConfig& config);
	VIR void onDestroy();

	void subscribeToKeyEvents();
	void subscribeToCharEvents();
	void subscribeToMouseEvents();
	void subscribeToScrollEvents();
	void subscribeToEnterEvent();
	void subscribeToEscEvent();

	bool hasFocus() CNS;

	bool isMouseCursorInsideElement();

	VIR void onChar(char character);

	VIR void setText(CNS SStr &text) { };

	VIR void onPressed();
	VIR void onReleased();

	void simulateClick();

	VIR void onMouseOver();

	VIR void onScroll(f32 scroll);

	VIR void onFocusLost();
	void onFocus();

	void setOnPressedCallback(UIElementCallback callback)
	{
		mOnPressedFunctor.mUIElement = this;
		mOnPressedFunctor.setCallback(callback);
	}

	void setOnReleasedCallback(UIElementCallback callback)
	{
		mOnReleasedFunctor.mUIElement = this;
		mOnReleasedFunctor.setCallback(callback);
	}

	void setOnTextChangedCallback(UIElementCallback callback)
	{
		mOnTextChangedFunctor.mUIElement = this;
		mOnTextChangedFunctor.setCallback(callback);
	}

	void setOnFocusLostCallback(UIElementCallback callback)
	{
		mOnFocusLostFunctor.mUIElement = this;
		mOnFocusLostFunctor.setCallback(callback);
	}

	void setComponentsCache();

	VIR void setVisibility(bool visibility);
	bool isVisible();
};