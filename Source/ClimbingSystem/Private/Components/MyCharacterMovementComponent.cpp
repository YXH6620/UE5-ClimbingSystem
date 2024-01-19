// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void UMyCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceClimbableSurface();
}


#pragma region ClimbTraces
TArray<FHitResult> UMyCharacterMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End,
                                                                              bool bShowDebugShape)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;

	UKismetSystemLibrary::CapsuleTraceMultiForObjects(
		this,
		Start,
		End,
		ClimbCapsuleTraceRadius,
		ClimbCapsuleTraceHalfHeight,
		ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		OutCapsuleTraceHitResults,
		false
	);

	return OutCapsuleTraceHitResults;
}
#pragma endregion

#pragma region ClimbCore
void UMyCharacterMovementComponent::TraceClimbableSurface()
{
	const FVector StartOffset = UpdatedComponent->GetForwardVector() * 30.f;
	const FVector Start = UpdatedComponent->GetComponentLocation()+StartOffset;
	const FVector End = Start + UpdatedComponent->GetForwardVector();

	DoCapsuleTraceMultiByObject(Start, End, true);
}
#pragma endregion