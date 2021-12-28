// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DragWidget.h"
#include "Blueprint/UserWidget.h"
#include "MyWindow.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API UMyWindow : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private:
	FVector2D DragOffset;
};



//private:
//UDragWidget* DragWidget;

	