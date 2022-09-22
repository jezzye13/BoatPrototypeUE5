// Fill out your copyright notice in the Description page of Project Settings.
// Code written by Ralph Warrand (200582)
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_ShipMovementComponent.generated.h"

class ACPP_ShipHull;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPP_ShipMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_ShipMovementComponent();

	UPROPERTY(EditAnywhere)
		TArray<FVector> actingForces;

	UPROPERTY(EditAnywhere)
		TArray<FVector4> turningForces;

	UPROPERTY(EditDefaultsOnly)
		ACPP_ShipHull* shipReference;

	UPROPERTY(EditAnywhere)
		FVector currentVelocity {};

	UPROPERTY(EditAnywhere)
		FVector currentWindForward {};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
