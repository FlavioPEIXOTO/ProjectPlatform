// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachTo(RootComponent);

	isJumping = false;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isJumping) {
		Jump();
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APlayerCharacter::HorizontalMove);
	InputComponent->BindAxis("Vertical", this, &APlayerCharacter::VerticalMove);

	InputComponent->BindAxis("HorizontalCamera", this, &APlayerCharacter::HorizontalCamera);
	InputComponent->BindAxis("VerticalCamera", this, &APlayerCharacter::VerticalCamera);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpMove);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::JumpMove);

}

void APlayerCharacter::HorizontalCamera(float horizontal_camera) {

	if (horizontal_camera) {
		AddActorLocalRotation(FRotator(0, horizontal_camera, 0));
	}
}

void APlayerCharacter::VerticalCamera(float vertical_camera) {

	if (vertical_camera) {
		AddActorLocalRotation(FRotator(0, vertical_camera, 0));
	}
}

void APlayerCharacter::JumpMove() {

	if (isJumping) {
		isJumping = false;
	}
	else {
		isJumping = true;
	}
}

void APlayerCharacter::HorizontalMove(float horizontal_move) {

	if (horizontal_move) {
		AddMovementInput(GetActorRightVector(), horizontal_move);
	}
}

void APlayerCharacter::VerticalMove(float vertical_move) {
	if (vertical_move) {
		AddMovementInput(GetActorForwardVector(), vertical_move);
	}
}

