// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/AIPerceptionTypes.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "DrakanAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API ADrakanAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADrakanAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UBehaviorTree* BTree;

private:
	UFUNCTION(BlueprintCallable, Category = "Perception")
		void OnTargetDetected(AActor* InActor, FAIStimulus Stimulus);

private:
	class ADrakan* Drakan;
};
