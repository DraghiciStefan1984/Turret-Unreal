// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretGameMode.h"
#include "GameWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

void ATurretGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(startingWidgetClass);
	((UGameWidget*)currentWidget)->Load();
	((UGameWidget*)currentWidget)->SetText(score, health);

	GetWorld()->GetFirstPlayerController()->InputComponent()->BindAction("Restart", IE_Pressed, this, %ATurretGameMode::OnRestart).bExecuteWhenPaused = true;
}

void ATurretGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	gameTimer += DeltaSeconds;
	enemyTimer -= DeltaSeconds;

	if (enemyTimer <= 0.0f)
	{
		float difficultyPercentage = FMath::Min(gameTimer / time_to_min_interval, 1.0f);
		enemyTimer = max_interval - (max_interval - min_interval)*difficultyPercentage;

		UWorld* world = GetWorld();

		if (world)
		{
			float distance = 900.0f;
			float randomAngle = FMath::RandRange(0.0f, 360.0f);
			FVector playerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
			FVector enemyLocation = playerLocation;

			enemyLocation.X += FMath::Cos(randomAngle*3.15f / 180.0f)*distance;
			enemyLocation.Y += FMath::Sin(randomAngle*3.15f / 180.0f)*distance;
			enemyLocation.Z = 220.0f;

			AEnemyController* enemy = world->SpawnActor<AEnemyController>(enemy_BP, enemyLocation, FRotator::ZeroRotator);
			enemy->direction = (playerLocation - enemyLocation).GetSafeNormal();
		}
	}
}

void ATurretGameMode::ChangeScore(int value)
{
	score += value;
	((UGameWidget*)currentWidget)->SetText(score, health);
}

void ATurretGameMode::ChangeHealth(int value)
{
	health += value;
	((UGameWidget*)currentWidget)->SetText(score, health);

	if (health <= 0)
	{
		this->OnGameOver();
	}
}

void ATurretGameMode::OnGameOver()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	((UGameWidget*)currentWidget)->OnGameOver(score);
}

void ATurretGameMode::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ATurretGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass)
{
	if (currentWidget != nullptr)
	{
		currentWidget->RemoveFromViewport();
		currentWidget = nullptr;
	}

	if (newWidgetClass != nullptr)
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), newWidgetClass);

		if (currentWidget != nullptr)
		{
			currentWidget->AddToViewport();
		}
	}
}
