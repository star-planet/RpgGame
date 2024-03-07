// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EndMontage.h"
#include "Gideon.h"

FString UAnimNotify_EndMontage::GetNotifyName_Implementation() const
{
	return TEXT("EndMontage");
}

void UAnimNotify_EndMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (IsValid(MeshComp) == false) return;
	AGideon* Gideon = Cast<AGideon>(MeshComp->GetOwner());
	if (IsValid(Gideon) == false) return;
	Gideon->EndMontage();
}
