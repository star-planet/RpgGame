// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Drakan.generated.h"

DECLARE_DELEGATE(FHealthSignature)

UCLASS()
class UNREALPORTFOLIO_API ADrakan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrakan();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	float Damage;

	UPROPERTY(VisibleAnywhere, Category = "State")
	float CurrentHp = 50000.0f;

	UPROPERTY(VisibleAnywhere, Category = "State")
	float MaxHp = 50000.0f;

	UPROPERTY(VisibleAnywhere, Category = "State")
	float AttackRange = 400.0f;

	UPROPERTY(VisibleAnywhere, Category = "State")
	float AttackRadius = 250.0f;

public:
	void SendDamage();

public:
	FORCEINLINE void SetDamage(float DamageAmount) { Damage = DamageAmount; }

private:
	UPROPERTY()
	class AGideon* Gideon;

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> BossWidgetClass;

public:
	FHealthSignature HealthSignature;

public:
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE float GetMaxHp() { return MaxHp; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* AttackOneParticle;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* AttackTwoParticle;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* AttackThreeParticle;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	class UParticleSystem* AttackFourParticle;

private:
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* AttackOneMontage;

	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* AttackTwoMontage;

	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* AttackThreeMontage;

	UPROPERTY(VisibleAnywhere, Category = "Montage")
	class UAnimMontage* AttackFourMontage;

public:
	void PlayAttackOneMontage();
	void PlayAttackTwoMontage();
	void PlayAttackThreeMontage();
	void PlayAttackFourMontage();

public:
	void PlayAttackOneParticle();
	void PlayAttackTwoParticle();
	void PlayAttackThreeParticle();
	void PlayAttackFourParticle();

private:
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundCue* BackgrondSoundCue;
};
