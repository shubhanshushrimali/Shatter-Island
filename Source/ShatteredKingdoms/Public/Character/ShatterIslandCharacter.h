// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterType.h"
#include "ShatterIslandCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem; 
class UAnimMontage;
class AWeapon;

UCLASS()
class SHATTEREDKINGDOMS_API AShatterIslandCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShatterIslandCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float value);
	void Turn(float value);
	void Look(float value);
	void MoveRight(float value); 
	void EKeyPressed(); 
	void Attack(); 


	
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();


	bool CanAttack();


	bool CanDisarm();
	bool CanArm(); 
	void PlayEquipMontage(FName SectionName);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharcterState GetCharcterState() const { return ChracterState;  }

private:

	ECharcterState  ChracterState = ECharcterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::ECS_Unoccupied;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBone;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem; 

	// Animation Montages 
	UPROPERTY(EditDefaultsOnly , Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon = nullptr;

};
