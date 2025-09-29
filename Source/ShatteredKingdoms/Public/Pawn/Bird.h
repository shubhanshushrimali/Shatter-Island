// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent; 
class UCameraComponent; 



UCLASS()
class SHATTEREDKINGDOMS_API ABird : public APawn
{
	GENERATED_BODY()

public:

	ABird();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;
	void MoveForward(float value);
	void Turn(float value);
	void Look(float value);

private:
	UPROPERTY(VisibleAnywhere)
   UCapsuleComponent* capsule; 

	UPROPERTY(VisibleAnywhere)
   USkeletalMeshComponent* BirdMesh;

   UPROPERTY(VisibleAnywhere)
   USpringArmComponent* CameraBone;

   UPROPERTY(VisibleAnywhere)
   UCameraComponent* ViewCamera; 

};
