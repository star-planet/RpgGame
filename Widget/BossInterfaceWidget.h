// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossInterfaceWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UBossInterfaceWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Boss", meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "Boss", meta = (BindWidget))
	class UTextBlock* CurrentHp;

	UPROPERTY(BlueprintReadOnly, Category = "Boss", meta = (BindWidget))
	class UTextBlock* MaxHp;

private:
	UPROPERTY()
	class ADrakan* Drakan;

public:
	void UpdateHealthWidget();
	
};
