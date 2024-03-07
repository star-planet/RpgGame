// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "Gideon.h"
#include "Drakan.h"
#include "DrakanAIController.h"
#include "DrakanAnimInstance.h"

UBTTask_Attack::UBTTask_Attack()
{
    bNotifyTick = true;
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    ADrakan* Drakan = Cast<ADrakan>(OwnerComp.GetAIOwner()->GetPawn());
    if (IsValid(Drakan) == false) return EBTNodeResult::Failed;

	int64 RandomAttack = FMath::RandRange(0, 3);

	switch (RandomAttack)
	{
	case 0:
		Drakan->SetDamage(1000.0f);
		Drakan->PlayAttackOneMontage();
		break;
	case 1:
		Drakan->SetDamage(800.0f);
		Drakan->PlayAttackTwoMontage();
		break;
	case 2:
		Drakan->SetDamage(950.0f);
		Drakan->PlayAttackThreeMontage();
		break;
	case 3:
		Drakan->SetDamage(700.0f);
		Drakan->PlayAttackFourMontage();
		break;
	default:
		break;
	}

    return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ADrakan* Drakan = Cast<ADrakan>(OwnerComp.GetAIOwner()->GetPawn());
	if (IsValid(Drakan) == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	auto Anim = Cast<UDrakanAnimInstance>(Drakan->GetMesh()->GetAnimInstance());
	if (IsValid(Anim) == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (Anim->Montage_GetIsStopped(Drakan->GetCurrentMontage()))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
