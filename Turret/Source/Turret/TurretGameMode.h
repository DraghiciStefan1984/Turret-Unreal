// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "GameFramework/GameMode.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "TurretGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TURRET_API ATurretGameMode : public AGameMode
{
	GENERATED_BODY()
	float min_interval = .5f;
	float max_interval = 2.0f;
	float time_to_min_interval = 30.0f;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void ChangeScore(int value);
	void ChangeHealth(int value);
	void OnGameOver();
	void OnRestart();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass);

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> enemy_BP;

	float enemyTimer;
	float gameTimer;

protected:
	int health = 100;
	int score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> startingWidgetClass;

	UPROPERTY()
	UUserWidget* currentWidget;
};
