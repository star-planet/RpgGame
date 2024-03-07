// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackFourParticle.h"
#include "Drakan.h"

FString UAnimNotify_AttackFourParticle::GetNotifyName_Implementation() const
{
    return TEXT("AttackFourParticle");
}

void UAnimNotify_AttackFourParticle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    if (IsValid(MeshComp) == false) return;

    ADrakan* Drakan = Cast<ADrakan>(MeshComp->GetOwner());
    if (IsValid(Drakan) == false) return;

    Drakan->PlayAttackFourParticle();
}
