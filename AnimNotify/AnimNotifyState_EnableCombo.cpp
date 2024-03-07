// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_EnableCombo.h"
#include "Gideon.h"

FString UAnimNotifyState_EnableCombo::GetNotifyName_Implementation() const
{
    return TEXT("EnableCombo");
}

void UAnimNotifyState_EnableCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
    if (IsValid(MeshComp) == false) return;

    AGideon* Gideon = Cast<AGideon>(MeshComp->GetOwner());
    if (IsValid(Gideon) == false) return;

    Gideon->SetIsEnableCombo(true);
}

void UAnimNotifyState_EnableCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);

    if (IsValid(MeshComp) == false) return;

    AGideon* Gideon = Cast<AGideon>(MeshComp->GetOwner());
    if (IsValid(Gideon) == false) return;

    Gideon->SetIsEnableCombo(false);
}
