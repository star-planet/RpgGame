// Fill out your copyright notice in the Description page of Project Settings.


#include "BossInterfaceWidget.h"
#include "Drakan.h"
#include "DrakanAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBossInterfaceWidget::NativeConstruct()
{
	Super::NativeConstruct();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADrakanAIController::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0)
    {
        ADrakanAIController* DrakanController = Cast<ADrakanAIController>(FoundActors[0]);
        if (IsValid(DrakanController) == false) return;

        Drakan = Cast<ADrakan>(DrakanController->GetPawn());
        if (IsValid(Drakan) == false) return;

        Drakan->HealthSignature.BindUObject(this, &UBossInterfaceWidget::UpdateHealthWidget);
    }
}

void UBossInterfaceWidget::UpdateHealthWidget()
{
	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	Opts.UseGrouping = false;

	HealthBar->SetPercent(Drakan->GetCurrentHp() / Drakan->GetMaxHp());

	CurrentHp->SetText(FText::AsNumber(Drakan->GetCurrentHp(), &Opts));
	MaxHp->SetText(FText::AsNumber(Drakan->GetMaxHp(), &Opts));
}
