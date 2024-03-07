#include "Gideon.h"
#include "GideonAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "SkillData.h"
#include "PlayerData.h"

AGideon::AGideon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 95.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 640.0f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = 1500.0f;
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	SpringArm->bDoCollisionTest = false;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	// Etc
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Tags.Add(FName(TEXT("Gideon")));

	// Player Data
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerDataAsset(TEXT("DataTable'/Game/Data/DT_Player.DT_Player'"));
	if (PlayerDataAsset.Succeeded())
	{
		PlayerDataTable = PlayerDataAsset.Object;
	}

	// Skill Data
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataAsset(TEXT("DataTable'/Game/Data/DT_Skill.DT_Skill'"));
	if (SkillDataAsset.Succeeded())
	{
		SkillDataTable = SkillDataAsset.Object;
	}
	
	// Main Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshAsset(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Inquisitor/Meshes/Gideon_Inquisitor.Gideon_Inquisitor'"));
	if (MainMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MainMeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	// Berserk Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BerserkMeshAsset(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Mephisto/Meshes/Gideon_Mephisto.Gideon_Mephisto'"));
	if (BerserkMeshAsset.Succeeded())
	{
		BerserkSkeletalMesh = BerserkMeshAsset.Object;
	}

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Blueprint/Gideon/ABP_Gideon.ABP_Gideon_C'"));
	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

	// Dash Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DashMtgAsset(TEXT("AnimMontage'/Game/Blueprint/Gideon/MTG_Dash.MTG_Dash'"));
	if (DashMtgAsset.Succeeded())
	{
		DashMontage = DashMtgAsset.Object;
	}

	// Attack Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMtgAsset(TEXT("AnimMontage'/Game/Blueprint/Gideon/MTG_Attack.MTG_Attack'"));
	if (AttackMtgAsset.Succeeded())
	{
		AttackMontage = AttackMtgAsset.Object;
	}

	// Blackhole Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BlackholeMtgAsset(TEXT("AnimMontage'/Game/Blueprint/Gideon/MTG_Skill_Blackhole.MTG_Skill_Blackhole'"));
	if (BlackholeMtgAsset.Succeeded())
	{
		BlackholeMontage = BlackholeMtgAsset.Object;
	}

	// Blast Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BlastMtgAsset(TEXT("AnimMontage'/Game/Blueprint/Gideon/MTG_Skill_Blast.MTG_Skill_Blast'"));
	if (BlastMtgAsset.Succeeded())
	{
		BlastMontage = BlastMtgAsset.Object;
	}

	// Cast Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CastMtgAsset(TEXT("AnimMontage'/Game/Blueprint/Gideon/MTG_Skill_Cast.MTG_Skill_Cast'"));
	if (CastMtgAsset.Succeeded())
	{
		CastMontage = CastMtgAsset.Object;
	}

	// Cosmic Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CosmicMtgAsset(TEXT("AnimMontage'/Game/Blueprint/Gideon/MTG_Skill_Cosmic.MTG_Skill_Cosmic'"));
	if (CosmicMtgAsset.Succeeded())
	{
		CosmicMontage = CosmicMtgAsset.Object;
	}
	
	// Death Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMtgAsset(TEXT("AnimMontage'/Game/Blueprint/Gideon/MTG_Death.MTG_Death'"));
	if (DeathMtgAsset.Succeeded())
	{
		DeathMontage = DeathMtgAsset.Object;
	}

	// Dash Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DashParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/ProjectileMeteor/FX/P_Gideon_RMB_Portal.P_Gideon_RMB_Portal'"));
	if (DashParticleAsset.Succeeded())
	{
		DashParticle = DashParticleAsset.Object;
	}

	// Blackhole Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BlackholeParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Primary_Cast.P_Primary_Cast'"));
	if (BlackholeParticleAsset.Succeeded())
	{
		BlackholeParticle = BlackholeParticleAsset.Object;
	}

	// Blast Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BlastParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Skins/Undertow/P_Ult_Cast_Undertow.P_Ult_Cast_Undertow'"));
	if (BlastParticleAsset.Succeeded())
	{
		BlastParticle = BlastParticleAsset.Object;
	}

	// Cast Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Meteor/FX/P_Meteor_Cast.P_Meteor_Cast'"));
	if (CastParticleAsset.Succeeded())
	{
		CastParticle = CastParticleAsset.Object;
	}

	// Cosmic Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CosmicParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Ultimate/FX/P_Gideon_Ultimate_Cast.P_Gideon_Ultimate_Cast'"));
	if (CosmicParticleAsset.Succeeded())
	{
		CosmicParticle = CosmicParticleAsset.Object;
	}

	// Berserk Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BerserkParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Burden/FX/P_Gideon_Burden_HitWorld.P_Gideon_Burden_HitWorld'"));
	if (BerserkParticleAsset.Succeeded())
	{
		BerserkParticle = BerserkParticleAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> BerserkEndParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Skins/Undertow/P_Anchor_Ghosts.P_Anchor_Ghosts'"));
	if (BerserkEndParticleAsset.Succeeded())
	{
		BerserkEndParticle = BerserkEndParticleAsset.Object;
	}

	// Hit Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitParticleAsset(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Burden/FX/P_Gideon_Burden_HitCharacter.P_Gideon_Burden_HitCharacter'"));
	if (HitParticleAsset.Succeeded())
	{
		HitParticle = HitParticleAsset.Object;
	}

	// Dash SoundCue
	static ConstructorHelpers::FObjectFinder<USoundCue> DashSoundCueAsset(TEXT("SoundCue'/Game/Audio/Gideon/Cue/DashSound_Cue.DashSound_Cue'"));
	if (DashSoundCueAsset.Succeeded())
	{
		DashSoundCue = DashSoundCueAsset.Object;
	}

	// Berserk SoundCue
	static ConstructorHelpers::FObjectFinder<USoundCue> BerserkSoundCueAsset(TEXT("SoundCue'/Game/Audio/Gideon/Cue/Berserk_Cue.Berserk_Cue'"));
	if (BerserkSoundCueAsset.Succeeded())
	{
		BerserkSoundCue = BerserkSoundCueAsset.Object;
	}

	// Blackhole SoundCue
	static ConstructorHelpers::FObjectFinder<USoundCue> BlackholeSoundCueAsset(TEXT("SoundCue'/Game/Audio/Gideon/Cue/BlackholeSound_Cue.BlackholeSound_Cue'"));
	if (BlackholeSoundCueAsset.Succeeded())
	{
		BlackholeSoundCue = BlackholeSoundCueAsset.Object;
	}

	// Blast SoundCue
	static ConstructorHelpers::FObjectFinder<USoundCue> BlastholeSoundCueAsset(TEXT("SoundCue'/Game/Audio/Gideon/Cue/BlastSound_Cue.BlastSound_Cue'"));
	if (BlastholeSoundCueAsset.Succeeded())
	{
		BlastSoundCue = BlastholeSoundCueAsset.Object;
	}

	// Cosmic SoundCue
	static ConstructorHelpers::FObjectFinder<USoundCue> CosmicSoundCueAsset(TEXT("SoundCue'/Game/Audio/Gideon/Cue/CosmicSound_Cue.CosmicSound_Cue'"));
	if (CosmicSoundCueAsset.Succeeded())
	{
		CosmicSoundCue = CosmicSoundCueAsset.Object;
	}

	// Cast SoundCue
	static ConstructorHelpers::FObjectFinder<USoundCue> CastSoundCueAsset(TEXT("SoundCue'/Game/Audio/Gideon/Cue/CastSound_Cue.CastSound_Cue'"));
	if (CastSoundCueAsset.Succeeded())
	{
		CastSoundCue = CastSoundCueAsset.Object;
	}

}

// Called when the game starts or when spawned
void AGideon::BeginPlay()
{
	Super::BeginPlay();

	SetPlayer();
	SetSkill();
}

void AGideon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HealthSignature.IsBound()) { HealthSignature.Unbind(); }

	if (ManaSignature.IsBound()) { ManaSignature.Unbind(); }

	if (AwakenSignature.IsBound()) { AwakenSignature.Unbind(); }

	if (CooltimeSignature.IsBound()) { CooltimeSignature.Unbind(); }

	if (PotionSignature.IsBound()) { PotionSignature.Unbind(); }
}

// Called every frame
void AGideon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentMp < MaxMp)
	{
		if (!GetWorldTimerManager().IsTimerActive(MpRegenHandle))
		{
			GetWorldTimerManager().SetTimer(MpRegenHandle, this, &AGideon::MpRegen, 2.0f, false);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(MpRegenHandle);
	}

	if (isBlackhole == false)
	{
		if (!GetWorldTimerManager().IsTimerActive(BlackholeCooltimeHandle))
		{
			GetWorldTimerManager().SetTimer(BlackholeCooltimeHandle, this, &AGideon::BlackholeRemainingCooltime, 1.0f, false);
		}
	}

	if (isBlast == false)
	{
		if (!GetWorldTimerManager().IsTimerActive(BlastCooltimeHandle))
		{
			GetWorldTimerManager().SetTimer(BlastCooltimeHandle, this, &AGideon::BlastRemainingCooltime, 1.0f, false);
		}
	}

	if (isCast == false)
	{
		if (!GetWorldTimerManager().IsTimerActive(CastCooltimeHandle))
		{
			GetWorldTimerManager().SetTimer(CastCooltimeHandle, this, &AGideon::CastRemainingCooltime, 1.0f, false);
		}
	}

	if (isCosmic == false)
	{
		if (!GetWorldTimerManager().IsTimerActive(CosmicCooltimeHandle))
		{
			GetWorldTimerManager().SetTimer(CosmicCooltimeHandle, this, &AGideon::CosmicRemainingCooltime, 1.0f, false);
		}
	}
	if (isPotion == false)
	{
		if (!GetWorldTimerManager().IsTimerActive(PotionCooltimeHandle))
		{
			GetWorldTimerManager().SetTimer(PotionCooltimeHandle, this, &AGideon::PotionRemainingCooltime, 1.0f, false);
		}
	}
}

// Called to bind functionality to input
void AGideon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGideon::PlayDashMontage()
{
	PlayAnimMontage(DashMontage, 1.8f, FName(TEXT("Dash")));

	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("spine_01")));
	FRotator ParticleRotation = GetActorRotation();

	ParticleRotation += FRotator(0.0f, 180.0f, 0.0f);

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DashParticle, ParticleTransform, true);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DashSoundCue, ParticleLocation);
}

void AGideon::PlayBlackholeMontage()
{
	isMove = false;
	isCasting = true;

	CurrentMp -= BlackholeMana;
	if (isBerserk) { FinalDamage = Damage * 1.5; }
	else { FinalDamage = Damage; }

	if (ManaSignature.IsBound()) { ManaSignature.Execute(); }

	AscendRegen(10.0f);

	GetCharacterMovement()->StopMovementImmediately();
	PlayAnimMontage(BlackholeMontage, 1.0f, FName(TEXT("Blackhole")));

	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("portal")));
	FRotator ParticleRotation = GetActorRotation();
	FVector NewScale3D = FVector(1.5f, 1.5f, 1.5f);

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation, NewScale3D);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlackholeParticle, ParticleTransform, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), BlackholeSoundCue, ParticleLocation);

}

void AGideon::PlayBlastMontage()
{
	isMove = false;
	isCasting = true;

	CurrentMp -= BlastMana;
	if (isBerserk) { FinalDamage = Damage * 1.5; }
	else { FinalDamage = Damage; }

	if (ManaSignature.IsBound()) { ManaSignature.Execute(); }

	AscendRegen(8.0f);

	GetCharacterMovement()->StopMovementImmediately();
	PlayAnimMontage(BlastMontage, 1.2f, FName(TEXT("Blast")));

	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("root")));
	FRotator ParticleRotation = GetActorRotation();
	FVector NewScale3D = FVector(0.1f, 0.1f, 0.1f);

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation, NewScale3D);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlastParticle, ParticleTransform, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), BlastSoundCue, ParticleLocation, 2.0f, 1.0f, 0.4f);
}

void AGideon::PlayCastMontage()
{
	isMove = false;
	isCasting = true;

	CurrentMp -= CastMana;
	if (isBerserk) { FinalDamage = Damage * 1.5; }
	else { FinalDamage = Damage; }

	if (ManaSignature.IsBound()) { ManaSignature.Execute(); }

	AscendRegen(5.0f);

	GetCharacterMovement()->StopMovementImmediately();
	PlayAnimMontage(CastMontage, 1.0f, FName(TEXT("Cast")));

	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("spine_01")));
	FRotator ParticleRotation = GetActorRotation();
	FVector NewScale3D = FVector(1.5f, 1.5f, 1.5f);

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation, NewScale3D);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CastParticle, ParticleTransform, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), CastSoundCue, ParticleLocation);
}

void AGideon::PlayCosmicMontage()
{
	isMove = false;
	isCasting = true;

	CurrentMp -= CosmicMana;
	if (isBerserk) { FinalDamage = Damage * 1.5; }
	else { FinalDamage = Damage; }

	if (ManaSignature.IsBound()) { ManaSignature.Execute(); }

	AscendRegen(9.0f);

	GetCharacterMovement()->StopMovementImmediately();
	PlayAnimMontage(CosmicMontage, 1.5f, FName(TEXT("Cosmic")));

	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("root")));
	FRotator ParticleRotation = GetActorRotation();
	FVector NewScale3D = FVector(0.1f, 0.1f, 0.1f);

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation, NewScale3D);


	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CosmicParticle, ParticleTransform, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), CosmicSoundCue, ParticleLocation);

}

void AGideon::EndMontage()
{
	isMove = true;
	isCasting = false;
}

void AGideon::ChangeApperance()
{
	isBerserk = true;
	
	CurrentAscend = 0.0f;
	if (AwakenSignature.IsBound()) { AwakenSignature.Execute(); }

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (IsValid(SkeletalMeshComponent) == false) return;
	TempSkeletalMesh = SkeletalMeshComponent->SkeletalMesh;

	SkeletalMeshComponent->SetSkeletalMesh(BerserkSkeletalMesh);

	FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("spine_01")));
	FRotator ParticleRotation = GetActorRotation();

	FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BerserkParticle, ParticleTransform, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), BerserkSoundCue, ParticleLocation);

	GetWorldTimerManager().SetTimer(RestoreTimerHandle, this, &AGideon::RestoreApperance, 10.0f, false);
}

void AGideon::RestoreApperance()
{
	isBerserk = false;

	if (isCasting)
	{
		GetWorldTimerManager().SetTimer(MontageTimerHandle, this, &AGideon::RestoreApperance, 0.1f, false);
	}
	else
	{
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		if (SkeletalMeshComponent && TempSkeletalMesh)
		{
			SkeletalMeshComponent->SetSkeletalMesh(TempSkeletalMesh);
		}

		FVector ParticleLocation = GetMesh()->GetBoneLocation(FName(TEXT("root")));
		FRotator ParticleRotation = GetActorRotation();
		FVector NewScale3D = FVector(0.5f, 0.5f, 0.5f);

		FTransform ParticleTransform = FTransform(ParticleRotation, ParticleLocation, NewScale3D);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BerserkEndParticle, ParticleTransform, true);
	}
}

void AGideon::Attack()
{
	if (isAttack == false)
	{
		PlayAnimMontage(AttackMontage, 1.0f, FName(TEXT("Attack1")));
		FinalDamage = 300.0f;
		isAttack = true;
		isMove = false;
		ComboCount++;
	}
	else if (isEnableCombo)
	{
		isNextAttack = true;
	}
}

void AGideon::NextAttack()
{
	if (isNextAttack == false) return;

	if (ComboCount == 1)
	{
		PlayAnimMontage(AttackMontage, 1.0f, FName(TEXT("Attack2")));
		FinalDamage = 350.0f;
		isNextAttack = false;
		ComboCount++;
	}
	else if(ComboCount == 2)
	{
		PlayAnimMontage(AttackMontage, 1.0f, FName(TEXT("Attack3")));
		FinalDamage = 500.0f;
		isNextAttack = false;
		ComboCount = 0;
	}
}

void AGideon::EndAttack()
{
	isMove = true;
	isAttack = false;
	ComboCount = 0;
}

float AGideon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHp -= DamageAmount;

	if (HealthSignature.IsBound())
	{
		HealthSignature.Execute();
	}

	if (CurrentHp <= 0.0f)
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayAnimMontage(DeathMontage, 1.0f, FName(TEXT("Death")));
	}
	return DamageAmount;
}

void AGideon::MpRegen()
{
	CurrentMp = FMath::Min(CurrentMp + MpRegenRate, MaxMp);
	ManaSignature.ExecuteIfBound();
}

void AGideon::AscendRegen(float AscendRegenRate)
{
	if (isBerserk == false)
	{
		CurrentAscend = FMath::Min(CurrentAscend + AscendRegenRate, MaxAscend);
		AwakenSignature.ExecuteIfBound();
	}
}

void AGideon::HpRegen()
{
	CurrentHp = FMath::Min(CurrentHp + HpRegenRate, MaxHp);
	HealthSignature.ExecuteIfBound();
}

void AGideon::BlackholeRemainingCooltime()
{
	BlackholeCooltime -= 1.0f;
	if (BlackholeCooltime <= 0.0f)
	{
		isBlackhole = true;
		BlackholeCooltime = 8.0f;
		GetWorldTimerManager().ClearTimer(BlackholeCooltimeHandle);
	}
	CooltimeSignature.ExecuteIfBound();
}

void AGideon::BlastRemainingCooltime()
{
	BlastCooltime -= 1.0f;
	if (BlastCooltime <= 0.0f)
	{
		isBlast = true;
		BlastCooltime = 7.0f;
		GetWorldTimerManager().ClearTimer(BlastCooltimeHandle);
	}
	CooltimeSignature.ExecuteIfBound();
}

void AGideon::CastRemainingCooltime()
{
	CastCooltime -= 1.0f;
	if (CastCooltime <= 0.0f)
	{
		isCast = true;
		CastCooltime = 5.0f;
		GetWorldTimerManager().ClearTimer(CastCooltimeHandle);
	}
	CooltimeSignature.ExecuteIfBound();
}

void AGideon::CosmicRemainingCooltime()
{
	CosmicCooltime -= 1.0f;
	if (CosmicCooltime <= 0.0f)
	{
		isCosmic = true;
		CosmicCooltime = 10.0f;
		GetWorldTimerManager().ClearTimer(CosmicCooltimeHandle);
	}
	CooltimeSignature.ExecuteIfBound();
}

void AGideon::PotionRemainingCooltime()
{
	PotionCooltime -= 1.0f;
	if (PotionCooltime <= 0.0f)
	{
		isPotion = true;
		PotionCooltime = 7.0f;
		GetWorldTimerManager().ClearTimer(PotionCooltimeHandle);
	}
	PotionSignature.ExecuteIfBound();
}

void AGideon::SendDamage()
{
	FVector Start, End, Direction;
	Start = GetActorLocation();
	Direction = GetActorForwardVector();
	End = Start + Direction;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> PawnType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	ObjectTypes.Add(PawnType);
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, AttackRadius, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->ActorHasTag(FName(TEXT("Drakan"))))
			{
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), FinalDamage, GetController(), this, UDamageType::StaticClass());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitResult.ImpactPoint, GetActorRotation(), true);
			}
		}
	}
}

void AGideon::SetPlayer()
{	
	auto List = PlayerDataTable->GetRowNames();
	FPlayerData* PlayerData = PlayerDataTable->FindRow<FPlayerData>(List[0], FString(""));

	if (PlayerData != nullptr)
	{
		MaxHp = PlayerData->Hp;
		CurrentHp = MaxHp;
		MaxMp = PlayerData->Mp;
		CurrentMp = MaxMp;
		Damage = PlayerData->Damage;
		MaxAscend = PlayerData->Ascend;
		HpRegenRate = PlayerData->HpRegenRate;
		MpRegenRate = PlayerData->MpRegenRate;
		AttackRadius = PlayerData->AttackRadius;
	}
}

void AGideon::SetSkill()
{
	FSkillData* BlackholeData = SkillDataTable->FindRow<FSkillData>(FName("Blackhole"), FString(""));
	if (BlackholeData != nullptr)
	{
		BlackholeCooltime = BlackholeData->Cooltime;
		BlackholeMana = BlackholeData->Mana;
		Damage = 1000 * BlackholeData->DamageRate;
	}

	FSkillData* BlastData = SkillDataTable->FindRow<FSkillData>(FName("Blast"), FString(""));
	if (BlastData != nullptr)
	{
		BlastCooltime = BlastData->Cooltime;
		BlastMana = BlastData->Mana;
		Damage = 1000 * BlastData->DamageRate;
	}

	FSkillData* CastData = SkillDataTable->FindRow<FSkillData>(FName("Cast"), FString(""));
	if (CastData != nullptr)
	{
		CastCooltime = CastData->Cooltime;
		CastMana = CastData->Mana;
		Damage = 1000 * CastData->DamageRate;
	}

	FSkillData* CosmicData = SkillDataTable->FindRow<FSkillData>(FName("Cosmic"), FString(""));
	if (CosmicData != nullptr)
	{
		CosmicCooltime = CosmicData->Cooltime;
		CosmicMana = CosmicData->Mana;
		Damage = 1000 * CosmicData->DamageRate;
	}

	FSkillData* PotionData = SkillDataTable->FindRow<FSkillData>(FName("Potion"), FString(""));
	if (PotionData != nullptr)
	{
		PotionCooltime = PotionData->Cooltime;
	}
}
