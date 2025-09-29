// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/ShatterIslandCharacter.h"
#include "CharacterType.h"
#include "ShadowAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHATTEREDKINGDOMS_API UShadowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override; 

	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class AShatterIslandCharacter* ShadowCharacter; 
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UCharacterMovementComponent* ShadowCharacterMovement; 

	UPROPERTY(BlueprintReadOnly, Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float GroundSpeed; 

	UPROPERTY(BlueprintReadOnly, Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	bool IsFalling; 

	UPROPERTY(BlueprintReadOnly, Category = "Movement  ", meta = (AllowPrivateAccess = "true"))
	ECharcterState CharacterState; 
};
