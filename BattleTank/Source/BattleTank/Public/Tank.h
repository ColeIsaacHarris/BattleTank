// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be at bottom

// Forward Declarations

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
public:

private:	
	// Sets default values for this pawn's properties
	ATank();

	//called on begin play
	virtual void BeginPlay() override;
};
