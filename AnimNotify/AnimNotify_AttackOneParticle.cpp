// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackOneParticle.h"
#include "Drakan.h"

FString UAnimNotify_AttackOneParticle::GetNotifyName_Implementation() const
{
    return TEXT("AttackOneParticle");
}

void UAnimNotify_AttackOneParticle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    if (IsValid(MeshComp) == false) return;

    ADrakan* Drakan = Cast<ADrakan>(MeshComp->GetOwner());
    if (IsValid(Drakan) == false) return;

    Drakan->PlayAttackOneParticle();
}
