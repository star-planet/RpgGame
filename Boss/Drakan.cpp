// Fill out your copyright notice in the Description page of Project Settings.


#include "Drakan.h"
#include "DrakanAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Gideon.h"
#include "BossInterfaceWidget.h"
#include "Sound/SoundCue.h"

// Sets default values
ADrakan::ADrakan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(88.0f, 200.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Boss"));

	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Drakan/Mon_BlackDragon31_Skeleton.Mon_BlackDragon31_Skeleton'"));;
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -200.0f));
		GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	}

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Blueprint/Drakan/ABP_Drakan.ABP_Drakan_C'"));
	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimAsset.Class);
	}

	// Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackOneAsset(TEXT("AnimMontage'/Game/Blueprint/Drakan/MTG_Attack1.MTG_Attack1'"));
	if (AttackOneAsset.Succeeded())
	{
		AttackOneMontage = AttackOneAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackTwoAsset(TEXT("AnimMontage'/Game/Blueprint/Drakan/MTG_Attack2.MTG_Attack2'"));
	if (AttackTwoAsset.Succeeded())
	{
		AttackTwoMontage = AttackTwoAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackThreeAsset(TEXT("AnimMontage'/Game/Blueprint/Drakan/MTG_Attack3.MTG_Attack3'"));
	if (AttackThreeAsset.Succeeded())
	{
		AttackThreeMontage = AttackThreeAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackFourAsset(TEXT("AnimMontage'/Game/Blueprint/Drakan/MTG_Attack4.MTG_Attack4'"));
	if (AttackFourAsset.Succeeded())
	{
		AttackFourMontage = AttackFourAsset.Object;
	}

	// Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackOneParticleAsset(TEXT("ParticleSystem'/Game/ParagonSerath/FX/Particles/Abilities/Ascend/FX/P_Ascend_Hit_Evil.P_Ascend_Hit_Evil'"));
	if (AttackOneParticleAsset.Succeeded())
	{
		AttackOneParticle = AttackOneParticleAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackTwoParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Burden/FX/P_Gideon_Burden_HitCharacter.P_Gideon_Burden_HitCharacter'"));
	if (AttackTwoParticleAsset.Succeeded())
	{
		AttackTwoParticle = AttackTwoParticleAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackThreeParticleAsset(TEXT("ParticleSystem'/Game/ParagonSerath/FX/Particles/Abilities/Chastise/FX/P_WingBlastFallen.P_WingBlastFallen'"));
	if (AttackThreeParticleAsset.Succeeded())
	{
		AttackThreeParticle = AttackThreeParticleAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackFourParticleAsset(TEXT("ParticleSystem'/Game/ParagonSerath/FX/Particles/Abilities/Ultimate/FX/P_Burning.P_Burning'"));
	if (AttackFourParticleAsset.Succeeded())
	{
		AttackFourParticle = AttackFourParticleAsset.Object;
	}

	// Interface
	static ConstructorHelpers::FClassFinder<UUserWidget> BossWidgetAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Widget/WB_BossInterface.WB_BossInterface_C'"));
	if (BossWidgetAsset.Succeeded())
	{
		BossWidgetClass = BossWidgetAsset.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> BackgrondSoundAsset(TEXT("SoundCue'/Game/Audio/Gideon/Cue/BackgrondBGM_Cue.BackgrondBGM_Cue'"));
	if (BackgrondSoundAsset.Succeeded())
	{
		BackgrondSoundCue = BackgrondSoundAsset.Object;
	}

	// Etc
	AIControllerClass = ADrakanAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Tags.Add(FName(TEXT("Drakan")));

}

// Called when the game starts or when spawned
void ADrakan::BeginPlay()
{
	Super::BeginPlay();

	if (BossWidgetClass != nullptr)
	{
		CreateWidget<UUserWidget>(GetWorld(), BossWidgetClass)->AddToViewport();
	}
	UGameplayStatics::PlaySound2D(GetWorld(), BackgrondSoundCue);
}

void ADrakan::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (HealthSignature.IsBound())
	{
		HealthSignature.Unbind();
	}
}

float ADrakan::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHp = FMath::Max(CurrentHp -= DamageAmount, 0.0f);

	HealthSignature.ExecuteIfBound();

	if (CurrentHp <= 0)
	{
		this->Destroy();
	}
	return DamageAmount;
}

// Called every frame
void ADrakan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ADrakan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADrakan::SendDamage()
{
	FVector Start, End, Direction;
	Start = GetActorLocation();
	Direction = GetActorForwardVector();
	End = Start + (Direction * AttackRange);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> PawnType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	ObjectTypes.Add(PawnType);
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, AttackRadius, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->ActorHasTag(FName(TEXT("Gideon"))))
			{
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, GetController(), this, UDamageType::StaticClass());
			}
		}
	}
}

void ADrakan::PlayAttackOneMontage()
{
	PlayAnimMontage(AttackOneMontage);
}

void ADrakan::PlayAttackTwoMontage()
{
	PlayAnimMontage(AttackTwoMontage);
}

void ADrakan::PlayAttackThreeMontage()
{
	PlayAnimMontage(AttackThreeMontage);
}

void ADrakan::PlayAttackFourMontage()
{
	PlayAnimMontage(AttackFourMontage);
}

void ADrakan::PlayAttackOneParticle()
{
	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("Hand_R")));
	FRotator ParticleRotation = GetActorRotation();

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackOneParticle, ParticleTransform, true);
}

void ADrakan::PlayAttackTwoParticle()
{
	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("ball_l")));
	FRotator ParticleRotation = GetActorRotation();

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackTwoParticle, ParticleTransform, true);
}

void ADrakan::PlayAttackThreeParticle()
{
	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("Wing_L06")));
	FRotator ParticleRotation = GetActorRotation();

	FVector NewScale3D = FVector(1.5f, 1.5f, 1.5f);
	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation, NewScale3D);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackThreeParticle, ParticleTransform, true);
}

void ADrakan::PlayAttackFourParticle()
{
	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("ball_r")));
	FRotator ParticleRotation = GetActorRotation();

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackFourParticle, ParticleTransform, true);
}