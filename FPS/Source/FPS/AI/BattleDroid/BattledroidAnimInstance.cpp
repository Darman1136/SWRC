// Fill out your copyright notice in the Description page of Project Settings.

#include "BattledroidAnimInstance.h"
#include "Animation/AnimEnums.h"
#include "AI/BattleDroid/BattledroidAICharacter.h"
#include "AI/BasicAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBattledroidAnimInstance::UBattledroidAnimInstance() {
	//RootMotionMode = ERootMotionMode::IgnoreRootMotion;
	Alive = true;
}

void UBattledroidAnimInstance::FindLookAtObjectRotator(FRotator& Rotation, float& Alpha)
{
	Alpha = 0;
	Rotation = FRotator();

	AActor* OwningActor = GetOwningActor();
	if (OwningActor && OwningActor->IsA(ABattledroidAICharacter::StaticClass())) {
		const ABattledroidAICharacter* BattledroidCharacter = Cast<ABattledroidAICharacter>(OwningActor);
		if (BattledroidCharacter && BattledroidCharacter->GetController()) {
			const UBlackboardComponent* BlackboardComp = BattledroidCharacter->GetController()->FindComponentByClass<UBlackboardComponent>();
			if (BlackboardComp) {
				const UObject* TargetObject = BlackboardComp->GetValueAsObject(ABasicAIController::BKTarget);
				if (TargetObject && TargetObject->IsA(AActor::StaticClass())) {
					const FVector SelfLocation = BattledroidCharacter->GetActorLocation();
					const FVector TargetLocation = Cast<AActor>(TargetObject)->GetActorLocation();
					FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfLocation, TargetLocation);
					FRotator BattledroidRotation = BattledroidCharacter->GetActorRotation();

					Rotation = LookAtRotation - BattledroidRotation;
					Alpha = 1;

					// -36 turn left
					// 86 turn right
					if (Rotation.Yaw > 86.f) {
						Rotation.Yaw = 86.f;
						TurnRight = true;
					}
					else if (Rotation.Yaw < -36.f) {
						Rotation.Yaw = -36.f;
						TurnLeft = true;
					}
					else {
						TurnRight = false;
						TurnLeft = false;
					}
				}
			}
		}
	}
}
