// Fill out your copyright notice in the Description page of Project Settings.


#include "DrakanAnimInstance.h"
#include "Drakan.h"
#include "GameFramework/CharacterMovementComponent.h"

UDrakanAnimInstance::UDrakanAnimInstance() : Speed(0), Hp(0)
{

}

void UDrakanAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Drakan = Cast<ADrakan>(TryGetPawnOwner());
}

void UDrakanAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(Drakan) == false) return;
	Speed = Drakan->GetVelocity().Size2D();
	Hp = Drakan->GetCurrentHp();
}

void UDrakanAnimInstance::AnimNotify_Damage()
{
	Drakan->SendDamage();
}
