// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "Gideon.generated.h"

DECLARE_DELEGATE(FHealthSignature)
DECLARE_DELEGATE(FManaSignature)
DECLARE_DELEGATE(FAwakenSignature)
DECLARE_DELEGATE(FCooltimeSignature)
DECLARE_DELEGATE(FPotionSignature)

UCLASS()
class UNREALPORTFOLIO_API AGideon : public ACharacter
{
	GENERATED_BODY()

public:
	AGideon();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* DashMontage;
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* BlackholeMontage;
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* BlastMontage;
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* CastMontage;
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* CosmicMontage;
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* AttackMontage;
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* DeathMontage;


private:
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* DashParticle;
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* BlackholeParticle;
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* BlastParticle;
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* CastParticle;
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* CosmicParticle;
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* BerserkParticle;
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* BerserkEndParticle;
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* HitParticle;

private:
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundCue* DashSoundCue;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundCue* BerserkSoundCue;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundCue* BlackholeSoundCue;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundCue* BlastSoundCue;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundCue* CosmicSoundCue;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundCue* CastSoundCue;

private:
	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool isMove = true;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool isBerserk = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool isCasting = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool isAttack = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool isNextAttack = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int ComboCount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool isEnableCombo = false;

public:
	FORCEINLINE bool GetIsMove() { return isMove; }
	FORCEINLINE bool GetIsBerserk() { return isBerserk; }
	FORCEINLINE bool GetIsCasting() { return isCasting; }
	FORCEINLINE bool GetIsAttack() { return isAttack; }
	FORCEINLINE void SetIsEnableCombo(bool bEnableCombo) { isEnableCombo = bEnableCombo; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	class UDataTable* PlayerDataTable;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float MaxHp;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float CurrentHp;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float MaxMp;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float CurrentMp;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float CurrentAscend;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float MaxAscend;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float HpRegenRate;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float MpRegenRate;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float Damage;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float AttackRadius;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	float FinalDamage;

private:
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	class UDataTable* SkillDataTable;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float BlackholeCooltime;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float BlastCooltime;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float CastCooltime;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float CosmicCooltime;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float PotionCooltime;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float BlackholeMana;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float BlastMana;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float CastMana;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float CosmicMana;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float DamageRate;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	bool isBlackhole = true;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	bool isBlast = true;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	bool isCast = true;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	bool isCosmic = true;

public:
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE float GetMaxHp() { return MaxHp; }
	FORCEINLINE float GetCurrentMp() { return CurrentMp; }
	FORCEINLINE float GetMaxMp() { return MaxMp; }
	FORCEINLINE float GetCurrentAscend() { return CurrentAscend; }
	FORCEINLINE float GetMaxAscend() { return MaxAscend; }

public:
	FORCEINLINE float GetBlackholeMana() { return BlackholeMana; }
	FORCEINLINE float GetBlastMana() { return BlastMana; }
	FORCEINLINE float GetCastMana() { return CastMana; }
	FORCEINLINE float GetCosmicMana() { return CosmicMana; }

public:
	FORCEINLINE float GetBlackholeCooltime() { return BlackholeCooltime; }
	FORCEINLINE float GetBlastCooltime() { return BlastCooltime; }
	FORCEINLINE float GetCastCooltime() { return CastCooltime; }
	FORCEINLINE float GetCosmicCooltime() { return CosmicCooltime; }
	FORCEINLINE float GetPotionCooltime() { return PotionCooltime; }

public:
	FORCEINLINE bool GetIsBlackhole() { return isBlackhole; }
	FORCEINLINE bool GetIsBlast() { return isBlast; }
	FORCEINLINE bool GetIsCast() { return isCast; }
	FORCEINLINE bool GetIsCosmic() { return isCosmic; }

public:
	FORCEINLINE void SetIsBlackhole(bool bEnableBlackhole) { isBlackhole = bEnableBlackhole; }
	FORCEINLINE void SetIsBlast(bool bEnableBlast) { isBlast = bEnableBlast; }
	FORCEINLINE void SetIsCast(bool bEnableCast) { isCast = bEnableCast; }
	FORCEINLINE void SetIsCosmic(bool bEnableCosmic) { isCosmic = bEnableCosmic; }

public:
	void ChangeApperance();
	void RestoreApperance();

	void Attack();
	void NextAttack();
	void EndAttack();
	
	void MpRegen();
	void AscendRegen(float AscendRegenRate);
	void HpRegen();

	void BlackholeRemainingCooltime();
	void BlastRemainingCooltime();
	void CastRemainingCooltime();
	void CosmicRemainingCooltime();
	void PotionRemainingCooltime();

	void PlayDashMontage();
	void PlayBlackholeMontage();
	void PlayBlastMontage();
	void PlayCastMontage();
	void PlayCosmicMontage();
	void EndMontage();

	void SendDamage();
	void SetPlayer();
	void SetSkill();

protected:
	FTimerHandle RestoreTimerHandle;
	FTimerHandle MontageTimerHandle;
	FTimerHandle MpRegenHandle;
	FTimerHandle BlackholeCooltimeHandle;
	FTimerHandle BlastCooltimeHandle;
	FTimerHandle CastCooltimeHandle;
	FTimerHandle CosmicCooltimeHandle;
	FTimerHandle PotionCooltimeHandle;

public:
	FHealthSignature HealthSignature;
	FManaSignature ManaSignature;
	FAwakenSignature AwakenSignature;
	FCooltimeSignature CooltimeSignature;
	FPotionSignature PotionSignature;

private:
	UPROPERTY(VisibleAnywhere, Category = "Character")
	class USkeletalMesh* BerserkSkeletalMesh;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	class USkeletalMesh* TempSkeletalMesh;


private:
	UPROPERTY(VisibleAnywhere, Category = "Potion")
	bool isPotion = true;

public:
	FORCEINLINE bool GetIsPotion() { return isPotion; }
	FORCEINLINE void SetIsPotion(bool bIsPotion) { isPotion = bIsPotion; }
};
