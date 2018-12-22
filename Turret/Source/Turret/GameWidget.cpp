// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"

void UGameWidget::Load()
{
	const FName textBlockName = FName(TEXT("ScoreText"));

	if (scoreText == nullptr)
	{
		scoreText = (UTextBlock*)(WidgetTree->FindWidget(textBlockName));
	}
}

void UGameWidget::SetText(int score, int heatlh)
{
	if (scoreText != nullptr)
	{
		scoreText->SetText(FText::FromString(FString(TEXT("Score: ")) + FString::FromInt(score) + FString(TEXT("\nHealth: ")) + FString::FromInt(health)));
	}
}

void UGameWidget::OnGameOver(int score)
{
	if (scoreText != nullptr)
	{
		scoreText->SetText(FText::FromString(FString(TEXT("GameOver!!\nTotal score: ")) + FString::FromInt(score) + FString(TEXT("\nPress R to restart!"))));
	}
}
