// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EndAttack.h"
#include "Gideon.h"

FString UAnimNotify_EndAttack::GetNotifyName_Implementation() const
{
	return TEXT("EndAttack");
}

void UAnimNotify_EndAttack::Notify(USkeletalMeshComponent* Meshcomp, UAnimSequenceBase* Animation)
{
	Super::Notify(Meshcomp, Animation);
	if (IsValid(Meshcomp) == false) return;

	AGideon* Gideon = Cast<AGideon>(Meshcomp->GetOwner());
	if (IsValid(Gideon) == false) return;

	Gideon->EndAttack();
}
