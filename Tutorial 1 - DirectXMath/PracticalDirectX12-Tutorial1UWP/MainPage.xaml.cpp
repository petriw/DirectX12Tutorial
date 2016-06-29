//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PracticalDirectX12_Tutorial1UWP;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace DirectX;
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	// Accept the following input
	inkCanvas->InkPresenter->InputDeviceTypes =
		Windows::UI::Core::CoreInputDeviceTypes::Mouse |
		Windows::UI::Core::CoreInputDeviceTypes::Pen |
		Windows::UI::Core::CoreInputDeviceTypes::Touch;

	// Set default ink color
	auto dA = inkCanvas->InkPresenter->CopyDefaultDrawingAttributes();
	dA->Color = Windows::UI::Colors::BlueViolet;
	inkCanvas->InkPresenter->UpdateDefaultDrawingAttributes(dA);

	// Events
	inkCanvas->InkPresenter->StrokeInput->StrokeStarted += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Input::Inking::InkStrokeInput ^, Windows::UI::Core::PointerEventArgs ^>(this, &PracticalDirectX12_Tutorial1UWP::MainPage::OnStrokeStarted);
	inkCanvas->InkPresenter->StrokeInput->StrokeEnded += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Input::Inking::InkStrokeInput ^, Windows::UI::Core::PointerEventArgs ^>(this, &PracticalDirectX12_Tutorial1UWP::MainPage::OnStrokeEnded);
}


void PracticalDirectX12_Tutorial1UWP::MainPage::OnStrokeStarted(Windows::UI::Input::Inking::InkStrokeInput ^sender, Windows::UI::Core::PointerEventArgs ^args)
{
	ResetDrawingCanvas();

	if(drawingLineId == 0)
		v1Start = XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);
	else if(drawingLineId == 1)
		v2Start = XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);
}

void PracticalDirectX12_Tutorial1UWP::MainPage::OnStrokeEnded(Windows::UI::Input::Inking::InkStrokeInput ^sender, Windows::UI::Core::PointerEventArgs ^args)
{
	if (drawingLineId == 0){
		v1End = XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

		XMVECTOR v1S = XMLoadFloat2(&v1Start);
		XMVECTOR v1E = XMLoadFloat2(&v1End);
		XMVECTOR v1Diff = v1E - v1S;

		XMStoreFloat2(&v1, v1Diff);

		v1Line->X1 = v1Start.x;
		v1Line->Y1 = v1Start.y;

		v1Line->X2 = v1Start.x + v1.x;
		v1Line->Y2 = v1Start.y + v1.y;

		v1Line->Visibility = Windows::UI::Xaml::Visibility::Visible;

		v1Text->Margin = Windows::UI::Xaml::Thickness(v1Start.x + (v1.x / 2.0f) - 20.0f, v1Start.y + v1.y / 2.0f, 0.0f, 0.0f);
		v1Text->Visibility = Windows::UI::Xaml::Visibility::Visible;
		
		drawingLineId++;
	}
	else if (drawingLineId == 1){
		v2End = XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

		XMVECTOR v2S = XMLoadFloat2(&v2Start);
		XMVECTOR v2E = XMLoadFloat2(&v2End);
		XMVECTOR v2Diff = v2E - v2S;

		XMStoreFloat2(&v2, v2Diff);

		v2Line->X1 = v1End.x;
		v2Line->Y1 = v1End.y;
		
		v2Line->X2 = v1End.x + v2.x;
		v2Line->Y2 = v1End.y + v2.y;

		v2Line->Visibility = Windows::UI::Xaml::Visibility::Visible;


		v2Text->Margin = Windows::UI::Xaml::Thickness(v1End.x + (v2.x / 2.0f) - 20.0f, v1End.y + v2.y / 2.0f, 0.0f, 0.0f);
		v2Text->Visibility = Windows::UI::Xaml::Visibility::Visible;

		DrawResultVector();

		drawingLineId++;
	}
}

void PracticalDirectX12_Tutorial1UWP::MainPage::DrawResultVector()
{
	XMVECTOR xmV1 = XMLoadFloat2(&v1);
	XMVECTOR xmV2 = XMLoadFloat2(&v2);
	XMVECTOR xmV3 = xmV1 + xmV2;

	XMStoreFloat2(&v3, xmV3);

	v3Line->X1 = v1Start.x;
	v3Line->Y1 = v1Start.y;

	v3Line->X2 = v1Start.x + v3.x;
	v3Line->Y2 = v1Start.y + v3.y;
	
	v3Line->Visibility = Windows::UI::Xaml::Visibility::Visible;


	v3Text->Margin = Windows::UI::Xaml::Thickness(v1Start.x + (v3.x / 2.0f) - 20.0f, v1Start.y + v3.y / 2.0f, 0.0f, 0.0f);
	v3Text->Visibility = Windows::UI::Xaml::Visibility::Visible;


	XMVECTOR v2angle = XMLoadFloat2(&v2);
	XMVECTOR v3angle = XMLoadFloat2(&v3);
	XMVECTOR angleBetweenV2andV3 = XMVector2AngleBetweenVectors(v2angle, v3angle);
	float aRad = XMVectorGetX(angleBetweenV2andV3);
	float aDeg = XMConvertToDegrees(aRad);
	CalculationsText->Text = "Angle: " + aDeg.ToString();

	anglePath->Visibility = Windows::UI::Xaml::Visibility::Visible;
	
	PathGeometry^ pg = ref new PathGeometry();
	PathFigure^ pf = ref new PathFigure();
	pf->StartPoint = Point(v2Line->X2 - v3.x / 10.0f, v2Line->Y2 - v3.y / 10.0f);
	
	ArcSegment^ as = ref new ArcSegment();
	as->Size = Size(10, 10);
	as->RotationAngle = 200.0f;

	// This needs to be set based on if our Triangle is drawn clockwise or counterclockwise
	as->SweepDirection = Windows::UI::Xaml::Media::SweepDirection::Counterclockwise; 
	as->Point = Point(v3Line->X2 - v2.x / 10.0f, v3Line->Y2 - v2.y / 10.0f);

	pf->Segments->Append(as);
	pg->Figures->Append(pf);

	anglePath->Data = pg;
}

void PracticalDirectX12_Tutorial1UWP::MainPage::ResetDrawingCanvas()
{
	if (drawingLineId > 1) {
		drawingLineId = 0;
		inkCanvas->InkPresenter->StrokeContainer->Clear();
		anglePath->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		v1Line->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		v2Line->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		v3Line->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		v1Text->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		v2Text->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		v3Text->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
}