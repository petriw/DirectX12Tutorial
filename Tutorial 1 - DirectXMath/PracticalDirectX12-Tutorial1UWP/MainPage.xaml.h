//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace PracticalDirectX12_Tutorial1UWP
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		XMFLOAT2 v1Start;
		XMFLOAT2 v1End;
		XMFLOAT2 v1;

		XMFLOAT2 v2Start;
		XMFLOAT2 v2End;
		XMFLOAT2 v2;

		XMFLOAT2 v3;

		int drawingLineId = 0;

		void OnStrokeStarted(Windows::UI::Input::Inking::InkStrokeInput ^sender, Windows::UI::Core::PointerEventArgs ^args);
		void OnStrokeEnded(Windows::UI::Input::Inking::InkStrokeInput ^sender, Windows::UI::Core::PointerEventArgs ^args);
		void DrawResultVector();
		void ResetDrawingCanvas();
	};
}
