// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShatterIslandCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Items/Item.h"
#include "Animation/AnimMontage.h"


// Sets default values
AShatterIslandCharacter::AShatterIslandCharacter()
{; 
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false; 

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);




	CameraBone = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBone->SetupAttachment(GetRootComponent());
	CameraBone->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBone);

}

// Called when the game starts or when spawned
void AShatterIslandCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}
void AShatterIslandCharacter::MoveForward(float value)
{
	if (ActionState == EActionState::ECS_Attacking) return;
	//UE_LOG(LogTemp, Warning, TEXT("VALUE %f"), value); 
	if (Controller && value != 0.f)
	{
		const FRotator controllerrotation =  GetControlRotation();
		const FRotator yawRotation(0.f, controllerrotation.Yaw, 0.f);

		const FVector Direction = 	FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, value); 
	}

}

void AShatterIslandCharacter::MoveRight(float value)
{
	if (ActionState == EActionState::ECS_Attacking) return;
	//UE_LOG(LogTemp, Warning, TEXT("VALUE %f"), value); 
	if (Controller && value != 0.f)
	{
		const FRotator controllerrotation = GetControlRotation();
		const FRotator yawRotation(0.f, controllerrotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}

}

void AShatterIslandCharacter::Turn(float value)
{
	AddControllerYawInput(value);

}

void AShatterIslandCharacter::Look(float value)
{

	AddControllerPitchInput(value);

}

void AShatterIslandCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem); 
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("Right_Hand_Socket")); 
		ChracterState = ECharcterState::ECS_EquippedOneHandedWeapon;
		EquippedWeapon = OverlappingWeapon;
	}
	else
	{
		if (CanDisarm())
		{
			PlayEquipMontage(FName("UnEquip"));
			ChracterState = ECharcterState::ECS_Unequipped;
		}
		else if (CanArm())
		{
			PlayEquipMontage(FName("Equip"));
			ChracterState = ECharcterState::ECS_EquippedOneHandedWeapon;
		}
	}

}


void AShatterIslandCharacter::Attack()
{
	
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::ECS_Attacking;
	}
	

}

bool AShatterIslandCharacter::CanAttack()
{
	return ActionState == EActionState::ECS_Unoccupied 
		&& ChracterState != ECharcterState::ECS_Unequipped;
}

bool AShatterIslandCharacter::CanDisarm()
{
	return ActionState == EActionState::ECS_Unoccupied 
		&& ChracterState != ECharcterState::ECS_Unequipped;
}

bool AShatterIslandCharacter::CanArm()
{
	return ActionState == EActionState::ECS_Unoccupied 
		&& ChracterState == ECharcterState::ECS_Unequipped 
		&& EquippedWeapon;
}



void AShatterIslandCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage && ChracterState == ECharcterState::ECS_EquippedOneHandedWeapon)
	{
		AnimInstance->Montage_Play(AttackMontage, 1.2f);
		const int32 Selection = FMath::RandRange(0, 1);

		FName SectionName = FName();
		switch (Selection)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default:
			break;
		}

		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void AShatterIslandCharacter::PlayEquipMontage(FName SectionName)
{

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage, 1.f);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}





void AShatterIslandCharacter::AttackEnd()
{

	ActionState = EActionState::ECS_Unoccupied;


}





// Called every frame
void AShatterIslandCharacter::Tick(float DeltaTime)
			
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void AShatterIslandCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AShatterIslandCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AShatterIslandCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AShatterIslandCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("Look1"), this, &AShatterIslandCharacter::Look);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this , &AShatterIslandCharacter::Jump);

	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AShatterIslandCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AShatterIslandCharacter::Attack);

}

