// Fill out your copyright notice in the Description page of Project Settings.


#include "GideonAnimInstance.h"
#include "Gideon.h"
#include "GameFramework/CharacterMovementComponent.h"

UGideonAnimInstance::UGideonAnimInstance() : Speed(0), Gideon(nullptr)
{

}

void UGideonAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Gideon = Cast<AGideon>(TryGetPawnOwner());
}

void UGideonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(Gideon) == false) return;
	Speed = Gideon->GetVelocity().Size2D();
}

void UGideonAnimInstance::AnimNotify_Damage()
{
	Gideon->SendDamage();
}
