// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_NextAttack.h"
#include "Gideon.h"

FString UAnimNotify_NextAttack::GetNotifyName_Implementation() const
{
    return TEXT("NextAttack");
}

void UAnimNotify_NextAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    if (IsValid(MeshComp) == false) return;
    
    AGideon* Gideon = Cast<AGideon>(MeshComp->GetOwner());
    if (IsValid(Gideon) == false) return;

    Gideon->NextAttack();
}
