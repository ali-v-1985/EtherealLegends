// © 2014 - 2016 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "EtherealPlayerMaster.h"

// Sets default values
AEtherealPlayerMaster::AEtherealPlayerMaster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Apprentice/Erika_Archer.Erika_Archer'"));
	//static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Apprentice/Mixamo_Skeleton_Erika_Anim.Mixamo_Skeleton_Erika_Anim'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ExclamationMesh(TEXT("StaticMesh'/Game/EtherealParty/Apprentice/exclamation.exclamation'"));

	SM_Exclamation = ExclamationMesh.Object;

	//GetMesh()->SkeletalMesh = SkeletalMeshObject.Object;
	//GetMesh()->SetAnimInstanceClass(AnimBP.Object->GetAnimBlueprintGeneratedClass());

	// configure the NPC exclamation
	Exclamation = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Exclamation"));
	Exclamation->SetupAttachment(GetMesh());
	Exclamation->StaticMesh = SM_Exclamation;
	Exclamation->SetVisibility(false);
	Exclamation->SetRelativeLocation(FVector(0, 0, 220.0f));
	Exclamation->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	SetupSMComponentsWithCollision(Exclamation);

	// configure the targeting reticle
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 200.0f));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	TargetingReticle->SetVisibility(false);
}

// Called when the game starts or when spawned
void AEtherealPlayerMaster::BeginPlay()
{
	Super::BeginPlay();

	// Gets and stores a reference to the Player State
	EtherealPlayerState = Cast<AEtherealPlayerState>(GetController()->PlayerState);
	EtherealGameInstance = Cast<UEtherealGameInstance>(GetGameInstance());

	if (EtherealPlayerState)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "EtherealPlayerState reference was successfully initialized from code.");
		EtherealPlayerState->Player = this;  // Sets a reference to itself inside the PlayerState
		EtherealPlayerState->Regen();  // start the regen tick
		EtherealPlayerState->Refresh();  // start the refresh tick
	}

	if (EtherealGameInstance)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "EtherealGameInstance reference was successfully initialized from code.");
	}
}

// Stops the player's movement
void AEtherealPlayerMaster::StopMovement()
{
	GetCharacterMovement()->StopMovementImmediately();
	SpeedForward = 0;
	SpeedRight = 0;
}

// Toggle Run State
void AEtherealPlayerMaster::ToggleRunState()
{
	if (IsRunning) // player is currently running, so set to walk speed
	{
		IsRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = 50;
	}
	else // player is currently walking, so set to run speed
	{
		IsRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = 100;
	}
}

// Interact with a NPC
void AEtherealPlayerMaster::Interact()
{
	InteractTarget->Interact();  // Interact with the NPC
	Exclamation->SetVisibility(false); // disables the exclamation notification, because you obviously are aware of the NPC
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None); // disable player movement
	DoInteractAnim = true;  // Play interact animation
}