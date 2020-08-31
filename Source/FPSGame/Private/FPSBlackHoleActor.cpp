// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHoleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Math/Vector.h"


// Sets default values
AFPSBlackHoleActor::AFPSBlackHoleActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RootComponent = MeshComp;

    BigSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("BigSphereComp"));
    BigSphereComp->SetupAttachment(MeshComp);

    SmallSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SmallSphereComp"));
    SmallSphereComp->SetupAttachment(MeshComp);
    SmallSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHoleActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFPSBlackHoleActor::BeginPlay()
{
    Super::BeginPlay();

}

void AFPSBlackHoleActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
    {
        OtherActor->Destroy();
    }
}

// Called every frame
void AFPSBlackHoleActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TArray<UPrimitiveComponent*> CollectedActors;
    BigSphereComp->GetOverlappingComponents(CollectedActors);

    for (int32 i = 0; i < CollectedActors.Num(); i++)
    {
        UPrimitiveComponent* comp = CollectedActors[i];
        if (comp && comp->IsSimulatingPhysics())
        {
            const float SphereRadius = BigSphereComp->GetScaledSphereRadius();

            //comp->AddRadialForce(GetActorLocation(), SphereRadius, gravityPower, ERadialImpulseFalloff::RIF_Constant, true);
            FVector normal = GetActorLocation() - comp->GetComponentLocation();
            comp->AddForce(normal * gravityPower, NAME_None, true);
        }
    }
}

