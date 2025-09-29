	// Fill out your copyright notice in the Description page of Project Settings.
    #include "Pawn/Bird.h"
	#include "Components/CapsuleComponent.h"
	#include "Components/SkeletalMeshComponent.h"
	#include "GameFramework/SpringArmComponent.h"
	#include "Camera/CameraComponent.h"




	ABird::ABird()
	{
 
		PrimaryActorTick.bCanEverTick = true;

		capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
		capsule->SetCapsuleHalfHeight(20.f); 
		capsule->SetCapsuleRadius(15.f); 
		SetRootComponent(capsule); 

		BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
		BirdMesh->SetupAttachment(GetRootComponent()); 

		CameraBone = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		CameraBone->SetupAttachment(capsule);
		CameraBone->TargetArmLength = 300.f;

		ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
		ViewCamera->SetupAttachment(CameraBone); 



		AutoPossessPlayer = EAutoReceiveInput::Player0;
	}


	void ABird::BeginPlay()
	{
		Super::BeginPlay();
	
	}

	void ABird::MoveForward(float value)
	{
		//UE_LOG(LogTemp, Warning, TEXT("VALUE %f"), value); 
		if (Controller && value != 0)
		{
			FVector Forward = GetActorForwardVector();
			AddMovementInput(Forward, value); 
		}

	}

	void ABird::Turn(float value)
	{
		AddControllerYawInput(value);

	}

	void ABird::Look(float value)
	{

		AddControllerPitchInput(value); 

	}

	void ABird::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

	}

	// Called to bind functionality to input
	void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		PlayerInputComponent->BindAxis(FName("MoveForward"), this , &ABird::MoveForward);
		PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::Turn);
		PlayerInputComponent->BindAxis(FName("Look1"), this, &ABird::Look); 

	}

