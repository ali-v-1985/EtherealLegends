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
#include "IronSword.h"

// Sets default values
AIronSword::AIronSword(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/VFX/sphere_skeletal.sphere_skeletal'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Elemental/Environment/Throne_Warspoils/Mesh/IronSword.IronSword'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_IronSword.WeaponIcon_IronSword'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_IronSword-small.WeaponIcon_IronSword-small'"));


	// Set Default Objects

	Name = EMasterGearList::GL_IronSword;
	Type = EMasterGearTypes::GT_OneHanded;
	Description = "A simple sword made of strong iron.";
	MPCost = 0.0f;
	ATK = 5.0f;
	DEF = 5.0f;
	SPD = 0.0f;
	HP = 50.0f;
	MP = 5.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponSkeletalMesh->SetHiddenInGame(true);
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponStaticMesh->SetWorldScale3D(FVector(2, 2, 2));  // scale correction
	WeaponStaticMesh->SetRelativeLocation(FVector(0, 0, 45));  // location correction
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);
	WeaponOffhandMesh->SetHiddenInGame(true);
	
	SwordCollider->SetBoxExtent(FVector(5.0f, 5.0f, 25.0f));
	SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
}

// Called when the game starts or when spawned
void AIronSword::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AIronSword::BindWeapon);
	
}


// Custom code when binding
void AIronSword::BindWeapon()
{
	WeaponSkeletalMesh->SetVisibility(false);
	WeaponStaticMesh->SetVisibility(true);
	WeaponOffhandMesh->SetVisibility(false);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Weapon was bound.");
}




