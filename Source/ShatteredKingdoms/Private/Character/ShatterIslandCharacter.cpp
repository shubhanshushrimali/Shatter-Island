// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShatterIslandCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Items/Item.h"

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
	}
	

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

}

