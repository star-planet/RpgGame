// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "QuestWidget.h"
#include "Gideon.h"

// Sets default values
ANpc::ANpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 95.0f);

	// * Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonSerath/Characters/Heroes/Serath/Meshes/Serath.Serath'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	// * Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Blueprint/Npc/ABP_Npc.ABP_Npc_C'"));
	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimAsset.Class);
	}

	// Interface
	static ConstructorHelpers::FClassFinder<UUserWidget> QuestWidgetAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Widget/WB_Quest.WB_Quest_C'"));
	if (QuestWidgetAsset.Succeeded())
	{
		QuestWidgetClass = QuestWidgetAsset.Class;
	}

	// * TriggerVolume
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetCollisionProfileName(TEXT("Npc"));
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->SetBoxExtent(FVector(200.0f, 200.0f, 88.0f));

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ANpc::OnPlayerEnterTriggerVolume);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ANpc::OnPlayerExitTriggerVolume);

	Tags.Add(FName(TEXT("Npc")));
}

// Called when the game starts or when spawned
void ANpc::BeginPlay()
{
	Super::BeginPlay();
	if (QuestWidgetClass != nullptr)
	{
		QuestWidget = CreateWidget<UUserWidget>(GetWorld(), QuestWidgetClass);
		QuestWidget->AddToViewport();
		QuestWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Called every frame
void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANpc::OnPlayerEnterTriggerVolume(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AGideon::StaticClass()))
	{
		QuestWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ANpc::OnPlayerExitTriggerVolume(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	QuestWidget->SetVisibility(ESlateVisibility::Hidden);
}

