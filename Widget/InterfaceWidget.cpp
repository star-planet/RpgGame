// Fill out your copyright notice in the Description page of Project Settings.


#include "InterfaceWidget.h"
#include "Gideon.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

UInterfaceWidget::UInterfaceWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// * Potion
	static ConstructorHelpers::FObjectFinder<UTexture2D> PotionAsset(TEXT("Texture2D'/Game/Texture/HealthPotion.HealthPotion'"));
	if (PotionAsset.Succeeded())
	{
		PotionTexture = PotionAsset.Object;
	}

	// * Skill
	static ConstructorHelpers::FObjectFinder<UTexture2D> AwakenAsset(TEXT("Texture2D'/Game/Texture/Awaken.Awaken'"));
	if (AwakenAsset.Succeeded())
	{
		AwakenTexture = AwakenAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> BlackholeAsset(TEXT("Texture2D'/Game/Texture/Blackhole.Blackhole'"));
	if (BlackholeAsset.Succeeded())
	{
		BlackholeTexture = BlackholeAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> BlastAsset(TEXT("Texture2D'/Game/Texture/Blast.Blast'"));
	if (BlastAsset.Succeeded())
	{
		BlastTexture = BlastAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> CastAsset(TEXT("Texture2D'/Game/Texture/Cast.Cast'"));
	if (CastAsset.Succeeded())
	{
		CastTexture = CastAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> CosmicAsset(TEXT("Texture2D'/Game/Texture/Cosmic.Cosmic'"));
	if (CosmicAsset.Succeeded())
	{
		CosmicTexture = CosmicAsset.Object;
	}
}

void UInterfaceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Gideon = Cast<AGideon>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Gideon) == false) return;

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	Opts.UseGrouping = false;

	// * AwakenBar
	Gideon->AwakenSignature.BindUObject(this, &UInterfaceWidget::UpdateAwakenWidget);

	// * HealthBar
	Gideon->HealthSignature.BindUObject(this, &UInterfaceWidget::UpdateHealthWidget);

	// * ManaBar
	Gideon->ManaSignature.BindUObject(this, &UInterfaceWidget::UpdateManaWidget);

	// * Potion
	Gideon->PotionSignature.BindUObject(this, &UInterfaceWidget::UpdatePotionWidget);
	PotionIcon->SetBrushFromTexture(PotionTexture);
	PotionIcon->SetBrushSize(FVector2D(70, 70));


	PotionText->SetText(FText::AsNumber(Gideon->GetPotionCooltime(), &Opts));
	PotionText->SetVisibility(ESlateVisibility::Hidden);

	// * Skill
	Gideon->CooltimeSignature.BindUObject(this, &UInterfaceWidget::UpdateSkillWidget);

	AwakenIcon->SetBrushFromTexture(AwakenTexture);
	AwakenIcon->SetBrushSize(FVector2D(70, 70));
	AwakenIcon->SetOpacity(0.5f);

	BlackholeIcon->SetBrushFromTexture(BlackholeTexture);
	BlackholeIcon->SetBrushSize(FVector2D(70, 70));

	BlastIcon->SetBrushFromTexture(BlastTexture);
	BlastIcon->SetBrushSize(FVector2D(70, 70));

	CastIcon->SetBrushFromTexture(CastTexture);
	CastIcon->SetBrushSize(FVector2D(70, 70));

	CosmicIcon->SetBrushFromTexture(CosmicTexture);
	CosmicIcon->SetBrushSize(FVector2D(70, 70));

	BlackholeText->SetText(FText::AsNumber(Gideon->GetBlackholeCooltime(), &Opts));
	BlackholeText->SetVisibility(ESlateVisibility::Hidden);

	BlastText->SetText(FText::AsNumber(Gideon->GetBlastCooltime(), &Opts));
	BlastText->SetVisibility(ESlateVisibility::Hidden);

	CastText->SetText(FText::AsNumber(Gideon->GetCastCooltime(), &Opts));
	CastText->SetVisibility(ESlateVisibility::Hidden);

	CosmicText->SetText(FText::AsNumber(Gideon->GetCastCooltime(), &Opts));
	CosmicText->SetVisibility(ESlateVisibility::Hidden);

}

void UInterfaceWidget::UpdateAwakenWidget()
{
	AwakenBar->SetPercent(Gideon->GetCurrentAscend() / Gideon->GetMaxAscend());
}

void UInterfaceWidget::UpdateManaWidget()
{
	ManaBar->SetPercent(Gideon->GetCurrentMp() / Gideon->GetMaxMp());

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	Opts.UseGrouping = false;

	CurrentMp->SetText(FText::AsNumber(Gideon->GetCurrentMp(), &Opts));
	MaxMp->SetText(FText::AsNumber(Gideon->GetMaxMp(), &Opts));
}

void UInterfaceWidget::UpdatePotionWidget()
{
	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	Opts.UseGrouping = false;

	if (Gideon->GetIsPotion() == false)
	{
		PotionIcon->SetOpacity(0.5f);
		PotionText->SetVisibility(ESlateVisibility::Visible);
		PotionText->SetText(FText::AsNumber(Gideon->GetPotionCooltime(), &Opts));
	}
	else
	{
		PotionIcon->SetOpacity(1.0f);
		PotionText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInterfaceWidget::UpdateSkillWidget()
{
	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	Opts.UseGrouping = false;

	if (Gideon->GetCurrentAscend() == Gideon->GetMaxAscend())
	{
		AwakenIcon->SetOpacity(1.0f);
	}
	else
	{
		AwakenIcon->SetOpacity(0.5f);
	}

	if (Gideon->GetIsBlackhole() == false)
	{
		BlackholeIcon->SetOpacity(0.5f);
		BlackholeText->SetVisibility(ESlateVisibility::Visible);
		BlackholeText->SetText(FText::AsNumber(Gideon->GetBlackholeCooltime(), &Opts));
	}
	else
	{
		BlackholeIcon->SetOpacity(1.0f);
		BlackholeText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Gideon->GetIsBlast() == false)
	{
		BlastIcon->SetOpacity(0.5f);
		BlastText->SetVisibility(ESlateVisibility::Visible);
		BlastText->SetText(FText::AsNumber(Gideon->GetBlastCooltime(), &Opts));
	}
	else
	{
		BlastIcon->SetOpacity(1.0f);
		BlastText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Gideon->GetIsCast() == false)
	{
		CastIcon->SetOpacity(0.5f);
		CastText->SetVisibility(ESlateVisibility::Visible);
		CastText->SetText(FText::AsNumber(Gideon->GetCastCooltime(), &Opts));
	}
	else
	{
		CastIcon->SetOpacity(1.0f);
		CastText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Gideon->GetIsCosmic() == false)
	{
		CosmicIcon->SetOpacity(0.5f);
		CosmicText->SetVisibility(ESlateVisibility::Visible);
		CosmicText->SetText(FText::AsNumber(Gideon->GetCosmicCooltime(), &Opts));
	}
	else
	{
		CosmicIcon->SetOpacity(1.0f);
		CosmicText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInterfaceWidget::UpdateHealthWidget()
{
	HealthBar->SetPercent(Gideon->GetCurrentHp() / Gideon->GetMaxHp());

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	Opts.UseGrouping = false;

	CurrentHp->SetText(FText::AsNumber(Gideon->GetCurrentHp(), &Opts));
	MaxHp->SetText(FText::AsNumber(Gideon->GetMaxHp(), &Opts));
}
