// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Engine/DataTable.h>
#include <PlayerData.generated.h>

USTRUCT(BlueprintType)
struct FPlayerData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	float Mp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	float Ascend;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	float HpRegenRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	float MpRegenRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	float AttackRadius;
};
