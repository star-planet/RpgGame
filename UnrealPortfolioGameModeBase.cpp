// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealPortfolioGameModeBase.h"
#include "Gideon.h"
#include "GideonController.h"
#include "Blueprint/UserWidget.h"

AUnrealPortfolioGameModeBase::AUnrealPortfolioGameModeBase()
{
	DefaultPawnClass = AGideon::StaticClass();
	PlayerControllerClass = AGideonController::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> InterfaceWidgetAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Widget/WB_Interface.WB_Interface_C'"));
	if (InterfaceWidgetAsset.Succeeded())
	{
		InterfaceWidgetClass = InterfaceWidgetAsset.Class;
	}
}

void AUnrealPortfolioGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (InterfaceWidgetClass != nullptr)
	{
		CreateWidget<UUserWidget>(GetWorld(), InterfaceWidgetClass)->AddToViewport();
	}
}