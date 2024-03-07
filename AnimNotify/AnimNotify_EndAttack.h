// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UAnimNotify_EndAttack : public UAnimNotify
{
	GENERATED_BODY()
	
	FString GetNotifyName_Implementation() const;

	virtual void Notify(class USkeletalMeshComponent* Meshcomp, class UAnimSequenceBase* Animation);
	
};
