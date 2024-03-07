// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Engine/DataTable.h>
#include <SkillData.generated.h>

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float Cooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float DamageRate;
};
