// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHoleActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHoleActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFPSBlackHoleActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
        void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(VisibleAnywhere, Category = "Components")
        UStaticMeshComponent* MeshComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
        USphereComponent* SmallSphereComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
        USphereComponent* BigSphereComp;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
        float gravityPower = 2000;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
