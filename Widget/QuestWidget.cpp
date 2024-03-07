// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"

UQuestWidget::UQuestWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> QuestAsset(TEXT("Texture2D'/Game/Texture/QuestWindow.QuestWindow'"));
	if (QuestAsset.Succeeded())
	{
		QuestTexture = QuestAsset.Object;
	}
}

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuestBackgrond->SetBrushFromTexture(QuestTexture);

	QuestText->SetText(FText::FromString(TEXT("Enter the Dungeon?")));

	TextInButton->SetText(FText::FromString(TEXT("Yes")));

	if (QuestButton != nullptr)
	{
		QuestButton->OnClicked.AddDynamic(this, &UQuestWidget::OnButtonClicked);
	}
}

void UQuestWidget::OnButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName(*BossMapName));
}