// Fill out your copyright notice in the Description page of Project Settings.
// Code written by Ralph Warrand (200582)

#include "CPP_ShipMovementComponent.h"
#include "CPP_ShipHull.h"

// Sets default values for this component's properties
UCPP_ShipMovementComponent::UCPP_ShipMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
	// ...
}


// Called when the game starts
void UCPP_ShipMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	shipReference = Cast<ACPP_ShipHull>(GetOwner());
	//actingForces.Add({ 1000.f, 0.f, 0.f });
	//actingForces.Add({ 0.f, 1000.f, 0.f });
	
}


// Called every frame
void UCPP_ShipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (IsValid(shipReference)) {

		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		//TODO: get ship data for variables shipReference->_data

		//mass
		float M = 100.f;

		//separate forces by comp
		float sumOfActingForcesX{};
		float sumOfActingForcesY{};

		actingForces.Add(GetOwner()->GetActorForwardVector() * 10000.f);

		for (int i = 0; i < actingForces.Num(); i++)
		{
			sumOfActingForcesX += actingForces[i].X;
			sumOfActingForcesY += actingForces[i].Y;
			//TODO: add Z implementation
		}
		//ΣF = MA
		FVector ΣF = { sumOfActingForcesX, sumOfActingForcesY, 0.f };
		//∴ A = ΣF/M
		FVector acceleration = ΣF / M;

		//S = ut + (1/2)at^2
		FVector displacement = currentVelocity * DeltaTime + ((1 / 2) * acceleration * DeltaTime * DeltaTime);

		turningForces.Add(FVector4(shipReference->GetActorForwardVector(), 100.f));

		float turningMoment = FVector2D(turningForces[0].X, turningForces[0].Y).Size() * turningForces[0].W;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("turning moment = %f,"), turningMoment));
		FRotator newRot = FRotator(0.f, shipReference->GetActorRotation().Yaw + turningMoment * 0.001f, 0.f);

		shipReference->SetActorLocation(shipReference->GetActorLocation() + displacement);
		shipReference->SetActorRotation(newRot);

		currentVelocity = currentVelocity + acceleration * DeltaTime;

		actingForces.Empty();
		turningForces.Empty();
	}
}

