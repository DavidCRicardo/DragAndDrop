// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWindow.h"
#include "Blueprint/SlateBlueprintLibrary.h"

FReply UMyWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	/*FEventReply ReplyResult =
		UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return ReplyResult.NativeReply;*/

	return CustomDetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
}

void UMyWindow::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragWidget* DragDropOperation = NewObject<UDragWidget>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);
	
	DragDropOperation->WidgetReference = this;
	DragDropOperation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());;

	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;
	
	OutOperation = DragDropOperation;
}

void UMyWindow::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	RemoveFromParent();
}

FReply UMyWindow::CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey)
{
	if ( InMouseEvent.GetEffectingButton() == DragKey /*|| PointerEvent.IsTouchEvent()*/ )
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();
		
		if ( WidgetDetectingDrag )
		{
			TSharedPtr<SWidget> SlateWidgetDetectingDrag = WidgetDetectingDrag->GetCachedWidget();
			if ( SlateWidgetDetectingDrag.IsValid() )
			{
				Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), DragKey);
				return Reply.NativeReply;
			}
		}
	}

	return FReply::Unhandled();
}

