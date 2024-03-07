// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GideonController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGideonController : public APlayerController
{
	GENERATED_BODY()

public:
	AGideonController();

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void GetMouseRightButtonDown();
	UFUNCTION()
	void GetMouseRightButtonUp();
	UFUNCTION()
	void GetMouseLeftButtonDown();
	UFUNCTION()
	void GetSpaceBarDown();
	UFUNCTION()
	void GetQButtonDown();
	UFUNCTION()
	void GetWButtonDown();
	UFUNCTION()
	void GetEButtonDown();
	UFUNCTION()
	void GetRButtonDown();
	UFUNCTION()
	void GetZButtonDown();
	UFUNCTION()
	void GetNumberOneButtonDown();

private:
	void SetDestination(const FVector Destination);
	void MouseToMoveCursor();
	void MouseToRotate();
	void Dash();
	void DashEnd();

private:
	UPROPERTY(VisibleAnywhere, Category = "Move")
	bool isClick;
	UPROPERTY(VisibleAnywhere, Category = "Move")
	bool isDashing;
	UPROPERTY(VisibleAnywhere, Category = "Move")
	bool bCanDash;

private:
	UPROPERTY(VisibleAnywhere, Category = "Dash")
	float DashRate = 4000;
	UPROPERTY(VisibleAnywhere, Category = "Dash")
	float DashCooltime = 5.0f;

private:
	UPROPERTY()
	class AGideon* Gideon;

private:
	FTimerHandle DashTimerHandle;
};
