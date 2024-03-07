// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackThreeParticle.h"
#include "Drakan.h"

FString UAnimNotify_AttackThreeParticle::GetNotifyName_Implementation() const
{
    return TEXT("AttackThreeParticle");
}

void UAnimNotify_AttackThreeParticle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    if (IsValid(MeshComp) == false) return;

    ADrakan* Drakan = Cast<ADrakan>(MeshComp->GetOwner());
    if (IsValid(Drakan) == false) return;

    Drakan->PlayAttackThreeParticle();
}