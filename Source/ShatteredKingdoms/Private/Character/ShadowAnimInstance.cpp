// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShadowAnimInstance.h"
#include "Character/ShatterIslandCharacter.h"
#include "Character/CharacterType.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UShadowAnimInstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();

	ShadowCharacter = 	Cast<AShatterIslandCharacter>(TryGetPawnOwner());
	if (ShadowCharacter)
	{
		ShadowCharacterMovement = ShadowCharacter->GetCharacterMovement();
	}
	
}

void UShadowAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime); 
	if (ShadowCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(ShadowCharacterMovement->Velocity); 
		IsFalling = ShadowCharacterMovement->IsFalling(); 
		CharacterState = ShadowCharacter->GetCharcterState();
	}
}

