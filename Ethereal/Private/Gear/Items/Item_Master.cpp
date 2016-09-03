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
#include "Item_Master.h"

// Sets default values
AItem_Master::AItem_Master(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UsePotion.Item_UsePotion'"));

	//// Set Default Objects
	S_ItemAudio = AudioObject.Object;
	P_ItemFX = ParticleObject.Object;
	
	// Create
	ItemAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Item Audio"));
	ItemAudio->SetupAttachment(Root);
	ItemAudio->Sound = S_ItemAudio;
	ItemAudio->bAutoActivate = false;

	ItemFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Item VFX"));
	ItemFX->SetupAttachment(Root);
	ItemFX->Template = P_ItemFX;
	ItemFX->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AItem_Master::BeginPlay()
{
	Super::BeginPlay();
}

void AItem_Master::UseItem()
{
	OnItemUse.Broadcast();
}

