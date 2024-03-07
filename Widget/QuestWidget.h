// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Quest", meta = (BindWidget))
	class UTextBlock* QuestText;

	UPROPERTY(BlueprintReadOnly, Category = "Quest", meta = (BindWidget))
	class UTextBlock* TextInButton;

	UPROPERTY(BlueprintReadOnly, Category = "Quest", meta = (BindWidget))
	class UImage* QuestBackgrond;

	UPROPERTY(BlueprintReadOnly, Category = "Quest", meta = (BindWidget))
	class UButton* QuestButton;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	class UTexture2D* QuestTexture;

public:
	UFUNCTION()
	void OnButtonClicked();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString BossMapName;
};
