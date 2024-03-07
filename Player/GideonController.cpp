// Fill out your copyright notice in the Description page of Project Settings.


#include "GideonController.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Gideon.h"

AGideonController::AGideonController()
{
	bShowMouseCursor = true;
}

void AGideonController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (isClick && Gideon->GetIsMove() && Gideon->GetIsAttack() == false) 
	{ 
		MouseToMoveCursor(); 
	}

	if (isDashing == false && bCanDash && Gideon->GetIsMove()) 
	{ 
		Dash(); 
	}
}

void AGideonController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Click"), IE_Pressed, this, &AGideonController::GetMouseRightButtonDown);
	InputComponent->BindAction(TEXT("Click"), IE_Released, this, &AGideonController::GetMouseRightButtonUp);
	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AGideonController::GetMouseLeftButtonDown);
	InputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &AGideonController::GetSpaceBarDown);
	InputComponent->BindAction(TEXT("Skill1"), IE_Pressed, this, &AGideonController::GetQButtonDown);
	InputComponent->BindAction(TEXT("Skill2"), IE_Pressed, this, &AGideonController::GetWButtonDown);
	InputComponent->BindAction(TEXT("Skill3"), IE_Pressed, this, &AGideonController::GetEButtonDown);
	InputComponent->BindAction(TEXT("Skill4"), IE_Pressed, this, &AGideonController::GetRButtonDown);
	InputComponent->BindAction(TEXT("Berserk"), IE_Pressed, this, &AGideonController::GetZButtonDown);
	InputComponent->BindAction(TEXT("Potion"), IE_Pressed, this, &AGideonController::GetNumberOneButtonDown);
}

void AGideonController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(InPawn) == false) return;
	Gideon = Cast<AGideon>(InPawn);
}

void AGideonController::GetMouseRightButtonDown()
{
	isClick = true;
}

void AGideonController::GetMouseRightButtonUp()
{
	isClick = false;
}

void AGideonController::GetSpaceBarDown()
{
	if(isDashing == false && Gideon->GetIsMove()) 
	{ 
		bCanDash = true;
	}
}

void AGideonController::GetQButtonDown()
{
	if(Gideon->GetIsCasting() == false && Gideon->GetCurrentMp() >= Gideon->GetBlackholeMana() && Gideon->GetIsBlackhole() && Gideon->GetIsAttack() == false) 
	{ 
		Gideon->SetIsBlackhole(false);
		MouseToRotate();
		Gideon->PlayBlackholeMontage();
	}
}

void AGideonController::GetWButtonDown()
{
	if (Gideon->GetIsCasting() == false && Gideon->GetCurrentMp() >= Gideon->GetBlastMana() && Gideon->GetIsBlast() && Gideon->GetIsAttack() == false)
	{ 
		Gideon->SetIsBlast(false);
		MouseToRotate();
		Gideon->PlayBlastMontage();
	}
}

void AGideonController::GetEButtonDown()
{
	if (Gideon->GetIsCasting() == false && Gideon->GetCurrentMp() >= Gideon->GetCastMana() && Gideon->GetIsCast() && Gideon->GetIsAttack() == false)
	{ 
		Gideon->SetIsCast(false);
		MouseToRotate();
		Gideon->PlayCastMontage(); 
	}
}

void AGideonController::GetRButtonDown()
{
	if (Gideon->GetIsCasting() == false && Gideon->GetCurrentMp() >= Gideon->GetCosmicMana() && Gideon->GetIsCosmic() && Gideon->GetIsAttack() == false)
	{ 
		Gideon->SetIsCosmic(false);
		MouseToRotate();
		Gideon->PlayCosmicMontage(); 
	}
}

void AGideonController::GetZButtonDown()
{
	if(Gideon->GetIsBerserk() == false && Gideon->GetIsCasting() == false && Gideon->GetCurrentAscend() >= Gideon->GetMaxAscend() && Gideon->GetIsMove())
	{ 
		Gideon->ChangeApperance(); 
	}
}

void AGideonController::GetNumberOneButtonDown()
{
	if (Gideon->GetIsPotion() && Gideon->GetCurrentHp() < Gideon->GetMaxHp())
	{
		Gideon->SetIsPotion(false);
		Gideon->HpRegen();
	}
}

void AGideonController::GetMouseLeftButtonDown()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Gideon->GetActorLocation());
	if (Gideon->GetIsCasting() == false)
	{
		if (Gideon->GetIsAttack() == false)
		{
			MouseToRotate();
		}
		Gideon->Attack();
	}
}

void AGideonController::Dash()
{
	bCanDash = false;
	isDashing = true;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Gideon->GetActorLocation());

	MouseToRotate();

	FVector DashDirection = Gideon->GetActorForwardVector();
	FVector DashDistance = DashDirection * DashRate;

	Gideon->LaunchCharacter(DashDistance, true, false);
	Gideon->PlayDashMontage();

	GetWorldTimerManager().SetTimer(DashTimerHandle, this, &AGideonController::DashEnd, DashCooltime, false);
}

void AGideonController::DashEnd()
{
	isDashing = false;
	GetWorldTimerManager().ClearTimer(DashTimerHandle);
}


void AGideonController::SetDestination(const FVector Destination)
{
	ACharacter* const MyPlayer = Cast<ACharacter>(GetPawn());
	if (IsValid(MyPlayer) == false) return;

	float const Distance = FVector::Dist(Destination, MyPlayer->GetActorLocation());

	if (Distance > 100.0f)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	}
}

void AGideonController::MouseToMoveCursor()
{
	FHitResult HitResult;

	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		SetDestination(HitResult.ImpactPoint);
	}
}

void AGideonController::MouseToRotate()
{
	FHitResult HitResult;

	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		FVector MouseLocation = HitResult.ImpactPoint;
		FVector PlayerLocation = Gideon->GetActorLocation();

		FVector LookDirection = FVector(MouseLocation.X, MouseLocation.Y, PlayerLocation.Z) - PlayerLocation;
		FRotator NewRotation = LookDirection.Rotation();

		NewRotation.Pitch = 0.0f;
		NewRotation.Roll = 0.0f;

		Gideon->SetActorRotation(NewRotation);
	}
}
