// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWindow.h"
#include "Blueprint/SlateBlueprintLibrary.h"

FReply UMyWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	
	/*
	FEventReply DetectDragIfPressed_ReturnValue =  UWidgetBlueprintLibrary::DetectDragIfPressed(
		InMouseEvent, this, EKeys::LeftMouseButton);

	return DetectDragIfPressed_ReturnValue.NativeReply; 
	*/

	FEventReply Reply;
	Reply.NativeReply = FReply::Handled();
	
	TSharedPtr<SWidget> SlateWidgetDetectingDrag = this->GetCachedWidget();
	if ( SlateWidgetDetectingDrag.IsValid() )
	{
		Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), EKeys::LeftMouseButton);
	}
	
	return Reply.NativeReply;
}

void UMyWindow::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	//UDragDropOperation* DragDropOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	
	UDragWidget* DragDropOperation = NewObject<class UDragWidget>();
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;
	
	DragDropOperation->WidgetReference = this;
	DragDropOperation->DragOffset = DragOffset;
	
	this->RemoveFromParent();
	
	OutOperation = DragDropOperation;
}
