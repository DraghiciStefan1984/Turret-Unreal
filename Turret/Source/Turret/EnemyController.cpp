// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TurretGameMode.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootBox = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("Root"));
	rootBox->SetGenerateOverlapEvents(true);
	rootBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::OnOverlap);
	RootComponent = rootBox;
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation();
	newLocation.X += direction.X * speed * DeltaTime;
	newLocation.Y += direction.Y * speed * DeltaTime;
	SetActorLocation(newLocation);
}

void AEnemyController::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains("Projectile"))
	{
		OtherActor->Destroy();
		this->Destroy();
		((ATurretGameMode*)GetWorld()->GetAuthGameMode())->ChangeScore(100);
	}
	else
	{
		this->Destroy();
		((ATurretGameMode*)GetWorld()->GetAuthGameMode())->ChangeHealth(-20);
	}
}

