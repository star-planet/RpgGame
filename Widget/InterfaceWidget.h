// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InterfaceWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UInterfaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInterfaceWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Awaken", meta = (BindWidget))
	class UProgressBar* AwakenBar;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (BindWidget))
	class UTextBlock* CurrentHp;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (BindWidget))
	class UTextBlock* MaxHp;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (BindWidget))
	class UProgressBar* ManaBar;

	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (BindWidget))
	class UTextBlock* CurrentMp;

	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (BindWidget))
	class UTextBlock* MaxMp;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Potion", meta = (BindWidget))
	class UImage* PotionIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Potion", meta = (BindWidget))
	class UTextBlock* PotionText;

	UPROPERTY(BlueprintReadOnly, Category = "Potion")
	class UTexture2D* PotionTexture;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UImage* AwakenIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UImage* BlackholeIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UImage* BlastIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UImage* CastIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UImage* CosmicIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UTextBlock* BlackholeText;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UTextBlock* BlastText;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UTextBlock* CastText;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (BindWidget))
	class UTextBlock* CosmicText;

	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	class UTexture2D* AwakenTexture;

	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	class UTexture2D* BlackholeTexture;

	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	class UTexture2D* BlastTexture;

	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	class UTexture2D* CastTexture;

	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	class UTexture2D* CosmicTexture;

private:
	UPROPERTY()
	class AGideon* Gideon;

public:
	void UpdateAwakenWidget();
	void UpdateManaWidget();
	void UpdatePotionWidget();
	void UpdateSkillWidget();
	void UpdateHealthWidget();
};
